#pragma once
#pragma once
#include "Component.h"

//ステージ
class TimeDeleteObject : public Component
{
public:
    //名前取得
    const char* GetName()const override { return "TimeDeleteObject"; }

    // コンストラクタ
    TimeDeleteObject() {};
    // デストラクタ
    virtual ~TimeDeleteObject() {};
    // 初期化
    virtual void Start() override;
    // 更新
    virtual void Update(float elapsedTime) override;
    // GUI描画
    virtual void DrawImGui() override;
public:
    void SetDeleteTime(float t) { delete_time = t; }
protected:
    float timer = 0;
    float delete_time = FLT_MAX;
};