#pragma once
#include"CollisionObject.h"

//追従オブジェクト
class TrackingObject : public CollisionObject
{
public:
    //名前取得
    const char* GetName()const override { return "TrackingObject"; }

    // コンストラクタ
    TrackingObject();
    // デストラクタ
    ~TrackingObject();
    // 初期化
    virtual void Start() override;
    // 更新
    virtual void Update(float elapsedTime) override;
    // GUI描画
    virtual void DrawImGui() override;
    //デバッグプリミティブ描画
    virtual void DrawDebug() override;
public:
    void SetMaxRuntimer(int max_runtimer) { this->max_runtimer = max_runtimer; }
    void SetDesiredPosition(DirectX::XMFLOAT3 d) { this->desired_position = d; }
    void SetSphereRadius(float r) { this->c_sphere.radius = r; }
    void SetDeleteTimer(int delete_timer) { this->delete_timer = delete_timer; }
protected:
    int timer = 0;
    int delete_timer = INT_MAX;
    int max_runtimer = INT_MAX;
    bool run_obj = false;
    DirectX::XMFLOAT3 desired_position = { FLT_MAX,FLT_MAX,FLT_MAX };
    bool desired_flg = false;
    DirectX::XMFLOAT3 default_position = {};
    Sphere c_sphere = { {0,0,0},0.0f };//Actorを追跡する範囲
    DirectX::XMFLOAT3 ppos = {FLT_MAX,FLT_MAX ,FLT_MAX };
};