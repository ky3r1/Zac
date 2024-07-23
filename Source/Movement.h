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

    // �X�V����
    virtual void Update(float elapsedTime);

    // �ړ�
    void Move(const DirectX::XMFLOAT3& direction, float elapsedTime);
    void MoveLocal(const DirectX::XMFLOAT3& direction, float elapsedTime);

    // ����
    void Turn(const DirectX::XMFLOAT3& direction, float elapsedTime);

    //�W�����v
    void Jump();

    //�Ռ���������
    void AddImpulse(const DirectX::XMFLOAT3& impulse);

    //�Z�b�^�[�E�Q�b�^�[
    //�ړ����x
    float GetMoveSpeed()const { return moveSpeed; }
    void SetMoveSpeed(float value) { moveSpeed = value; }
    //���񑬓x
    float GetTurnSpeed()const { return turnSpeed; }
    void SetTurnSpeed(float value) { turnSpeed = value; }

private:
    float		moveSpeed = 5.0f;
    float		turnSpeed = 6.28f;
    DirectX::XMFLOAT3 velocity = {};
    DirectX::XMFLOAT3 friction = {0.01f,0.01f,0.01f};
    float       gravity = 0.05f;
    float       now_gravity = 0;
};