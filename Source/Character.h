#pragma once

#include "All.h"
#include "Input/Input.h"
#include "Effect.h"

#include "Component.h"

#include "StateMachine.h"

//キャラクター
class Character :public Component
{
public:
    // 名前取得
    const char* GetName() const override { return "Character"; }

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

public:
    //ダメージを受ける
    virtual void TakeDamage(float damage);
    //ダメージを受ける
    virtual void TakeHeel(float heel);
public:
    //無敵時間のゲッターセッター
    DelayTime GetUndeatableDelay() { return unbeatable_delay; }
    void SetUndeatableDelay(bool c) { unbeatable_delay.checker = c; }

    // 体力セッター・ゲッター
    void SetHealth(float health) { current_health = health; }
    float GetHealth() { return current_health; }

    // 体力最大値セッター・ゲッター
    void SetMaxHealth(float maxhealth) { max_health = maxhealth; }
    float GetMaxHealth() { return max_health; }

    //state_machineのゲッター・セッター
    StateMachine* GetStateMachine() { return state_machine; }
    void SetStateMachine(StateMachine* state) { state_machine = state; }
private:
    DelayTime unbeatable_delay;
    float max_health = 10;
    float current_health = max_health;
    StateMachine* state_machine = nullptr;
};