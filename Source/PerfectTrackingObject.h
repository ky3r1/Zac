#pragma once
#include"CollisionObject.h"

//完全追従オブジェクト
class PerfectTrackingObject : public CollisionObject
{
public:
    //名前取得
    const char* GetName()const override { return "ApproachingObject"; }

    // コンストラクタ
    PerfectTrackingObject();
    // デストラクタ
    ~PerfectTrackingObject();
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
    void SetDesiredPosition(DirectX::XMFLOAT3 desired_position) { this->desired_position = desired_position; }
    void SetSphereRadius(float r) { this->c_sphere.radius = r; }
private:
    int timer=0;
    int max_runtimer = INT_MAX;
    bool run_obj = false;
    DirectX::XMFLOAT3 desired_position = {FLT_MAX,FLT_MAX,FLT_MAX};
    bool desired_flg = false;
    DirectX::XMFLOAT3 default_position = {};
    Sphere c_sphere = { {0,0,0},0.0f };
};