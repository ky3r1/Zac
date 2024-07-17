#pragma once

#include "All.h"
#include "Input/Input.h"
#include "StageMain.h"
#include "Effect.h"
#include "Component.h"

#define FRONT 1
#define BACK -1

struct DelayTime
{
    int time;
    bool checker = false;
};

//キャラクター
class Character :public Component
{
public:
    // コンストラクタ
    Character() {}
    // デストラクタ
    virtual ~Character() {}

    // 開始処理
    virtual void Start() override;

    // 更新処理
    virtual void Update(float elapsedTime) override;
};