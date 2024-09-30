#pragma once
#include "Component.h"

class TimeTrackingObject : public Component
{
public:
    TimeTrackingObject() {}
    ~TimeTrackingObject() {}

    //名前取得
    const char* GetName() const { return "TimeTrackingObject"; }

    // 初期化
    void Start() override;
    // 更新
    void Update(float elapsedTime) override;
    // GUI描画
    void DrawImGui() override;
    //デバッグプリミティブ描画
    void DrawDebug() override;
public:
    void SetRunTimer(float time) { run_timer = time; }
private:
    int timer = 0;
    float run_timer = FLT_MAX;
};