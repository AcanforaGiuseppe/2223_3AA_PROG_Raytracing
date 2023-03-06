#include "raytrace.h"

color_t ray_trace(ray_t* ray, scene_t* s) 
{
    //return (color_t){1, 0, 0};
    return *(color_t*)ray->direction;
}