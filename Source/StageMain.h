#pragma once
//#include"Graphics/Shader.h"
#include"Graphics/Model.h"
//#include "Collision.h"
#include "Stage.h"

//ステージ
class StageMain:public Stage 
{
public:
    //名前取得
    const char* GetName()const override { return "StageMain"; }

    // コンストラクタ
    StageMain();
    // デストラクタ
    ~StageMain();
    // 初期化
    void Start() override;
    // 更新
    void Update(float elapsedTime) override;

    // デバッグプリミティブ描画
    void DrawDebug() override;
    //Imgui描画
    void DrawImGui() override;

    //// 名前取得
    //const char* GetName() const override { return "Player"; }
};