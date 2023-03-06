#pragma once 
#include "vector.h"
#include "color.h"
#include "scene.h"

typedef struct {
    vector3_t* origin;
    vector3_t* direction;
} ray_t;

color_t ray_trace(ray_t* ray, scene_t* s);