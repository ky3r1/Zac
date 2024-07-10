#include "Mathf.h"


float Mathf::Lerp(float a, float b, float t)
{
    return a * (1.0f - t) + (b * t);
}

float Mathf::RandomRange(float min, float max)
{
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}