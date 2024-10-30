#pragma once
#include "Component.h"

//CollisionObject->FrontObjectの順に登録

//前方移動オブジェクト
class Gravity : public Component
{
public:
    //名前取得
    const char* GetName()const override { return "Gravity"; }

    // コンストラクタ
    Gravity() {}
    // デストラクタ
    ~Gravity() {}
    // 初期化
    virtual void Start() override;
    // 更新
    virtual void Update(float elapsedTime) override;
    // GUI描画
    virtual void DrawImGui() override;
    //デバッグプリミティブ描画
    virtual void DrawDebug() override;
public:
    void Jump(float power);
public:
    void SetSpeed(float speed){ this->speed = speed; }
    float GetSpeed() { return speed; }
    bool GetOnGround() { return on_ground; }
    void SetOnGround(bool on_ground) { this->on_ground = on_ground; }//true:地表 false:空中
    DirectX::XMFLOAT3 GetPower() { return power; }
protected:
    //地球の中心座標から地表への距離pos
    DirectX::XMFLOAT3 pos = { 0.0f,-6.378137e6f,0.0f };
    //地球の質量mass(5.9724e24-5.9724x10^24-kg)
    float mass = 5.9724e24f;
    float speed = 1.0f;
    DirectX::XMFLOAT3 power = {};
    bool on_ground = false;
};