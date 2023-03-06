#pragma once 
#include "vector.h"
#include "color.h"
#include "scene.h"

//typedef struct scene_t scene_t;

typedef struct {
    vector3_t* origin;
    vector3_t* direction;
} ray_t;

typedef struct {
    vector3_t point;
    sphere_t* object;
} rayhit_t;

color_t ray_trace(ray_t* ray, scene_t* s);


