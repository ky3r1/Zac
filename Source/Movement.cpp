#include "Movement.h"
#include "Mathf.h"

#define MAX_GRAVITY 1.0f

//Velocityの最大値(移動ベクトルに掛けるため0になる場合があるので下の数値アリ)
#define MAX_VELOCITY_X 7.00f
#define MAX_VELOCITY_Y 7.00f
#define MAX_VELOCITY_Z 7.00f
//Velocityの最低限の最大値
#define MAX_MINI_VELOCITY_X 0.00f
#define MAX_MINI_VELOCITY_Y 0.00f
#define MAX_MINI_VELOCITY_Z 0.00f

//Velocity最大値の有効化
#define VLOCITY_MAX_FLG_X
//#define VLOCITY_MAX_FLG_Y
#define VLOCITY_MAX_FLG_Z
//Velocity最小値の有効化
#define VLOCITY_MIN_FLG_X
#define VLOCITY_MIN_FLG_Y
#define VLOCITY_MIN_FLG_Z
Movement::Movement()
{
}

Movement::~Movement()
{
}

void Movement::DrawImGui()
{
    ImGui::InputFloat("MoveSpeed", &move_speed);
    ImGui::InputFloat("Friction", &friction);
	ImGui::InputFloat("Mass", &mass);
	ImGui::InputFloat3("Velocity", &velocity.x);
	ImGui::InputFloat3("Acceleration", &acceleration.x);
	ImGui::InputFloat3("Resultant", &resultant.x);
}

void Movement::DrawDebug()
{
	//Graphics::Instance().GetDebugRenderer()->DrawCube({ velocity.x,0,velocity.z }, { GetActor()->GetPosition() .x,0,GetActor()->GetPosition().z}, { 1,0,0,1 });
}

void Movement::Start()
{
}

void Movement::Update(float elapsedTime)
{
	DirectX::XMFLOAT3 pos=GetActor()->GetPosition();

	//スロープの傾斜
	if(false)
	{
		//傾斜率の計算
		float normalLengthXZ = sqrtf(normal.x* normal.x + normal.z * normal.z);
		slope_rate = 1.0 - (normal.y / (normalLengthXZ + normal.y));
		DirectX::XMFLOAT2 vel = { velocity.x, velocity.z };
		DirectX::XMVECTOR velVel = DirectX::XMLoadFloat2(&vel);
		float length = DirectX::XMVectorGetX(DirectX::XMVector2Length(velVel));
		//下り坂でガタガタしないようにする
		if (slope_rate > 0.0f)
		{
			velocity.y -= length * slope_rate * elapsedTime;
		}
	}



	//地面の向きに沿うようにXZ軸回転
	if(GetActor()->GetAttitudeControlFlag())
	{
		//Y軸が法線ベクトル方向に向くオイラー角回転を算出
		float X, Z;
		X = atan2f(normal.z, normal.y);
		Z = -atan2f(normal.x, normal.y);
		float rotation_X = Mathf::Lerp(GetActor()->GetRotation().x, X, 0.1f);
		float rotation_Z = Mathf::Lerp(GetActor()->GetRotation().z, Z, 0.1f);
		DirectX::XMFLOAT4 rotation = { rotation_X, GetActor()->GetRotation().y, rotation_Z, GetActor()->GetRotation().w };
		GetActor()->SetRotation(rotation);
	}
	//摩擦
	{

		{
			DirectX::XMVECTOR f = DirectX::XMLoadFloat3(&velocity);
			f=DirectX::XMVectorScale(f, -1);
			f = DirectX::XMVectorAdd(DirectX::XMVectorScale(f, friction), DirectX::XMLoadFloat3(&velocity));
			DirectX::XMStoreFloat3(&velocity, f);
		}
	}
	//速度更新
	{

		assert(mass > 0);

		DirectX::XMStoreFloat3(&acceleration, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&resultant), 1 / mass));
		DirectX::XMStoreFloat3(&velocity, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&velocity), DirectX::XMVectorScale(DirectX::XMLoadFloat3(&acceleration), elapsedTime)));
		DirectX::XMStoreFloat3(&pos, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&pos), DirectX::XMVectorScale(DirectX::XMLoadFloat3(&velocity), elapsedTime)));
		GetActor()->SetPosition(pos);
		resultant = {};
	}
}
void Movement::Move(DirectX::XMFLOAT3 v)
{
	//if (!Mathf::Equal(v, { 0.0f,0.0f,0.0f }))
	{
		//移動方向ベクトル
		{
			AddForce({v.x*move_speed,v.y*move_speed,v.z*move_speed});
		}
	}
}


void Movement::MoveTarget(DirectX::XMFLOAT3 tp, float elapsedTime)
{
	DirectX::XMFLOAT3 vec = {};
	DirectX::XMFLOAT3 zero = {};
	DirectX::XMVECTOR Vec = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&tp), DirectX::XMLoadFloat3(&GetActor()->GetPosition())));
	DirectX::XMStoreFloat3(&vec, Vec);
	Turn(elapsedTime, vec);
	Move(vec);
}

void Movement::Turn(float elapsedTime, DirectX::XMFLOAT3 v)
{
	std::shared_ptr<Actor> actor = GetActor();
	float speed = turnSpeed;
	speed *= elapsedTime;
	//Mathf::Lerp();

	//進行ベクトルがゼロベクトルの場合は処理する必要なし
	float length = sqrtf(v.x * v.x + v.z * v.z);
	if (length < 0.0001f) return;

	//進行ベクトルを単位ベクトル化
	v.x /= length;
	v.z /= length;


	//自身の回転値から前方向を求める
	float frontX = sinf(actor->GetRotation().y);
	float frontZ = cosf(actor->GetRotation().y);

	//回転角を求めるため、2つの単位ベクトルの内積を計算する
	float dot = (v.x * frontX) + (v.z * frontZ);

	//内積値は-1.0～1.0で表現されており、2つの単位ベクトルの角度が
	// 小さいほど1.0に近づくという性質を利用して回転速度を調整する
	float rot = 1.0 - dot;
	if (rot > speed) { rot = speed; }
	//speed *= rot;
	//左右判定を行うために2つの単位ベクトルの外積を計算する
	float cross = (v.z * frontX) - (v.x * frontZ);

	//2Dの外積値が正の場合か負の場合によって左右判定が行える
	//左右判定を行うことによって左右回転を選択する

	if (cross < 0.0f)
	{
		float angle_y= actor->GetRotation().y;
        angle_y += rot;
		actor->SetRotation({ actor->GetRotation().x, angle_y, actor->GetRotation().z, actor->GetRotation().w });
	}
	else
	{
		float angle_y = actor->GetRotation().y;
		angle_y -= rot;
		actor->SetRotation({ actor->GetRotation().x, angle_y, actor->GetRotation().z, actor->GetRotation().w });
	}
}

void Movement::Jump(float jump_power)
{
	velocity.y += jump_power;
}

void Movement::AddForce(const DirectX::XMFLOAT3& impulse)
{
	resultant.x += impulse.x;
	resultant.y += impulse.y;
	resultant.z += impulse.z;
}

void Movement::ResetVelocity()
{
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
}
