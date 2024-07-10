#include "MouseManager.h"

void MouseManager::MouseTransform(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{
    //ビューポート
    D3D11_VIEWPORT viewport;
    UINT numViewports = 1;
    dc->RSGetViewports(&numViewports, &viewport);

    //変換行列
    DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
    DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
    DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();


    //エネミー配置処理
    GamePad& gamePad = Input::Instance().GetGamePad();
    Mouse& mouse = Input::Instance().GetMouse();
    /*if (gamePad.GetButtonDown() & GamePad::BTN_A)
    {*/
    //マウスカーソル座標取得
    DirectX::XMFLOAT3 screenPosition;
    screenPosition.x = static_cast<float>(mouse.GetPositionX());
    screenPosition.y = 0;
    screenPosition.z = static_cast<float>(mouse.GetPositionY());

    screen_mouse_position = screenPosition;

    DirectX::XMVECTOR ScreenCursor = DirectX::XMLoadFloat3(&screenPosition);

    DirectX::XMVECTOR WorldPosition = DirectX::XMVector3Unproject
    (
        ScreenCursor,
        viewport.TopLeftX,
        viewport.TopLeftY,
        viewport.Width,
        viewport.Height,
        viewport.MinDepth,
        viewport.MaxDepth,
        Projection,
        View,
        World
    );
    DirectX::XMFLOAT3 world_position_start;
    DirectX::XMStoreFloat3(&world_position_start, WorldPosition);

    world_mouse_position = world_position_start;
}

void MouseManager::DrawDebugGUI()
{
    if (ImGui::Begin("Mouse", nullptr, ImGuiWindowFlags_None))
    {
        if (ImGui::TreeNode("Position"))
        {
            //ImGui::SliderFloat("positionX", Input::Instance().GetMouse().GetPositionX(),100,100)
            ImGui::TreePop();
        }
    }
    ImGui::End();
}
