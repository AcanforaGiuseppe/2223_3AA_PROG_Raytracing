#include "raytrace.h"
#include <stdbool.h>
#include <math.h>
#include <float.h>

static bool ray_sphere_intersect(ray_t* ray, sphere_t* sphere, rayhit_t* out) 
{
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

    vector3_t norm_unnorm = vector3_sub(&out->point, &sphere->center);
    out->normal = vector3_norm(&norm_unnorm);

    out->distance = t0;

    return true;
}


static bool ray_cast(ray_t* ray, scene_t* s, rayhit_t* out, raycast_strategy_e strategy) 
{   
    rayhit_t best_hit;
    best_hit.distance = FLT_MAX;

    bool has_best_hit = false;

    for(int i=0; i < s->sphere_count; ++i) 
    {
        sphere_t* sphere = &s->spheres[i];
        rayhit_t hit;
        bool has_hit = ray_sphere_intersect(ray, sphere, &hit);
        if (has_hit && hit.distance < best_hit.distance) 
        {
            best_hit = hit;
            has_best_hit = true;
            if (strategy == RAYCAST_FIRST) break;
        }
    }

    *out = best_hit;
    return has_best_hit;
}

color_t ray_trace(ray_t* ray, scene_t* s) 
{
    //Primary Ray
    rayhit_t hit;
    bool has_hit = ray_cast(ray, s, &hit, RAYCAST_BEST); 
    if (!has_hit) return s->bg_color;

    //Shadow Ray
    float bias = 1e-4;
    vector3_t biased_norm = vector3_mult(&hit.normal, bias);
    vector3_t biased_hit_point = vector3_sum(&hit.point, &biased_norm);

    ray_t shadow_ray;
    shadow_ray.origin = &biased_hit_point; 

    vector3_t inverted_light_dir = vector3_mult(&s->light.direction, -1);
    shadow_ray.direction = &inverted_light_dir;

    rayhit_t shadow_hit;
    bool shadow_has_hit = ray_cast(&shadow_ray, s, &shadow_hit, RAYCAST_FIRST);
    //if (shadow_has_hit) return s->bg_color;

    //Phong
    sphere_t* object = hit.object;

    float ambient_factor = 0.1f;
    color_t ambient = color_mult_scalar(&object->color, ambient_factor);

    if (shadow_has_hit) return ambient;

    //Diffuse
    float lambert = fmaxf(0.f, vector3_dot(&inverted_light_dir, &hit.normal));
    color_t diffuse = color_mult_scalar(&object->color, lambert);
    //diffuse = color_add(&diffuse, &s->light.color);

    //Specular
    vector3_t L = inverted_light_dir;
    vector3_t V = vector3_mult(&hit.point, -1.f);
    V = vector3_norm(&V);

    vector3_t H = vector3_sum(&L, &V);
    H = vector3_norm(&H);

    float specular_strength = fmaxf(0, vector3_dot(&hit.normal, &H));
    float specular_intesity = powf(specular_strength, 50.f);
    color_t specular = color_mult_scalar(&s->light.color, specular_intesity);
    
    color_t phong = (color_t){0,0,0};
    phong = color_add(&phong, &ambient);
    phong = color_add(&phong, &diffuse);
    phong = color_add(&phong, &specular);

    phong = color_clamp(&phong);
    return phong;
}