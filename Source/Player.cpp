#include <algorithm>
#include "Graphics/Graphics.h"
#include "Camera.h"
#include "Player.h"
#include "Input/Input.h"
#include "CameraController.h"
#include "Enemy.h"
#include "Mathf.h"


// コンストラクタ
Player::Player()
{
	current_health = max_health;
}

Player::~Player()
{
}

// 開始処理
void Player::Start()
{
	movement = GetActor()->GetComponent<Movement>();
	movement.get()->SetMoveSpeed(5.0f);
	vs_collision=GetActor()->GetComponent<VsCollision>();

	// 適当にモーション再生
	Model* model = GetActor()->GetModel();
	animation_state = Anim_Player_Spawn;

	//if (model != nullptr)
	//{
	//	model->PlayAnimation(Anim_Player_Spawn, false);
	//}
}

// 更新
void Player::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	//gamePad.Update();
	CharacterControl(elapsedTime);
	Actor* enemy = nullptr;
	//プレイヤーとエネミーの当たり判定
	if (vs_collision->CylinderVsCylinder(ActorType::Enemy, &enemy))
	{
		if (unbeatable_delay.checker)
		{
			//TakeDamage(1.0f);
			{
				DirectX::XMFLOAT3 impulse;
				//吹き飛ばす力
				const float power = 10.0f;
				DirectX::XMVECTOR Enemy_Position = DirectX::XMLoadFloat3(&enemy->GetPosition());
				DirectX::XMVECTOR Player_Position = DirectX::XMLoadFloat3(&GetActor()->GetPosition());
				DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Player_Position, Enemy_Position);
				Vec = DirectX::XMVector3Normalize(Vec);
				DirectX::XMFLOAT3 vec;
				DirectX::XMStoreFloat3(&vec, Vec);
				impulse.x = vec.x * power;
				impulse.y = vec.y * power;
				impulse.z = vec.z * power;
				movement->AddImpulse(vec);
			}

			unbeatable_delay.checker = false;
		}
	}
	//Jump
	if (gamePad.GetButtonDown() & GamePad::BTN_X)
	{
		movement->Jump(5.0f);
	}
	Character::Update(elapsedTime);
}

void Player::DrawImGui()
{
	Character::DrawImGui();
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
	DirectX::XMFLOAT3 move_vec=GetMoveVec();
	{
#if 1
		movement->Turn(elapsedTime,move_vec.x, move_vec.z);
		movement->Move(move_vec);
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

DirectX::XMFLOAT3 Player::GetMoveVec()
{
	static DirectX::XMFLOAT3 old_position = GetActor()->GetPosition();
	//入力情報の取得
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	//カメラ方向とスティックの入力によって進行方向を計算する
	Camera* camera = ActorManager::Instance().GetActor("MainCamera")->GetComponent<Camera>().get();
	const DirectX::XMFLOAT3& cameraRight = camera->GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera->GetFront();

	//移動ベクトルはXY平面に水平なベクトルになるようにする

	//カメラ右方向ベクトルをXZ単位ベクトルに変換
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	if (cameraRightLength > 0.0f)
	{
		//単位ベクトル化
		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;
	}

	//カメラ前方向ベクトルをXZ単位ベクトルに変換
	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX  + cameraFrontZ * cameraFrontZ);
	if (cameraFrontLength > 0.0f)
	{
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
	}

	//スティックの水平入力値をカメラの右方向に反映し、
	//スティックの垂直入力値をカメラの前方向に反映し、
	//進行ベクトルを計算する
	DirectX::XMFLOAT3 vec;
	vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
	vec.y = 0;
	vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);
	

	//{
	//	DirectX::XMFLOAT3 rotation = { GetActor()->GetRotation().x,GetActor()->GetRotation().y,GetActor()->GetRotation().z };
	//	DirectX::XMVECTOR Normal = DirectX::XMLoadFloat3(&GetActor()->GetComponent<Movement>()->GetNormal());
	//	DirectX::XMFLOAT3 normal = GetActor()->GetComponent<Movement>()->GetNormal();
	//	DirectX::XMVECTOR Vec = DirectX::XMLoadFloat3(&vec);
	//	DirectX::XMVECTOR parallelDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(Vec, DirectX::XMVectorScale(Normal, DirectX::XMVectorGetX(DirectX::XMVector3Dot(Vec, Normal)))));
	//	//DirectX::XMStoreFloat3(&vec, parallelDirection);

	//	if (vec.x < 0)normal = DirectX::XMFLOAT3(normal.x*1.0f, normal.y*1.0f, normal.z*1.0f);
	//	float sub = GetActor()->GetPosition().y - old_position.x;
	//	if(sub)
	//	//float VdotN=Mathf::Dot(normal, vec);
	//	//normal.x *= VdotN;
	//	//normal.y *= VdotN;
	//	//normal.z *= VdotN;
	//	//vec.x -= normal.x;
	//	//vec.y -= normal.y;
	//	//vec.z -= normal.z;
	//}
	//GetActor()->SetPosition(old_position);

	return vec;
}