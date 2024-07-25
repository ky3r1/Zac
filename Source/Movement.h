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


    //初期化
    virtual void Start()override;
    // 更新処理
    virtual void Update(float elapsedTime);

    // 移動
    void Move(DirectX::XMFLOAT3 v);
    void MoveLocal(const DirectX::XMFLOAT3& direction, float elapsedTime);

    // 旋回
    void Turn(float elapsedTime, float vx, float vz);

    //ジャンプ
    void Jump(float jump_power);

    //衝撃を加える
    void AddImpulse(const DirectX::XMFLOAT3& impulse);

    //velocityを0にする
    void ResetVelocity();

    //法線を使って任意の方向に変える
    void ChangeVector(DirectX::XMFLOAT3& v, DirectX::XMFLOAT3& normal);
private:
    //軸事の更新処理
    void UpdateAxisX(float elapsedTime);
    void UpdateAxisY(float elapsedTime);
    void UpdateAxisZ(float elapsedTime);
public:
    //セッター・ゲッター
    //移動速度
    float GetMoveSpeed()const { return moveSpeed; }
    void SetMoveSpeed(float value) { moveSpeed = value; }
    //旋回速度
    float GetTurnSpeed()const { return turnSpeed; }
    void SetTurnSpeed(float value) { turnSpeed = value; }
    //重力
    float GetGravity()const { return gravity; }
    void SetGravity(float value) { gravity = value; }
    //現在の重力
    float GetNowGravity()const { return now_gravity; }
    void SetNowGravity(float value) { now_gravity = value; }
    //速度
    DirectX::XMFLOAT3 GetVelocity()const { return velocity; }
    void SetVelocity(const DirectX::XMFLOAT3& value) { velocity = value; }
    //摩擦
    DirectX::XMFLOAT3 GetFriction()const { return friction; }
    void SetFriction(const DirectX::XMFLOAT3& value) { friction = value; }
    //地面の上
    bool GetOnGround()const { return on_ground; }
    void SetOnGround(bool value) { on_ground = value; }
    //法線
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