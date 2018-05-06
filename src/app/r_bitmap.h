#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "r_math.h"
#include "r_types.h"

#pragma pack(push, 1) // pack struct bits

typedef struct BitmapHeader {
  u16 type;
  u32 file_size;
  u32 reserved0;
  u32 offset;
  u32 size;
  u32 width;
  i32 height;
  u16 planes;
  u16 bit_count;
  u32 compression;
  u32 data_size;
  i32 x_pels_per_meter;
  i32 y_pels_per_meter;
  u32 colors_used;
  u32 colors_important;
  u32 red_mask;
  u32 green_mask;
  u32 blue_mask;
  u32 alpha_mask;
  u32 cs_type;
  u32 cie_red_x;
  u32 cie_red_y;
  u32 cie_red_z;
  u32 cie_green_x;
  u32 cie_green_y;
  u32 cie_green_z;
  u32 cie_blue_x;
  u32 cie_blue_y;
  u32 cie_blue_z;
  u32 gamma_red;
  u32 gamma_green;
  u32 gamma_blue;
} BitmapHeader;

#pragma pack(pop)

typedef struct Bitmap {
  BitmapHeader header;
  u32 width;
  u32 height;
  u8* data;
} Bitmap;

Bitmap*
r_create_image(const u32 width, const i32 height) {
  Bitmap* image = (Bitmap*)malloc(sizeof(Bitmap));
  image->width = width;
  image->height = height < 0 ? -height : height;

  u32 image_size = width * image->height;
  u32 data_size = image_size * sizeof(u32);
  u32 header_size = sizeof(BitmapHeader);
  u32 file_size = header_size + data_size;
  u32 offset = file_size - data_size;

  BitmapHeader header = {0};
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

void
r_clear_image(const Bitmap* image, const Color color) {
  i32 x, y, w, h, bpp, stride;
  w = image->width;
  h = image->height;
  bpp = image->header.bit_count;
  stride = ((bpp * w + 31) / 32) * 4;

  for (y = 0; y < h; ++y) {
    for (x = 0; x < stride; x += 4) {
      u32 index = y * stride + x;
      Color c = color;

      if (y < 25)
        c = (Color){0.0f, 0.0f, 1.0f, 1.0f};

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

Bitmap*
r_load_image(const char* file_name) {
  FILE* file = 0;
  file = fopen(file_name, "rb");
  fseek(file, 0L, SEEK_END);
  size_t file_size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  size_t header_size = sizeof(BitmapHeader);
  size_t data_size = file_size - header_size;

  Bitmap* image = malloc(sizeof(Bitmap));
  image->data = malloc(data_size);

  fread(&image->header, 1, header_size, file);
  fread(image->data, 1, data_size, file);
  fclose(file);

  image->width = image->header.width;
  image->height =
      image->header.height < 0 ? -image->header.height : image->header.height;
  return image;
}

void
r_save_image(const Bitmap* image, char* file_name) {
  FILE* file = 0;
  file = fopen("image.bmp", "wb");
  fwrite(&image->header, 1, sizeof(BitmapHeader), file);
  fwrite(image->data, 1, image->header.data_size, file);
  fclose(file);
}

void
r_flip_image(Bitmap* image) {
  image->header.height = -image->header.height;
}

void
r_destroy_image(Bitmap* image) {
  free(image->data);
  free(image);
}
