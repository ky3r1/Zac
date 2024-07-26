#include "AiComponent.h"

AiComponent::AiComponent()
{
}

AiComponent::~AiComponent()
{
}

void AiComponent::DrawImGui()
{
}

void AiComponent::Start()
{
}

void AiComponent::Update(float elapsedTime)
{
}

void AiComponent::DrawDebug()
{
    {
        //DebugRenderer::DrawCube()
        for (float x = 0; x < 35; x++)
        {
            for(float z=0;z<35;z++)
            {
                //衝突判定用のデバッグ円柱を描画
                Graphics::Instance().GetDebugRenderer()->DrawCube({-350+10*x,0,10*z}, { -350 + 10 * x,0,10}, {1,0,0,1});
            }
        }
    }
}
