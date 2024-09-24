#pragma once

#include "All.h"
#include "Input/Input.h"
//#include "StageMain.h"
#include "Effect.h"
#include "Component.h"
#include "Movement.h"
#include "VsCollision.h"

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
    DelayTime GetUndeatableDelay() { return unbeatable_delay; }
private:
    DelayTime unbeatable_delay;
};