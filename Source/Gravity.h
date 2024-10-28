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
protected:
    //地球の中心座標から地表への距離pos
    DirectX::XMFLOAT3 pos = { 0.0f,-6.378137e6f,0.0f };
    //地球の質量mass
    float mass = 5.9724e24f;
};