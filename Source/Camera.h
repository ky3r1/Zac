#pragma once

#include "All.h"
#include "Component.h"

//�J����
class Camera : public Component
{
public:
    //�R���X�g���N�^
    Camera();

    //���O�擾
    virtual const char* GetName() const override { return "Camera"; }

    //�w�����������
    void SetLookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT3& up);

    //�p�[�X�y�N�e�B�u�ݒ�
    void SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ);

    //�r���[�s��擾
    const DirectX::XMFLOAT4X4& GetView() const { return view; }

    //�v���W�F�N�V�����s��擾
    const DirectX::XMFLOAT4X4& GetProjection() const { return projection; }

    //���_�擾
    const DirectX::XMFLOAT3& GetEye() const { return eye; }

    //�����_�擾
    const DirectX::XMFLOAT3& GetFocus() const { return focus; }

    //������擾
    const DirectX::XMFLOAT3& GetUp() const { return up; }

    //�O�����擾
    const DirectX::XMFLOAT3& GetFront() const { return front; }

    //�E�����擾
    const DirectX::XMFLOAT3& GetRight() const { return right; }

    //Imgui�`��
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