#pragma once
#include "Component.h"

//CollisionObject->TrackingObjectの順に登録

//追従オブジェクト
class TrackingObject : public Component
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
    void SetSphereRadius(float r) { this->c_sphere.radius = r; }//FLT_MAXに設定すると完全追従。0に設定すると非完全追従。
    void SetRunObject(bool run_obj) { this->run_obj = run_obj; }
    void SetDeleteTimer(int delete_timer) { this->delete_timer = delete_timer; }
protected:
    int timer = 0;
    int delete_timer = INT_MAX;//消える時間(消す必要がない場合はINT_MAX)
    int max_runtimer = INT_MAX;//追跡する時間(追跡する必要がない場合はINT_MAX)
    bool run_obj = false;//真:追跡中--偽:未追跡
    DirectX::XMFLOAT3 desired_position = { FLT_MAX,FLT_MAX,FLT_MAX };
    bool desired_flg = false;
    DirectX::XMFLOAT3 default_position = {};
    Sphere c_sphere = { {0,0,0},0.0f };//目標を追跡する範囲(radiusの範囲内にいると追跡する)
    DirectX::XMFLOAT3 tpos = {FLT_MAX,FLT_MAX ,FLT_MAX };
};