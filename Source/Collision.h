#pragma once

#include"Graphics/Model.h"
#include "All.h"

enum class Axis2D
{
    X_Y,
    Y_Z,
    Z_X,
    NONE
};

//ƒRƒŠƒWƒ‡ƒ“
static class Collision
{
public:
    //‰~’Œ‚Æ‰~’Œ‚ÌŒğ·”»’è
    static bool IntersectCylinderVsCylinder(
        Cylinder& A,
        Cylinder& B
    );

    //‹…‚Æ‰~’Œ‚ÌŒğ·”»’è
    static bool IntersectSphereVsCylinder(
        Sphere& sphere,
        Cylinder& cylinder
    );

    //‹…‚Æ‹…‚ÌŒğ·”»’è
    static bool IntersectSphereVsSphere(
        Sphere& A,
        Sphere& B
    );

    //ƒŒƒC‚Æƒ‚ƒfƒ‹‚ÌŒğ“_”»’è
    static bool IntersectRayVsModel(
        const DirectX::XMFLOAT3& start,
        const DirectX::XMFLOAT3& end,
        const Model* model,
        HitResult& result
    );

    //HPbar‚ÌˆÊ’u
    static bool HPbarPoint(
        DirectX::XMFLOAT3 player_position,
        DirectX::XMFLOAT3 enemy_position
    );

    //bottom_left_front`top_right_back“à‚Émove_pos‚ª“ü‚é‚Ætrue‚ğ•Ô‚·
    static bool InPoint(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos
    );

    //bottom_left_front`top_right_back“à‚ÌXZ•½–Ê‚É‚Émove_pos‚ª“ü‚é‚Ætrue‚ğ•Ô‚·
    static bool InPoint2D(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos,
        Axis2D axis
    );

    //“_‚ª‰~“à‚É“ü‚Á‚Ä‚¢‚é‚©
    static bool PointInsideCircle(DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 center, float radius);

    static void UpdateCylinder(
        DirectX::XMFLOAT3 p,
        float r,
        float w,
        float h,
        Cylinder& c
    );

    static void UpdateSphere(
        DirectX::XMFLOAT3 p,
        float r,
        float w,
        Sphere& s
    );
};