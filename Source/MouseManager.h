#pragma once
#include "All.h"
#include "Input/Input.h"
//#include"StageMain.h"


class MouseManager
{
public:
    void MouseTransform(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection);
    static MouseManager& GetInstance() {
        static MouseManager instance;
        return instance;
    }

    DirectX::XMFLOAT3& GetWorldMousePos() { return world_mouse_position; }

    DirectX::XMFLOAT3& GetScreenMousePos() { return screen_mouse_position; }

    void DrawDebugGUI();

private:
    GamePad& gamePad = Input::Instance().GetGamePad();
    Mouse& mouse = Input::Instance().GetMouse();
    DirectX::XMFLOAT3 world_mouse_position = { 0.0f,0.0f,0.0f };
    DirectX::XMFLOAT3 screen_mouse_position = { 0.0f,0.0f,0.0f };
};