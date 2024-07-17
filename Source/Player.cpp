#include <algorithm>
#include "Graphics/Graphics.h"
#include "Camera.h"
#include "Player.h"
#include "Input/Input.h"

// コンストラクタ
Player::Player()
{
}

Player::~Player()
{
}

// 開始処理
void Player::Start()
{
	movement = GetActor()->GetComponent<Movement>();

	// 適当にモーション再生
	Model* model = GetActor()->GetModel();
	if (model != nullptr)
	{
		model->PlayAnimation(20, true);
	}
}

// 更新
void Player::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	gamePad.Update();

	CameraControl(elapsedTime);
	CharacterControl(elapsedTime);

	// デバッグ球描画
	DirectX::XMFLOAT3 position = GetActor()->GetPosition();
	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
	Graphics::Instance().GetDebugRenderer()->DrawSphere(position, 3.0f, color);
}

// キャラクター操作
void Player::CharacterControl(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	float lengthSq = ax * ax + ay * ay;
	if (lengthSq > 0.1f)
	{
		Camera& camera = CameraManager::Instance().GetMainCamera();
		const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
		const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

		DirectX::XMFLOAT3 direction;
		direction.x = (cameraRight.x * ax) + (cameraFront.x * ay);
		direction.y = 0.0f;
		direction.z = (cameraRight.z * ax) + (cameraFront.z * ay);

		float length = sqrtf(direction.x * direction.x + direction.z * direction.z);
		direction.x /= length;
		direction.z /= length;

#if 1
		movement->Turn(direction, elapsedTime);
		movement->Move(direction, elapsedTime);
#else
		// オイラーで制御する場合
		std::shared_ptr<Actor>& actor = GetActor();

		// 移動
		float moveSpeed = 5.0f * elapsedTime;
		float vx = sinf(angle.y);
		float vz = cosf(angle.y);
		DirectX::XMFLOAT3 position = actor->GetPosition();
		position.x += vx * moveSpeed;
		position.z += vz * moveSpeed;
		actor->SetPosition(position);

		// 内積を使って回転量を計算する
		float turnSpeed = 6.28f * elapsedTime;
		float dot = (vx * direction.x) + (vz * direction.z);
		float rot = (1.0f - dot);
		if (rot > turnSpeed) rot = turnSpeed;

		// 外積で左右判定をしてＹ軸回転する
		float cross = (vx * direction.z) - (vz * direction.x);
		if (cross < 0.0f)
			angle.y += rot;
		else
			angle.y -= rot;

		// アクターに回転値を設定する
		DirectX::XMMATRIX M = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
		DirectX::XMVECTOR Q = DirectX::XMQuaternionRotationMatrix(M);
		DirectX::XMFLOAT4 rotation;
		DirectX::XMStoreFloat4(&rotation, Q);
		actor->SetRotation(rotation);
#endif
	}
}

// カメラ操作
void Player::CameraControl(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();

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
	DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&GetActor()->GetPosition());
	DirectX::XMVECTOR Focus = DirectX::XMVectorAdd(Target, Offset);
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(cameraAngle.x, cameraAngle.y, cameraAngle.z);
	DirectX::XMVECTOR Range = DirectX::XMVectorSet(0.0f, 0.0f, -cameraRange, 0.0f);
	DirectX::XMVECTOR Vec = DirectX::XMVector3TransformCoord(Range, Transform);
	DirectX::XMVECTOR Eye = DirectX::XMVectorAdd(Focus, Vec);

	DirectX::XMFLOAT3 eye, focus;
	DirectX::XMStoreFloat3(&eye, Eye);
	DirectX::XMStoreFloat3(&focus, Focus);

	Camera& camera = CameraManager::Instance().GetMainCamera();
	camera.SetLookAt(eye, focus, DirectX::XMFLOAT3(0, 1, 0));
}
