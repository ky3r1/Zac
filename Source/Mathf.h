#pragma once
#include "All.h"

//浮動小数算術
class Mathf
{
public:
    //線形補完
    static float Lerp(float a, float b, float t);

    //指定範囲のランダムな値を返す
    static float RandomRange(float min, float max);
};