#pragma once

#include "Graphics/Shader.h"
#include "Collision.h"
#include "Component.h"

//ステージ
class Stage: public Component
{
public:
    // GUI描画
    virtual void DrawImGui() override;
protected:
};