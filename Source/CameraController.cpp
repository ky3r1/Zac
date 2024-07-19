#include <imgui.h>
#include "CameraController.h"
#include "Input/Input.h"

#define MAXANGLE_X 3.14f * 0.5f-0.01f
#define MINANGLE_X 0.1f

// �J��������R���g���[���[�փp�����[�^�𓯊�����
void CameraController::SyncCameraToController(const Camera& camera)
{
	//eye = camera.GetEye();
	//focus = camera.GetFocus();
	//up = camera.GetUp();
	//right = camera.GetRight();

	//// ���_���璍���_�܂ł̋������Z�o
	//DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	//DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	//DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Focus, Eye);
	//DirectX::XMVECTOR Distance = DirectX::XMVector3Length(Vec);
	//DirectX::XMStoreFloat(&distance, Distance);

	//// ��]�p�x���Z�o
	//const DirectX::XMFLOAT3& front = camera.GetFront();
	//angle.x = ::asinf(-front.y);
	//if (up.y < 0)
	//{
	//	if (front.y > 0)
	//	{
	//		angle.x = -DirectX::XM_PI - angle.x;
	//	}
	//	else
	//	{
	//		angle.x = DirectX::XM_PI - angle.x;
	//	}
	//	angle.y = ::atan2f(front.x, front.z);
	//}
	//else
	//{
	//	angle.y = ::atan2f(-front.x, -front.z);
	//}
}

// �R���g���[���[����J�����փp�����[�^�𓯊�����
void CameraController::SyncControllerToCamera(Camera& camera)
{
	//camera.SetLookAt(eye, focus, up);
}

