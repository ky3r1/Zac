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

    // 移動
    void Move(const DirectX::XMFLOAT3& direction, float elapsedTime);
    void MoveLocal(const DirectX::XMFLOAT3& direction, float elapsedTime);

    // 旋回
    void Turn(const DirectX::XMFLOAT3& direction, float elapsedTime);

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
};