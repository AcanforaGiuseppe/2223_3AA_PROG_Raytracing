#include "scene.h"
#include "SDL.h"
#include "vector.h"
#include "raytrace.h"
#include "color.h"

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r) {
    static scene_t s;
    s.width = screen_width;
    s.height = screen_height;
    s.sphere_count = 2;

    s.spheres[0].center = (vector3_t){-2.f, 0.f, -5.f};
    s.spheres[0].radius = 1.3f;
    s.spheres[0].color = (color_t){1.f, 0, 0};

    s.spheres[1].center = (vector3_t){2.f, 0.f, -5.f};
    s.spheres[1].radius = 1.f;
    s.spheres[1].color = (color_t){0.f, 1, 0};

    s.bg_color = (color_t){0.f, 0, 0};

    s.light.direction = (vector3_t){0, -1, 0};
    s.light.color = (color_t){0.f, 0, 1};

    s.renderer = r;
    return &s;
}

void scene_update(scene_t* s, float delta_time) {
    float heightf = (float)s->height;
    float widthf = (float)s->width;

    float aspect_ratio = widthf / heightf; 

    float fov_y_degrees = 60.f;
    float half_fov_rad = (fov_y_degrees * 0.5f) * M_PI / 180.f;
    float fov = tanf(half_fov_rad);

    vector3_t camera_position = (vector3_t){0, 0, 0};

    for(int h=0; h < heightf; ++h) {
        for(int w=0; w < widthf; ++w) 
        {
            float ndc_x = ( (float)w + 0.5f ) / widthf; //0 - 1
            float ndc_y = ( (float)h + 0.5f ) / heightf;//0 - 1

            float plane_x = (2.f * ndc_x) - 1.f; //-1:1
            float plane_y = 1.f - 2.f * ndc_y;

            plane_x *= fov;
            plane_y *= fov;

            plane_x *= aspect_ratio;

            vector3_t plane_point = (vector3_t){plane_x, plane_y, -1.f};
            vector3_t ray_dir = vector3_sub(&plane_point, &camera_position);
            ray_dir = vector3_norm(&ray_dir);

            ray_t ray;
            ray.origin = &camera_position;
            ray.direction = &ray_dir;

            color_t c = ray_trace(&ray, s);

            SDL_SetRenderDrawColor(s->renderer, c.r * 255.f, c.g * 255.f, c.b * 255.f, 255);
            SDL_RenderDrawPoint(s->renderer, w, h);
        }   
    }    

}

void scene_destroy(scene_t* s) {
    
}