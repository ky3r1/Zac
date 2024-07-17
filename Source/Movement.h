#pragma once
#include "Component.h"

class Movement :public Component
{
public:
    Movement();
    virtual ~Movement();

    //���O�擾
    const char* GetName()const override { return "Movement"; }

    //ImGui�`��
    void DrawImGui()override;

    // �ړ�
    void Move(const DirectX::XMFLOAT3& direction, float elapsedTime);
    void MoveLocal(const DirectX::XMFLOAT3& direction, float elapsedTime);

    // ����
    void Turn(const DirectX::XMFLOAT3& direction, float elapsedTime);

private:
    float		moveSpeed = 5.0f;
    float		turnSpeed = 6.28f;
};