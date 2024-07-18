#pragma once

#include "All.h"
#include "Input/Input.h"
#include "StageMain.h"
#include "Effect.h"
#include "Component.h"
#include "Movement.h"

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
    Character() {}
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
protected:
    std::shared_ptr<Movement>	movement;
};