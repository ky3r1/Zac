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


    //������
    virtual void Start()override;
    // �X�V����
    virtual void Update(float elapsedTime);

    // �ړ�
    void Move(DirectX::XMFLOAT3 v);
    void MoveLocal(const DirectX::XMFLOAT3& direction, float elapsedTime);

    // ����
    void Turn(float elapsedTime, float vx, float vz);

    //�W�����v
    void Jump(float jump_power);

    //�Ռ���������
    void AddImpulse(const DirectX::XMFLOAT3& impulse);

    //velocity��0�ɂ���
    void ResetVelocity();

    //�@�����g���ĔC�ӂ̕����ɕς���
    void ChangeVector(DirectX::XMFLOAT3& v, DirectX::XMFLOAT3& normal);
private:
    //�����̍X�V����
    void UpdateAxisX(float elapsedTime);
    void UpdateAxisY(float elapsedTime);
    void UpdateAxisZ(float elapsedTime);
public:
    //�Z�b�^�[�E�Q�b�^�[
    //�ړ����x
    float GetMoveSpeed()const { return moveSpeed; }
    void SetMoveSpeed(float value) { moveSpeed = value; }
    //���񑬓x
    float GetTurnSpeed()const { return turnSpeed; }
    void SetTurnSpeed(float value) { turnSpeed = value; }
    //�d��
    float GetGravity()const { return gravity; }
    void SetGravity(float value) { gravity = value; }
    //���݂̏d��
    float GetNowGravity()const { return now_gravity; }
    void SetNowGravity(float value) { now_gravity = value; }
    //���x
    DirectX::XMFLOAT3 GetVelocity()const { return velocity; }
    void SetVelocity(const DirectX::XMFLOAT3& value) { velocity = value; }
    //���C
    DirectX::XMFLOAT3 GetFriction()const { return friction; }
    void SetFriction(const DirectX::XMFLOAT3& value) { friction = value; }
    //�n�ʂ̏�
    bool GetOnGround()const { return on_ground; }
    void SetOnGround(bool value) { on_ground = value; }
    //�@��
    DirectX::XMFLOAT3 GetNormal()const { return normal; }
    void SetNormal(const DirectX::XMFLOAT3& value) { normal = value; }
private:
    float		moveSpeed = 5.0f;
    float		turnSpeed = 6.28f;

    DirectX::XMFLOAT3 velocity = {};
    DirectX::XMFLOAT3 friction = { 0.10f,0.00f,0.10f};

    float       gravity = 0.005f;
    float       now_gravity = 0;
    bool        on_ground = false;

    DirectX::XMFLOAT3 normal = { 0.0f,0.0f,0.0f };
    DirectX::XMFLOAT3 move_vec = {};
    float slope_rate;
};