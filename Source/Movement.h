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

    // 更新処理
    virtual void Update(float elapsedTime);

    // 移動
    void Move(const DirectX::XMFLOAT3& direction, float elapsedTime);
    void MoveLocal(const DirectX::XMFLOAT3& direction, float elapsedTime);

    // 旋回
    void Turn(const DirectX::XMFLOAT3& direction, float elapsedTime);

    //ジャンプ
    void Jump(float jump_power);

    //衝撃を加える
    void AddImpulse(const DirectX::XMFLOAT3& impulse);
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
    //速度
    DirectX::XMFLOAT3 GetVelocity()const { return velocity; }
    void SetVelocity(const DirectX::XMFLOAT3& value) { velocity = value; }
    //地面の上
    bool GetOnGround()const { return on_ground; }
    void SetOnGround(bool value) { on_ground = value; }
private:
    float		moveSpeed = 5.0f;
    float		turnSpeed = 6.28f;

    DirectX::XMFLOAT3 velocity = {};
    DirectX::XMFLOAT3 friction = { 0.01f,0.01f,0.01f };
    float       gravity = 0.005f;
    float       now_gravity = 0;
    bool        on_ground = false;
};