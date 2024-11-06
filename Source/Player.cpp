#include "Player.h"

#include "Character.h"

#include "Movement.h"
#include "VsCollision.h"
#include "Gravity.h"

#include "CollisionObject.h"
#include "FrontObject.h"
#include "TimeDeleteObject.h"

#include <algorithm>
#include "Graphics/Graphics.h"
#include "Camera.h"

#include "Input/Input.h"
#include "CameraController.h"
#include "Enemy.h"
#include "Mathf.h"


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
	GetActor()->AddComponent<Gravity>();
	GetActor()->GetComponent<Gravity>()->SetSpeed(1.0f);
	GetActor()->AddComponent<Movement>();
	Movement* movement = GetActor()->GetComponent<Movement>().get();
	movement->SetMass(1.0f);
	GetActor()->AddComponent<VsCollision>();
	GetActor()->AddComponent<Character>();
	GetActor()->GetComponent<Character>()->SetHealth(GetActor()->GetComponent<Character>()->GetMaxHealth());
	//GetActor()->GetComponent<Movement>()->SetMoveSpeed(5.0f);
	GetActor()->SetAttitudeControlFlag(true);
	GetActor()->GetModel()->PlayAnimation(Animation::Anim_idle, true, 1.0f);
	//GetActor()->AddComponent<Gravity>();
	//GetActor()->GetComponent<Gravity>()->SetSpeed(1.0f);
}

// 更新
void Player::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	//gamePad.Update();
	{
		CharacterControl(elapsedTime);
	}

	//Jump
	if (gamePad.GetButtonDown() & GamePad::BTN_B)
	{
		GetActor()->GetComponent<Gravity>()->Jump(jumpPower);
	}
	if (gamePad.GetButton() & GamePad::BTN_X)
	{
		//GetActor()->GetModel()->SetAnimationSpeed(0.0f);
		const char* filename = "Data/Model/Cube/Cube.mdl";
		std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		std::string name = std::string("TrackingObject:") + std::string(GetActor()->GetName());
		actor->LoadModel(filename);
		actor->SetName(name);
		DirectX::XMFLOAT3 position = GetActor()->GetPosition();
		actor->SetPosition({ position.x, position.y+GetActor()->GetHeight()*0.5f    , position.z});
		actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
		actor->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
		actor->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 0.5f));
		actor->SetRadius(3.0f);
		actor->SetActorType(ActorType::Bullet);
		actor->AddComponent<VsCollision>();
		actor->AddComponent<Movement>();

		actor->AddComponent<CollisionObject>();
		CollisionObject* collisionObject = actor->GetComponent<CollisionObject>().get();
		collisionObject->SetTargetActorType(ActorType::Enemy);
		collisionObject->SetHitCollisionType(HitCollisionType::Damage);
		collisionObject->SetHitNum(1.0f);

		actor->AddComponent<FrontObject>();
		FrontObject* frontObject = actor->GetComponent<FrontObject>().get();
		frontObject->SetForward({ GetActor()->GetTransform()._31,GetActor()->GetTransform()._32,GetActor()->GetTransform()._33 });
		frontObject->SetPower(1000.0f);

		actor->AddComponent<TimeDeleteObject>();
		actor->GetComponent<TimeDeleteObject>()->SetDeleteTime(0.5f);
	}
	Actor* enemy = nullptr;
	//プレイヤーとエネミーの当たり判定
	if (GetActor()->GetComponent<VsCollision>()->CylinderVsCylinderPushing(ActorType::Enemy, &enemy))
	{
		if(GetActor()->GetComponent<Character>()->GetUndeatableDelay().checker)
		{
			ActorManager::Instance().GetActor("MainCamera")->GetComponent<Camera>()->SetCameraShake(true);
			GetActor()->GetComponent<Character>()->TakeDamage(1.0f);
		}
		GetActor()->GetComponent<Character>()->SetUndeatableDelay();
	}
	//GetActor()->SetRayPosition({
	//	GetActor()->GetModel()->FindNode("Character1_Hips")->worldTransform._41,
	//	GetActor()->GetModel()->FindNode("Character1_Hips")->worldTransform._42,
	//	GetActor()->GetModel()->FindNode("Character1_Hips")->worldTransform._43 });
}

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	//DirectX::XMFLOAT4X4 hand_transform = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	//DirectX::XMFLOAT3 actor_position = GetActor()->GetPosition();
	//DirectX::XMFLOAT3 actor_scale = GetActor()->GetScale();
	//DirectX::XMFLOAT3 actor_rotation = {GetActor()->GetRotation().x,GetActor()->GetRotation().y,GetActor()->GetRotation().z};
	//DirectX::XMFLOAT3 offset = { GetActor()->GetFront().x + 0.9f,GetActor()->GetFront().y + GetActor()->GetHeight() * 0.90f+0.5f,GetActor()->GetFront().z + 5.0f };
	//DirectX::XMFLOAT3 position = Mathf::Add(actor_position, offset);
	//DirectX::XMFLOAT3 scale = { 0.1f,0.1f,0.1f };
	//DirectX::XMFLOAT3 rotation = Mathf::Add(actor_rotation, { 3.14f * 0.0f,3.14f * 0.95f ,3.14f * -0.05f });
	//Mathf::UpdateTransform(hand_transform,position,scale,rotation);
	////Gun.UpdateWorldTransform(hand_transform);
	////hand_transform=GetActor()->GetModel()->FindNode("mixamorig9:RightHand")->worldTransform;


	////hand_transform._11 = hand_transform._11 + 3.14 * 0.0f;
	////hand_transform._12 = hand_transform._12 + 3.14 * 0.0f;
	////hand_transform._13 = hand_transform._13 + 3.14 * 1.0f;
	////hand_transform._21 = hand_transform._21+3.14*0.0f;
 ////   hand_transform._22 = hand_transform._22+3.14*0.0f;
 ////   hand_transform._23 = hand_transform._23+3.14*0.0f;

	//Gun.UpdateWorldTransform(hand_transform);
	//shader->Draw(dc, &Gun, { 1,1,1,1 });
}

void Player::DrawImGui()
{
	//Character::DrawImGui();
	DirectX::XMFLOAT3 a=GetMoveVec();
	ImGui::InputFloat3("Move Vec", &a.x);
	ImGui::InputFloat("JumpPower", &jumpPower);
	int anim = GetActor()->GetModel()->GetCurrentAnimationNo();
	const char* anim_items[] = 
	{ 
		"Anim_shot_auto",
		"Anim_shot_semiauto",
		"Anim_reload",
		"Anim_idle",
		"Anim_jump",
		"Anim_run_front",
		"Anim_run_back",
		"Anim_run_left",
		"Anim_walk_left",
		"Anim_walk_right",
		"Anim_run_right",
		"Anim_throw",
		"Anim_aim_left",
		"Anim_aim_right",
		"Anim_aim_back",
		"Anim_aim_front",
		"None"
	};
	ImGui::Combo("Animation", &anim, anim_items, IM_ARRAYSIZE(anim_items));
	if(anim != GetActor()->GetModel()->GetCurrentAnimationNo())
    {
        GetActor()->GetModel()->PlayAnimation(anim, true, 1.0f);
    }
}

void Player::DrawDebug()
{
}

// キャラクター操作
void Player::CharacterControl(float elapsedTime)
{
	DirectX::XMFLOAT3 move_vec=GetMoveVec();
	{
#if 1
		GetActor()->GetComponent<Movement>()->Turn(elapsedTime, move_vec);
		GetActor()->GetComponent<Movement>()->Move(move_vec);
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

	return vec;
}