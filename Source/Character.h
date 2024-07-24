#pragma once

#include "All.h"
#include "Input/Input.h"
#include "StageMain.h"
#include "Effect.h"
#include "Component.h"
#include "Movement.h"
#include "VsCollision.h"

//キャラクター
class Character :public Component
{
public:
    // コンストラクタ
    Character();
    // デストラクタ
    virtual ~Character() {}

    // 開始処理
    virtual void Start() override;

    // 更新処理
    virtual void Update(float elapsedTime) override;

    //Imgui描画
    virtual void DrawImGui() override;

    //デバッグプリミティブ描画
    virtual void DrawDebug() override;
    
    //ダメージを受ける
    virtual void TakeDamage(float damage);

    //死亡通知
    bool IsDead() { return current_health <= 0; }

public:
    // 体力セッター・ゲッター
    void SetHealth(float health) { current_health = health; }
    float GetHealth() { return current_health; }

    //anime_stateセッター・ゲッター
    void SetAnimationState(int state) { animation_state = state; }
    int GetAnimationState() { return animation_state; }

protected:
    std::shared_ptr<Movement>	movement;
    std::shared_ptr<VsCollision>	vs_collision;
    float max_health = 10;
    float current_health = max_health;

    DelayTime unbeatable_delay;

    int animation_state = 0;
};