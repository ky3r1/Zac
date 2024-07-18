#pragma once

#include"Graphics/Model.h"
#include "All.h"

//ƒRƒŠƒWƒ‡ƒ“
static class Collision
{
public:
    //‰~’Œ‚Æ‰~’Œ‚ÌŒğ·”»’è
    static bool IntersectCylinderVsSphere(
        const DirectX::XMFLOAT3& positionA,
        float radiusA,
        float heightA,
        float weightA,
        const DirectX::XMFLOAT3& positionB,
        float radiusB,
        float heightB,
        float weightB,
        DirectX::XMFLOAT3& outPositionB
    );

    //‹…‚Æ‰~’Œ‚ÌŒğ·”»’è
    static bool IntersectSphereVsCylinder(
        const DirectX::XMFLOAT3& spherePosition,
        float sphereRadius,
        const DirectX::XMFLOAT3& cylinderPosition,
        float cylinderRadius,
        float cylinderHeight,
        DirectX::XMFLOAT3& outCylinderPosition
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
    static bool InXYPoint(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos
    );

    //“_‚ª‰~“à‚É“ü‚Á‚Ä‚¢‚é‚©
    static bool PointInsideCircle(DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 center, float radius);
};