#pragma once
#include "Component.h"

class AiComponent :public Component
{
public:
    AiComponent();
    ~AiComponent();

    //名前取得
    const char* GetName()const override { return "AiComponent"; }

    //ImGui描画
    void DrawImGui()override;

    //初期化
    virtual void Start()override;
    // 更新処理
    virtual void Update(float elapsedTime);

    // デバッグ描画
    void DrawDebug() override;
};