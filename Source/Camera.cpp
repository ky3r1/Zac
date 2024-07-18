#include <imgui.h>
#include "Camera.h"

Camera::Camera()
{
	// �J�����ݒ�
	SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),	// ��p
		1280.0f / 720.0f,					// ��ʃA�X�y�N�g��
		0.1f,								// �j�A�N���b�v
		1000.0f								// �t�@�[�N���b�v
	);
	SetLookAt(
		{ 0, 0, -5 },		// ���_
		{ 0, 0, 0 },		// �����_
		{ 0, 1, 0 }			// ��x�N�g��
	);
}

//�w�����������
void Camera::SetLookAt(const DirectX::XMFLOAT3& eye, const DirectX::XMFLOAT3& focus, const
    DirectX::XMFLOAT3& up)
{
	// ���_�A�����_�A���������r���[�s����쐬
	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);
	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	DirectX::XMStoreFloat4x4(&view, View);

	// �r���[���t�s�񉻂��A���[���h�s��ɖ߂�
	DirectX::XMMATRIX World = DirectX::XMMatrixInverse(nullptr, View);
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, World);

	// �J�����̕��������o��
	this->right.x = world._11;
	this->right.y = world._12;
	this->right.z = world._13;

	this->up.x = world._21;
	this->up.y = world._22;
	this->up.z = world._23;

	this->front.x = world._31;
	this->front.y = world._32;
	this->front.z = world._33;

	// ���_�A�����_��ۑ�
	this->eye = eye;
	this->focus = focus;
}

//�p�[�X�y�N�e�B�u�ݒ�
void Camera::SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ)
{
	// ��p�A��ʔ䗦�A�N���b�v��������v���W�F�N�V�����s����쐬
	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, nearZ, farZ);
	DirectX::XMStoreFloat4x4(&projection, Projection);
}

void CameraManager::DrawImGui()
{
	ImGui::SetNextWindowPos(ImVec2(950, 50), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	DirectX::XMFLOAT3 eye = mainCamera.GetEye();
    DirectX::XMFLOAT3 focus = mainCamera.GetFocus();
    DirectX::XMFLOAT3 up = mainCamera.GetUp();
	DirectX::XMFLOAT3 right = mainCamera.GetRight();
	DirectX::XMFLOAT3 front = mainCamera.GetFront();
	//DirectX::XMFLOAT3 distance = mainCamera.GetDistance();

	if (ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_None))
	{
		// �g�����X�t�H�[��
		if (ImGui::CollapsingHeader("MainCamera", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputFloat3("Eye", &eye.x);
			ImGui::InputFloat3("Focus", &focus.x);
			ImGui::InputFloat3("Up", &up.x);
			ImGui::InputFloat3("Right", &right.x);
			ImGui::InputFloat3("Front", &front.x);
		}
	}
	ImGui::End();
}
