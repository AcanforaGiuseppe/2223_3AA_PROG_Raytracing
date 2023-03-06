#pragma once 
#include "math.h"

typedef struct {
    float x;
    float y;
    float z;
} vector3_t;

static vector3_t vector3_sub(vector3_t* v1, vector3_t* v2) 
{
    vector3_t r;
    r.x = v1->x - v2->x;
    r.y = v1->y - v2->y;
    r.z = v1->z - v2->z;
    return r;
}

static float vector3_magn2(vector3_t* v) 
{
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

static float vector3_magn(vector3_t* v) 
{
    return sqrtf(vector3_magn2(v));
}

static vector3_t vector3_norm(vector3_t* v) 
{
    float magn = vector3_magn(v);

    vector3_t r;
    r.x = v->x / magn;
    r.y = v->y / magn;
    r.z = v->z / magn;
    return r;
}

static float vector3_dot(vector3_t* v1, vector3_t* v2) 
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

static vector3_t vector3_sum(vector3_t* v1, vector3_t* v2) 
{
    vector3_t r;
    r.x = v1->x + v2->x;
    r.y = v1->y + v2->y;
    r.z = v1->z + v2->z;
    return r;
}

static vector3_t vector3_mult(vector3_t* v1, float scalar) 
{
    vector3_t r;
    r.x = v1->x * scalar;
    r.y = v1->y * scalar;
    r.z = v1->z * scalar;
    return r;
}