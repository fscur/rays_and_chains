#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#pragma pack(push, 1) // pack struct bits
typedef struct r_media_bitmap_header_t {
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
} r_media_bitmap_header_t;
#pragma pack(pop)

typedef struct r_media_bitmap_t {
  r_media_bitmap_header_t header;
  u32 width;
  u32 height;
  u8* data;
} r_media_bitmap_t;

r_media_bitmap_t* //
r_media_create_image(const u32 width, const i32 height);

void //
r_media_clear_image(const r_media_bitmap_t* image, const r_color_t color);

r_media_bitmap_t* //
r_media_load_image(const char* file_name);

void //
r_media_save_image(const r_media_bitmap_t* image, char* file_name);

void //
r_media_flip_image(r_media_bitmap_t* image);

void //
r_media_destroy_image(r_media_bitmap_t* image);

#ifdef __cplusplus
}
#endif