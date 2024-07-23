#pragma once
#include "Component.h"

//ステージ
class Object : public Component
{
public:
    //名前取得
    const char* GetName()const override { return "Object"; }
    
    // コンストラクタ
    Object();
    // デストラクタ
    virtual ~Object();
    // 初期化
    virtual void Start() override;
    // 更新
    virtual void Update(float elapsedTime) override;
    // GUI描画
    virtual void DrawImGui() override;
protected:
};