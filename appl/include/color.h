#pragma once 

typedef struct {
    float r;
    float g;
    float b;
} color_t;


static color_t color_mult_scalar(color_t* color, float scalar) 
{
    color_t res;
    res.r = color->r * scalar;
    res.g = color->g * scalar;
    res.b = color->b * scalar;
    return res;
}   

static color_t color_add(color_t* c1, color_t* c2) 
{
    color_t res;
    res.r = c1->r + c2->r;
    res.g = c1->g + c2->g;
    res.b = c1->b + c2->b;
    return res;
}   

static color_t color_mult(color_t* c1, color_t* c2) 
{
    color_t res;
    res.r = c1->r * c2->r;
    res.g = c1->g * c2->g;
    res.b = c1->b * c2->b;
    return res;
}   

static color_t color_clamp(color_t* color) 
{
    color_t res;
    res.r = color->r > 1 ? 1 : color->r;
    res.g = color->g > 1 ? 1 : color->g;
    res.b = color->b > 1 ? 1 : color->b;
    return res;
} 