// �X�V����
void CameraController::Update(DirectX::XMFLOAT3 target, Camera& camera)
{
	// �f�o�b�O�E�C���h�E���쒆�͏������Ȃ�
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
	{
		return;
	}

	// IMGUI�̃}�E�X���͒l���g���ăJ�������삷��
	ImGuiIO io = ImGui::GetIO();

	// �}�E�X�J�[�\���̈ړ��ʂ����߂�
	float moveX = io.MouseDelta.x * 0.02f;
	float moveY = io.MouseDelta.y * 0.02f;

	// �}�E�X���{�^��������
	if (io.MouseDown[ImGuiMouseButton_Right])
	{
		// Y����]
		angle.y += moveX * 0.5f;
		if (angle.y > DirectX::XM_PI)
		{
			angle.y -= DirectX::XM_2PI;
		}
		else if (angle.y < -DirectX::XM_PI)
		{
			angle.y += DirectX::XM_2PI;
		}
		// X����]
		angle.x += moveY * 0.5f;
		if (angle.x > DirectX::XM_PI)
		{
			angle.x -= DirectX::XM_2PI;
		}
		else if (angle.x < -DirectX::XM_PI)
		{
			angle.x += DirectX::XM_2PI;
		}
	}
	// �}�E�X���{�^��������
	else if (io.MouseDown[ImGuiMouseButton_Middle])
	{
		// ���s�ړ�
		float s = distance * 0.035f;
		float x = moveX * s;
		float y = moveY * s;

		focus.x -= right.x * x;
		focus.y -= right.y * x;
		focus.z -= right.z * x;

		focus.x += up.x * y;
		focus.y += up.y * y;
		focus.z += up.z * y;
	}
	// �}�E�X�E�{�^��������
	else if (io.MouseDown[ImGuiMouseButton_Left] && io.MouseDown[ImGuiMouseButton_Right])
	{
		// �Y�[��
		distance += (-moveY - moveX) * distance * 0.1f;
	}
	// �}�E�X�z�C�[��
	else if (io.MouseWheel != 0)
	{
		// �Y�[��
		distance -= io.MouseWheel * distance * 0.1f;
	}

	float sx = ::sinf(angle.x);
	float cx = ::cosf(angle.x);
	float sy = ::sinf(angle.y);
	float cy = ::cosf(angle.y);

	// �J�����̕������Z�o
	DirectX::XMVECTOR Front = DirectX::XMVectorSet(-cx * sy, -sx, -cx * cy, 0.0f);
	DirectX::XMVECTOR Right = DirectX::XMVectorSet(cy, 0, -sy, 0.0f);
	DirectX::XMVECTOR Up = DirectX::XMVector3Cross(Right, Front);
	// �J�����̎��_�������_���Z�o
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR Distance = DirectX::XMVectorSet(distance, distance, distance, 0.0f);
	DirectX::XMVECTOR Eye = DirectX::XMVectorSubtract(Focus, DirectX::XMVectorMultiply(Front, Distance));
	// �r���[�s�񂩂烏�[���h�s����Z�o
	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	DirectX::XMMATRIX World = DirectX::XMMatrixTranspose(View);
	// ���[���h�s�񂩂�������Z�o
	Right = DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(1, 0, 0, 0), World);
	Up = DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(0, 1, 0, 0), World);

	// ���ʂ��i�[
	DirectX::XMFLOAT4X4 view, projection;
    DirectX::XMStoreFloat4x4(&view, View);
    DirectX::XMStoreFloat4x4(&projection, World);
	DirectX::XMStoreFloat3(&eye, Eye);
	DirectX::XMStoreFloat3(&up, Up);
	DirectX::XMStoreFloat3(&right, Right);

	//��]�s�񂩂�O�����x�N�g�������o��
	Front = World.r[2];
	DirectX::XMFLOAT3 front;
	DirectX::XMStoreFloat3(&front, Front);

	//�����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
	//DirectX::XMFLOAT3 eye;
	eye.x = target.x - front.x * distance / 1.0f;
	eye.y = target.y - front.y * distance / 1.0f;
	eye.z = target.z - front.z * distance / 1.0f;

	//�J�����̎��_�ƒ����_��ݒ�
	//CameraManager::Instance().GetMainCamera().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
	camera.SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::UpdateKey(float elapsedTime, DirectX::XMFLOAT3 target, Camera& camera)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();

	DirectX::XMFLOAT3	angle = DirectX::XMFLOAT3(0, 0, 0);

	static DirectX::XMFLOAT3	cameraAngle = DirectX::XMFLOAT3(0, 0, 0);
	static float				cameraRollSpeed = DirectX::XMConvertToRadians(90);
	static float				cameraMaxPitch = DirectX::XMConvertToRadians(45);
	static float				cameraMinPitch = DirectX::XMConvertToRadians(-45);
	static float				cameraRange = 100.0f;
	static 	float				characterHeight = 10.0f;
	float lengthSq = ax * ax + ay * ay;
	if (lengthSq > 0.1f)
	{
		float speed = cameraRollSpeed * elapsedTime;

		cameraAngle.x += ay * speed;
		cameraAngle.y += ax * speed;

		if (cameraAngle.x < cameraMinPitch)
		{
			cameraAngle.x = cameraMinPitch;
		}
		if (cameraAngle.x > cameraMaxPitch)
		{
			cameraAngle.x = cameraMaxPitch;
		}
		if (cameraAngle.y < -DirectX::XM_PI)
		{
			cameraAngle.y += DirectX::XM_2PI;
		}
		if (cameraAngle.y > DirectX::XM_PI)
		{
			cameraAngle.y -= DirectX::XM_2PI;
		}
	}

	DirectX::XMVECTOR Offset = DirectX::XMVectorSet(0.0f, characterHeight, 0.0f, 0.0f);
	DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR Focus = DirectX::XMVectorAdd(Target, Offset);
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(cameraAngle.x, cameraAngle.y, cameraAngle.z);
	DirectX::XMVECTOR Range = DirectX::XMVectorSet(0.0f, 0.0f, -cameraRange, 0.0f);
	DirectX::XMVECTOR Vec = DirectX::XMVector3TransformCoord(Range, Transform);
	DirectX::XMVECTOR Eye = DirectX::XMVectorAdd(Focus, Vec);

	DirectX::XMFLOAT3 eye, focus;
	DirectX::XMStoreFloat3(&eye, Eye);
	DirectX::XMStoreFloat3(&focus, Focus);
	//Camera* camera = ActorManager::Instance().GetActor("MainCamera")->GetComponent<Camera>().get();
	camera.SetLookAt(eye, focus, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::DrawDebugGUI()
{
	//if (ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_None))
	//{
	//	if (ImGui::CollapsingHeader("CameraController", ImGuiTreeNodeFlags_DefaultOpen))
	//	{	
	//		ImGui::InputFloat3("Eye", &eye.x);
	//		ImGui::InputFloat3("Focus", &focus.x);
	//		ImGui::SliderFloat3("Up", &up.x, -1, 1);
	//		ImGui::SliderFloat3("Right", &right.x, -1, 1);
	//		ImGui::SliderFloat("Distance", &distance, 0, 100);
	//		ImGui::SliderFloat3("angle", &angle.x, -3.14f, 3.14f * 0.5f);
	//	}
	//}
	//ImGui::End();
}
