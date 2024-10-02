#pragma once

#include "All.h"
#include "Component.h"

//カメラ
class Camera : public Component
{
public:
    //コンストラクタ
    Camera();

    //名前取得
    virtual const char* GetName() const override { return "Camera"; }

    //指定方向を向く
    void SetLookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up);

    //パースペクティブ設定
    void SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ);

    //ビュー行列取得
    const DirectX::XMFLOAT4X4& GetView() const { return view; }

    //プロジェクション行列取得
    const DirectX::XMFLOAT4X4& GetProjection() const { return projection; }

    //視点取得
    const DirectX::XMFLOAT3& GetEye() const { return eye; }

    //注視点取得
    const DirectX::XMFLOAT3& GetFocus() const { return focus; }

    //上方向取得
    const DirectX::XMFLOAT3& GetUp() const { return up; }

    //前方向取得
    const DirectX::XMFLOAT3& GetFront() const { return front; }

    //右方向取得
    const DirectX::XMFLOAT3& GetRight() const { return right; }

    //Imgui描画
    void DrawImGui() override;
public:
    void SetCameraShake(bool camera_shake) 
    {
        this->camera_shake = camera_shake; 
        this->shake_time = 1.0f;
        this->shake_range = 0.3f;
    }
    void SetCameraShake(bool camera_shake,float shake_time, float shake_range)
    {
        this->camera_shake = camera_shake; 
        this->shake_time = shake_time;
        this->shake_range = shake_range;
    }
    bool GetCameraShake() { return camera_shake; }
    float GetShakeTime() { return shake_time; }
    float GetShakeRange() { return shake_range; }


private:
    DirectX::XMFLOAT4X4     view;
    DirectX::XMFLOAT4X4     projection;

    DirectX::XMFLOAT3       eye;
    DirectX::XMFLOAT3       focus;

    DirectX::XMFLOAT3       up;
    DirectX::XMFLOAT3       front;
    DirectX::XMFLOAT3       right;

    bool camera_shake = false;
    float shake_time = 1.0f;
    float shake_range = 0.3f;
};