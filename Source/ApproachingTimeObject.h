#pragma once
#include "Object.h"

class ApproachingTimeObject : public Object
{
public:
    //名前取得
    const char* GetName()const override { return "DeadAfterObject"; }

    // コンストラクタ
    ApproachingTimeObject();
    // デストラクタ
    ~ApproachingTimeObject();
    // 初期化
    void Start() override;
    // 更新
    void Update(float elapsedTime) override;
    // GUI描画
    void DrawImGui() override;
    //デバッグプリミティブ描画
    void DrawDebug() override;
public:
    void SetMaxRuntimer(int max_runtimer) { this->max_runtimer = max_runtimer; }
private:
    int timer=0;
    int max_runtimer = INT_MAX;
    bool test_flg = false;
    bool run_obj = false;
    DirectX::XMFLOAT3 default_position = {};
};