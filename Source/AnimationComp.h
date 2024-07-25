#pragma once
#include "Component.h"
#include "Model.h"

class AnimationComp :public Component
{
public:
    AnimationComp();
    virtual ~AnimationComp();

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
    //std::vector<AnimUnity> Storage;
    Animation old_animation;
};