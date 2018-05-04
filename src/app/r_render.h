#pragma once

#include "r_types.h"
#include "r_math.h"
#include "r_bitmap.h"

Color 
li(World* world, Ray ray) {
    f32 t_min = world->camera.far;

    if (ray_plane_intersection(ray, world->floor, &t_min))
        return (Color){ 1.0f, 0.0f, 0.0f, 1.0f };
    else
        return world->sky_color;
}

void 
start_raytracing(Bitmap* image, f32 dt) {
    
    Camera camera = { 0 };
    camera.near = 1.0;
    camera.far = 1001.0;
    camera.fov = 90;
    camera.position = (v3) { 0.0, dt, 1.0 };
    camera.look_at = (v3) { 0.0, 0.0, 0.0 };
    
    camera.up = (v3) { 0.0, 1.0, 0.0 };
    camera.direction = norm3(sub3(camera.position, camera.look_at));
    camera.right = norm3(cross3(camera.up, camera.direction));
    camera.up = cross3(camera.direction, camera.right);

    Plane plane = {0};
    plane.position = (v3) { 0.0f , 0.0f , 0.0f };
    plane.normal = (v3) { 0.0f, 1.0f, 0.0f };
    World world = {0};
    world.sky_color = (Color) { 0.5f, 0.6f, 0.8f, 1.0f};
    world.camera = camera;
    world.floor = plane;

    f32 x, y, w, h;

    w = (f32)image->width;
    h = (f32)image->height;

    f32 x_factor = 1.0f/w;
    f32 y_factor = 1.0f/h;
    f32 x_aspect = w > h ? w/h : 1.0f;
    f32 y_aspect = h > w ? h/w : 1.0f;

    u32* pixels = (u32*)image->data;

    v3 film_z = add3(camera.position, mul3(camera.direction, -camera.near));

    for (y = 0; y < h; ++y) {
        v3 film_y = mul3(camera.up, (y * y_factor * 2.0f - 1.0f) * y_aspect);

        for (x = 0.0f; x < w; ++x) {
            v3 film_x = mul3(camera.right, (x * x_factor * 2.0f - 1.0f) * x_aspect);
            v3 film_pos = add3(add3(film_x, film_y), film_z);
            Ray ray = { camera.position, norm3(sub3(film_pos, camera.position)) };

            Color color = li(&world, ray);

            u8 r = round_f32_to_i32(color.r * 255.0f);
            u8 g = round_f32_to_i32(color.g * 255.0f);
            u8 b = round_f32_to_i32(color.b * 255.0f);
            u8 a = round_f32_to_i32(color.a * 255.0f);

            *pixels++ = from_u8_to_32(a, r, g, b);
        }
    }
}