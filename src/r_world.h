#pragma once

#include "r_types.h"
#include "r_math.h"

typedef struct Camera {
    f32 near;
    f32 far;
    f32 fov;
    v3 position;
    v3 look_at;    
    v3 up;
    v3 right;
    v3 direction;
} Camera;

typedef struct World {
    Color sky_color;
    Camera camera;
    Plane floor;
} World;