#pragma once

#include"Graphics/Model.h"
#include "All.h"
#include "Actor.h"

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
        Sphere& sphere,
        Cylinder& cylinder
    );

    //球と球の交差判定
    static bool IntersectSphereVsSphere(
        Sphere& A,
        Sphere& B
    );

    //レイとモデルの交点判定
    static bool RayCast(
        const DirectX::XMFLOAT3& start,
        const DirectX::XMFLOAT3& end,
        const DirectX::XMFLOAT4X4& worldTransform,
        const Model* model,
        HitResult& result);

    //スフィアとモデルの交差判定


    //HPbarの位置
    static bool HPbarPoint(
        DirectX::XMFLOAT3 player_position,
        DirectX::XMFLOAT3 enemy_position
    );

    //bottom_left_front～top_right_back内にmove_posが入るとtrueを返す
    static bool RectInPoint(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos
    );

    //bottom_left_front～top_right_back内のXZ平面ににmove_posが入るとtrueを返す
    static bool RectInPoint2D(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos,
        Axis2D axis
    );
    // 球と点の交差判定
    static bool SphereInPoint(
        DirectX::XMFLOAT3 center,
        float radius,
        DirectX::XMFLOAT3 move_pos
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

    //円と円の当たり判定
    static bool CircleVsCircle(
        DirectX::XMFLOAT2 Apos,
        float Ar,
        DirectX::XMFLOAT2 Bpos,
        float Br
    );
};