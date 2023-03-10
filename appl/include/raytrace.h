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
    vector3_t normal;
    sphere_t* object;
    float distance;
} rayhit_t;

typedef enum 
{
    RAYCAST_BEST,
    RAYCAST_FIRST
} raycast_strategy_e;


color_t ray_trace(ray_t* ray, scene_t* s);


