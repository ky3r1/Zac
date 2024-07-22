#pragma once

#include "All.h"
#include "Input/Input.h"
#include "StageMain.h"
#include "Effect.h"
#include "Component.h"
#include "Movement.h"
#include "VsCollision.h"

struct DelayTime
{
    int time;
    bool checker = false;
};

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

public:
    // 体力セッター・ゲッター
    void SetHealth(float health) { current_health = health; }
    float GetHealth() { return current_health; }
protected:
    std::shared_ptr<Movement>	movement;
    std::shared_ptr<VsCollision>	vs_collision;
    float max_health = 10;
    float current_health = max_health;
};