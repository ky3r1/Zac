#pragma once

#include "All.h"
#include "Camera.h"

class CameraController
{
public:
	// �J��������R���g���[���[�փp�����[�^�𓯊�����
	void SyncCameraToController(const Camera& camera);

	// �R���g���[���[����J�����փp�����[�^�𓯊�����
	void SyncControllerToCamera(Camera& camera);

	// �X�V����
	void Update(DirectX::XMFLOAT3 target);

	// �X�V����
	void UpdateKey(float elapsedTime,DirectX::XMFLOAT3 target);

	//�f�o�b�O�pImgui�\��
	void DrawDebugGUI();
private:
	DirectX::XMFLOAT3		eye;
	DirectX::XMFLOAT3		focus;
	DirectX::XMFLOAT3		up;
	DirectX::XMFLOAT3		right;
	float					distance;
	DirectX::XMFLOAT3		angle;
};