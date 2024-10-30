#pragma once
#include "Component.h"

class Movement :public Component
{
public:
    Movement();
    virtual ~Movement();

    //名前取得
    const char* GetName()const override { return "Movement"; }

    //ImGui描画
    void DrawImGui()override;
    void DrawDebug()override;

    void Reset()override;

    //初期化
    virtual void Start()override;
    // 更新処理
    virtual void Update(float elapsedTime);

    // 移動
    void Move(DirectX::XMFLOAT3 v);
    void Move(DirectX::XMFLOAT3 v,float force);
    void MoveTarget(DirectX::XMFLOAT3 tp,float elapsedTime);

    // 旋回
    void Turn(float elapsedTime, DirectX::XMFLOAT3 v);

    //衝撃を加える
    void AddForce(const DirectX::XMFLOAT3& impulse);

    //velocityを0にする
    void ResetVelocity();
public:
    //セッター・ゲッター
    //移動速度
    float GetMoveSpeed()const { return move_speed; }
    void SetMoveSpeed(float value) { move_speed = value; }
    //旋回速度
    float GetTurnSpeed()const { return turnSpeed; }
    void SetTurnSpeed(float value) { turnSpeed = value; }
    //摩擦
    float GetFriction()const { return friction; }
    void SetFriction(const float& value) { friction = value; }
    //法線
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
    //加速度
    DirectX::XMFLOAT3 GetAcceleration()const { return acceleration; }
    void SetAcceleration(const DirectX::XMFLOAT3& value) { acceleration = value; }

    //合力
    DirectX::XMFLOAT3 GetResultant()const { return resultant; }
    void SetResultant(const DirectX::XMFLOAT3& value) { resultant = value; }

    //速度
    DirectX::XMFLOAT3 GetVelocity()const { return velocity; }
    void SetVelocity(const DirectX::XMFLOAT3& value) { velocity = value; }

    //重量
    float GetMass()const { return mass; }
    void SetMass(float value) { mass = value; }
private:
    float mass = 1.0f;//質量
    DirectX::XMFLOAT3 velocity = {};//速度
    DirectX::XMFLOAT3 acceleration = {};//加速度
    DirectX::XMFLOAT3 resultant = {};//合力
};