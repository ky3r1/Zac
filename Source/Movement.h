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
    void DrawDebug()override;

    void Reset()override;

    //������
    virtual void Start()override;
    // �X�V����
    virtual void Update(float elapsedTime);

    // �ړ�
    void Move(DirectX::XMFLOAT3 v);
    void Move(DirectX::XMFLOAT3 v,float force);
    void MoveTarget(DirectX::XMFLOAT3 tp,float elapsedTime);

    // ����
    void Turn(float elapsedTime, DirectX::XMFLOAT3 v);

    //�Ռ���������
    void AddForce(const DirectX::XMFLOAT3& impulse);

    //velocity��0�ɂ���
    void ResetVelocity();
public:
    //�Z�b�^�[�E�Q�b�^�[
    //�ړ����x
    float GetMoveSpeed()const { return move_speed; }
    void SetMoveSpeed(float value) { move_speed = value; }
    //���񑬓x
    float GetTurnSpeed()const { return turnSpeed; }
    void SetTurnSpeed(float value) { turnSpeed = value; }
    //���C
    float GetFriction()const { return friction; }
    void SetFriction(const float& value) { friction = value; }
    //�@��
    DirectX::XMFLOAT3 GetNormal()const { return normal; }
    void SetNormal(const DirectX::XMFLOAT3& value) { normal = value; }
private:
    float		move_speed = 500.0f;
    float		turnSpeed = 6.28f;

    //DirectX::XMFLOAT3 velocity = {};
    float friction = { 6.00f };

    DirectX::XMFLOAT3 normal = { 0.0f,0.0f,0.0f };
    float slope_rate;
public:
    //�����x
    DirectX::XMFLOAT3 GetAcceleration()const { return acceleration; }
    void SetAcceleration(const DirectX::XMFLOAT3& value) { acceleration = value; }

    //����
    DirectX::XMFLOAT3 GetResultant()const { return resultant; }
    void SetResultant(const DirectX::XMFLOAT3& value) { resultant = value; }

    //���x
    DirectX::XMFLOAT3 GetVelocity()const { return velocity; }
    void SetVelocity(const DirectX::XMFLOAT3& value) { velocity = value; }

    //�d��
    float GetMass()const { return mass; }
    void SetMass(float value) { mass = value; }
private:
    float mass = 1.0f;//����
    DirectX::XMFLOAT3 velocity = {};//���x
    DirectX::XMFLOAT3 acceleration = {};//�����x
    DirectX::XMFLOAT3 resultant = {};//����
};