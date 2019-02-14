#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "r_media_bitmap.h"

r_media_bitmap_t* //
r_media_create_image(const u32 width, const i32 height) {
  r_media_bitmap_t* image = (r_media_bitmap_t*)malloc(sizeof(r_media_bitmap_t));
  image->width = width;
  image->height = height < 0 ? -height : height;

  u32 image_size = width * image->height;
  u32 data_size = image_size * sizeof(u32);
  u32 header_size = sizeof(r_media_bitmap_header_t);
  u32 file_size = header_size + data_size;
  u32 offset = file_size - data_size;

  r_media_bitmap_header_t header = {0};
  header.type = 0x4D42;
  header.file_size = file_size;
  header.offset = offset;
  header.size = header_size - 14; // bitmap header size
  header.width = width;
  header.height = height;
  header.planes = 1;
  header.bit_count = 32;
  header.data_size = data_size;

  image->header = header;
  image->data = (u8*)malloc(data_size);

  return image;
}

void //
r_media_clear_image(const r_media_bitmap_t* image, const r_color_t color) {
  i32 x, y, w, h, bpp, stride;
  w = image->width;
  h = image->height;
  bpp = image->header.bit_count;
  stride = ((bpp * w + 31) / 32) * 4;

  for (y = 0; y < h; ++y) {
    for (x = 0; x < stride; x += 4) {
      u32 index = y * stride + x;
      r_color_t c = color;

      if (y < 25)
        c = (r_color_t){0.0f, 0.0f, 1.0f, 1.0f};

      u8 r = round_f32_to_i32(c.r * 255.0f);
      u8 g = round_f32_to_i32(c.g * 255.0f);
      u8 b = round_f32_to_i32(c.b * 255.0f);
      u8 a = round_f32_to_i32(c.a * 255.0f);

      image->data[index + 0] = b;
      image->data[index + 1] = g;
      image->data[index + 2] = r;
      image->data[index + 3] = a;
    }
  }
}

r_media_bitmap_t* //
r_media_load_image(const char* file_name) {
  FILE* file = 0;
  file = fopen(file_name, "rb");
  fseek(file, 0L, SEEK_END);
  size_t file_size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  size_t header_size = sizeof(r_media_bitmap_header_t);
  size_t data_size = file_size - header_size;

  r_media_bitmap_t* image = malloc(sizeof(r_media_bitmap_t));
  image->data = malloc(data_size);

  fread(&image->header, 1, header_size, file);
  fread(image->data, 1, data_size, file);
  fclose(file);

  image->width = image->header.width;
  image->height =
      image->header.height < 0 ? -image->header.height : image->header.height;
  return image;
}

void //
r_media_save_image(const r_media_bitmap_t* image, char* file_name) {
  FILE* file = 0;
  file = fopen("image.bmp", "wb");
  fwrite(&image->header, 1, sizeof(r_media_bitmap_header_t), file);
  fwrite(image->data, 1, image->header.data_size, file);
  fclose(file);
}

void //
r_media_flip_image(r_media_bitmap_t* image) {
  image->header.height = -image->header.height;
}

void //
r_media_destroy_image(r_media_bitmap_t* image) {
  free(image->data);
  free(image);
}
