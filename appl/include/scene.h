#ifndef SCENE_H
#define SCENE_H
#include "SDL.h"
#include "vector.h"
#include "color.h"

typedef struct
{
    vector3_t center;
    float radius;

    struct
    {
        color_t albedo;
        color_t specular_color;
        float specular_shiness_factor;
        float reflect_factor;
    } material;

} sphere_t;

typedef struct
{
    vector3_t direction;
    color_t color;
    float intensity;
} light_t;

typedef struct
{
    int width;
    int height;
    SDL_Renderer* renderer;
    sphere_t spheres[2];
    int sphere_count;
    color_t bg_color;
    light_t light;
} scene_t;

scene_t* scene_create(int w, int h, SDL_Renderer*);
void scene_update(scene_t*, float delta_time);
void scene_destroy(scene_t*);

#endif //SCENE_H