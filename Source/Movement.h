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
    void Jump();

    //衝撃を加える
    void AddImpulse(const DirectX::XMFLOAT3& impulse);

    //セッター・ゲッター
    //移動速度
    float GetMoveSpeed()const { return moveSpeed; }
    void SetMoveSpeed(float value) { moveSpeed = value; }
    //旋回速度
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