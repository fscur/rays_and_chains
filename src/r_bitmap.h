#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "r_types.h"

#pragma pack(push, 1) //pack struct bits

typedef struct BitmapHeader {
    u16 type;
    u32 file_size;
    u32 reserved;
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
} BitmapHeader;

#pragma pack(pop)

typedef struct Bitmap {
    BitmapHeader header;
    u32 width;
    u32 height;
    u8* data;
} Bitmap;

Bitmap* rc_create_image (const u32 width, const i32 height) {
    Bitmap* image = (Bitmap*)malloc(sizeof(Bitmap));
    image->width = width;
    image->height = height < 0 ? -height : height;

    u32 image_size = width * image->height; 
    u32 data_size = image_size * sizeof(u32);
    u32 header_size = sizeof(BitmapHeader);
    u32 file_size = header_size + data_size;
    u32 offset = file_size - data_size;

    BitmapHeader header = {};
    header.type = 0x4D42;
    header.file_size = file_size;
    header.offset = offset;
    header.size = header_size - 14; //bitmap header size
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bit_count = 32;
    header.data_size = data_size;

    image->header = header;
    image->data = (u8*)malloc(data_size);

    return image;
}

void rc_clear_image(const Bitmap* image, Color color) {
    i32 x, y, w, h, bpp, stride;
    w = image->width;
    h = image->height;
    bpp = image->header.bit_count;
    stride = ((bpp * w + 31) / 32) * 4;

    for (y = 0; y < h; ++y) {
        for (x = 0; x < stride; x+=4) {
            u32 index = y * stride + x;
            Color c = color;

            if (y < 25)
                c = (Color) { 0.0f, 0.0f, 1.0f, 1.0f };

            u8 r = round_f32_to_i32(c.r * 255.0f);
            u8 g = round_f32_to_i32(c.g * 255.0f);
            u8 b = round_f32_to_i32(c.b * 255.0f);
            u8 a = round_f32_to_i32(c.a * 255.0f);

            image->data[index+0] = b;
            image->data[index+1] = g;
            image->data[index+2] = r;
            image->data[index+3] = a;
        }
    }
}

void rc_save_image (const Bitmap* image, char* file_name) {
    FILE* file = 0;
    file = fopen("image.bmp", "wb");
    fwrite(&image->header, 1, sizeof(BitmapHeader), file);
    fwrite(image->data, 1, image->header.data_size, file);
    fclose(file);
}

void rc_destroy_image (Bitmap* image) {
    free(image->data);
    free(image);
}