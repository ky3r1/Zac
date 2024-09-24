#pragma once
#include "Component.h"

//CollisionObject->FrontObjectの順に登録

//前方移動オブジェクト
class FrontObject : public Component
{
public:
    //名前取得
    const char* GetName()const override { return "FrontObject"; }

    // コンストラクタ
    FrontObject() {}
    // デストラクタ
    ~FrontObject() {}
    // 初期化
    virtual void Start() override;
    // 更新
    virtual void Update(float elapsedTime) override;
    // GUI描画
    virtual void DrawImGui() override;
    //デバッグプリミティブ描画
    virtual void DrawDebug() override;
public:
    void SetForward(DirectX::XMFLOAT3 f) { forward = f; }
    void SetPower(float p) { power = p; }
protected:
    DirectX::XMFLOAT3 forward;
    float power;
};