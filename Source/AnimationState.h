#pragma once
#include "Component.h"
#include "Model.h"

class AnimationState :public Component
{
public:
    AnimationState();
    virtual ~AnimationState();

    //名前取得
    const char* GetName()const override { return "AnimationState"; }

    //ImGui描画
    void DrawImGui()override;

    // 更新処理
    virtual void Update(float elapsedTime);

    // アニメーションが停止していいアニメーションか判定
    bool IsAnimationStopFlg();

public:
    //セッター・ゲッター
private:
    Animation old_animation;
};