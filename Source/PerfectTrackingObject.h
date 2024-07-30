#pragma once
#include"TrackingObject.h"

//完全追従オブジェクト
class PerfectTrackingObject : public TrackingObject
{
public:
    //名前取得
    const char* GetName()const override { return "PerfectTrackingObject"; }

    // コンストラクタ
    PerfectTrackingObject();
    // デストラクタ
    ~PerfectTrackingObject();
    // 更新
    void Update(float elapsedTime) override;
    // GUI描画
    void DrawImGui() override;
    //デバッグプリミティブ描画
    void DrawDebug() override;
};