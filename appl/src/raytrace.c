#include "raytrace.h"
#include <stdbool.h>

bool ray_cast(ray_t* ray, scene_t* s, rayhit_t* out) 
{
    sphere_t* sphere = &s->spheres[0];
    //TODO: For loop on all spheres

    vector3_t L = vector3_sub(&sphere->center, ray->origin);
    float Tca = vector3_dot(&L, ray->direction);

    //d = sqrt(magn(L*L) - tca*tca)

    //d2 =magn(L*L) - tca*tca
    // if(d2 > radius*radius) return false;

    float d2 = vector3_magn2(&L) - Tca*Tca;
    float radius2 = sphere->radius * sphere->radius;
    if (d2 > radius2) return false;

    float Thc = sqrtf(radius2 - d2);

    float t0 = Tca - Thc;
    float t1 = Tca + Thc;

    //Finding smallest positive among t0 and t1
    if (t1 < t0) 
    {
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }
    
    out->object = sphere;

    vector3_t dir_unnorm = vector3_mult(ray->direction, t0);
    out->point = vector3_sum(ray->origin, &dir_unnorm);

    return true;
}

color_t ray_trace(ray_t* ray, scene_t* s) 
{
    //Primary Ray
    rayhit_t hit;
    bool has_hit = ray_cast(ray, s, &hit); 
    if (!has_hit) return s->bg_color;

    //Shadow Ray
    ray_t shadow_ray;
    shadow_ray.origin = &hit.point; //Note: attention!!!

    vector3_t inverted_light_dir = vector3_mult(&s->light.direction, -1);
    shadow_ray.direction = &inverted_light_dir;

    rayhit_t shadow_hit;
    bool shadow_has_hit = ray_cast(&shadow_ray, s, &shadow_hit);
    if (shadow_has_hit) return s->bg_color;

    //Phong

    return hit.object->color;
}