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

//コリジョン
static class Collision
{
public:
    //円柱と円柱の交差判定
    static bool IntersectCylinderVsCylinder(
        Cylinder& A,
        Cylinder& B
    );

    //球と円柱の交差判定
    static bool IntersectSphereVsCylinder(
        const DirectX::XMFLOAT3& spherePosition,
        float sphereRadius,
        const DirectX::XMFLOAT3& cylinderPosition,
        float cylinderRadius,
        float cylinderHeight,
        DirectX::XMFLOAT3& outCylinderPosition
    );

    //レイとモデルの交点判定
    static bool IntersectRayVsModel(
        const DirectX::XMFLOAT3& start,
        const DirectX::XMFLOAT3& end,
        const Model* model,
        HitResult& result
    );

    //HPbarの位置
    static bool HPbarPoint(
        DirectX::XMFLOAT3 player_position,
        DirectX::XMFLOAT3 enemy_position
    );

    //bottom_left_front〜top_right_back内にmove_posが入るとtrueを返す
    static bool InPoint(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos
    );

    //bottom_left_front〜top_right_back内のXZ平面ににmove_posが入るとtrueを返す
    static bool InPoint2D(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos,
        Axis2D axis
    );

    //点が円内に入っているか
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