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

//�R���W����
static class Collision
{
public:
    //�~���Ɖ~���̌�������
    static bool IntersectCylinderVsCylinder(
        Cylinder& A,
        Cylinder& B
    );

    //���Ɖ~���̌�������
    static bool IntersectSphereVsCylinder(
        Sphere& sphere,
        Cylinder& cylinder
    );

    //���Ƌ��̌�������
    static bool IntersectSphereVsSphere(
        Sphere& A,
        Sphere& B
    );

    //���C�ƃ��f���̌�_����
    static bool RayCast(
        const DirectX::XMFLOAT3& start,
        const DirectX::XMFLOAT3& end,
        const DirectX::XMFLOAT4X4& worldTransform,
        const Model* model,
        HitResult& result);

    //�X�t�B�A�ƃ��f���̌�������


    //HPbar�̈ʒu
    static bool HPbarPoint(
        DirectX::XMFLOAT3 player_position,
        DirectX::XMFLOAT3 enemy_position
    );

    //bottom_left_front�`top_right_back����move_pos�������true��Ԃ�
    static bool RectInPoint(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos
    );

    //bottom_left_front�`top_right_back����XZ���ʂɂ�move_pos�������true��Ԃ�
    static bool RectInPoint2D(
        DirectX::XMFLOAT3 bottom_left_front,
        DirectX::XMFLOAT3 top_right_back,
        DirectX::XMFLOAT3 move_pos,
        Axis2D axis
    );
    // ���Ɠ_�̌�������
    static bool SphereInPoint(
        DirectX::XMFLOAT3 center,
        float radius,
        DirectX::XMFLOAT3 move_pos
    );

    //�_���~���ɓ����Ă��邩
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

    //�~�Ɖ~�̓����蔻��
    static bool CircleVsCircle(
        DirectX::XMFLOAT2 Apos,
        float Ar,
        DirectX::XMFLOAT2 Bpos,
        float Br
    );
};