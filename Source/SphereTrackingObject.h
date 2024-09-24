#pragma once
#include "Component.h"

//TrackingObject->SphereTrackingObjectの順に登録

//追従オブジェクト
class SphereTrackingObject : public Component
{
public:
    //名前取得
    const char* GetName()const override { return "SphereTrackingObject"; }

    // コンストラクタ
    SphereTrackingObject();
    // デストラクタ
    ~SphereTrackingObject();
    // 初期化
    virtual void Start() override;
    // 更新
    virtual void Update(float elapsedTime) override;
    // GUI描画
    virtual void DrawImGui() override;
    //デバッグプリミティブ描画
    virtual void DrawDebug() override;
public:
    void SetRadiusSearch(float s) { this->radius_search = s; }
protected:
    float radius_search=0.0f;//目標が範囲内に入っていると追跡開始
};