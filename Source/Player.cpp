#include <algorithm>
#include "Graphics/Graphics.h"
#include "Camera.h"
#include "Player.h"
#include "Input/Input.h"
#include "CameraController.h"
#include "Collision.h"

// コンストラクタ
Player::Player()
{
	current_health = max_health;
}

Player::~Player()
{
	delete enemy;
}

// 開始処理
void Player::Start()
{
	movement = GetActor()->GetComponent<Movement>();
	movement.get()->SetMoveSpeed(15.0f);
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
	//if (!ActorManager::Instance().GetNearActor(GetActor().get(), *enemy, ActorType::Enemy));
	enemy=ActorManager::Instance().GetNearActor(GetActor().get(),ActorType::Enemy);
	//Sphere pc = GetActor()->GetSphere();
 //   Sphere ec = enemy->GetSphere();
	//Collision::IntersectSphereVsSphere(pc, ec);
	//GetActor()->SetSphere(pc);
	//enemy->SetSphere(ec);


	Cylinder pc = GetActor()->GetCylinder();
	Cylinder ec = enemy->GetCylinder();
	Collision::IntersectCylinderVsCylinder(pc, ec);
	GetActor()->SetCylinder(pc);
	enemy->SetCylinder(ec);
}

void Player::DrawImGui()
{
	Character::DrawImGui();
	ImGui::Text(u8"NearEnemy:%s", enemy->GetName().c_str());
}

void Player::DrawDebug()
{
	// デバッグ球描画
	DirectX::XMFLOAT3 position = GetActor()->GetPosition();
	float radius = GetActor()->GetRadius();
	float height = GetActor()->GetHeight();
	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
	Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
	//衝突判定用のデバッグ円柱を描画
	Graphics::Instance().GetDebugRenderer()->DrawCylinder(position, radius, height, color);
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
		Camera* camera = ActorManager::Instance().GetActor("MainCamera")->GetComponent<Camera>().get();
		const DirectX::XMFLOAT3& cameraRight = camera->GetRight();
		const DirectX::XMFLOAT3& cameraFront = camera->GetFront();

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
	CameraController camera_c;
	//camera_c.Update(GetActor()->GetPosition());
	//camera_c.UpdateKey(elapsedTime, GetActor().get()->GetPosition());
}
