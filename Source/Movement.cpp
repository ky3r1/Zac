#include "Movement.h"
#include "Mathf.h"

#define MAX_GRAVITY 1.0f

//Velocityの最大値(移動ベクトルに掛けるため0になる場合があるので下の数値アリ)
#define MAX_VELOCITY_X 1.00f
#define MAX_VELOCITY_Y 1.00f
#define MAX_VELOCITY_Z 1.00f
//Velocityの最低限の最大値
#define MAX_MINI_VELOCITY_X 0.00f
#define MAX_MINI_VELOCITY_Y 0.00f
#define MAX_MINI_VELOCITY_Z 0.00f

//移動ベクトル入力時の最大値
#define MAX_VELOCITY_MOVE_X 0.50f
#define MAX_VELOCITY_MOVE_Y 0.50f
#define MAX_VELOCITY_MOVE_Z 0.50f

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
    ImGui::InputFloat("Move Speed", &moveSpeed);
    ImGui::InputFloat("Turn Speed", &turnSpeed);
	ImGui::InputFloat("Gravity", &gravity);
	ImGui::InputFloat3("Velocity", &velocity.x);
	ImGui::InputFloat3("Normal", &normal.x);
	ImGui::InputFloat3("Friction", &friction.x);
}

void Movement::Start()
{
	move_vec={7.5f,7.5f,7.5f};
}

void Movement::Update(float elapsedTime)
{
	DirectX::XMFLOAT3 pos=GetActor()->GetPosition();
	UpdateAxisX(elapsedTime);
	//AddImpulse({ 0.1f, 0.0f, 0.1f });
	UpdateAxisY(elapsedTime);
	UpdateAxisZ(elapsedTime);

	//スロープの傾斜
	{
		//傾斜率の計算
		float normalLengthXZ = sqrtf(normal.x* normal.x + normal.z * normal.z);
		slope_rate = 1.0 - (normal.y / (normalLengthXZ + normal.y));
		DirectX::XMFLOAT2 vel = { velocity.x, velocity.z };
		DirectX::XMVECTOR velVel = DirectX::XMLoadFloat2(&vel);
		float length = DirectX::XMVectorGetX(DirectX::XMVector2Length(velVel));
		//下り坂でガタガタしないようにする
		if (on_ground && slope_rate > 0.0f)
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

	

	pos = Mathf::Add(velocity, pos);
	//if(pos.y < 0.0f)pos.y = 0.0f;
	GetActor()->SetPosition(pos);
}
void Movement::Move(DirectX::XMFLOAT3 v)
{
	move_vec = { abs(v.x) ,abs(v.y) ,abs(v.z)  };
	DirectX::XMFLOAT3 mv = { v.x * moveSpeed ,v.y * moveSpeed ,v.z * moveSpeed };
	//移動方向ベクトル
	//velocity.x += v.x * moveSpeed*0.01f;
	//velocity.y += v.y * moveSpeed*0.01f;
	//velocity.z += v.z * moveSpeed*0.01f;

	//velocityの最大値
	{
		//velocityの最大値を超えないようにする
		{
			if (mv.x >  MAX_VELOCITY_MOVE_X * move_vec.x)mv.x =  MAX_VELOCITY_MOVE_X * move_vec.x;
			if (mv.x < -MAX_VELOCITY_MOVE_X * move_vec.x)mv.x = -MAX_VELOCITY_MOVE_X * move_vec.x;
		}
		{
			if (mv.y >	MAX_VELOCITY_MOVE_Y * move_vec.y)mv.y =  MAX_VELOCITY_MOVE_Y * move_vec.y;
			if (mv.y < -MAX_VELOCITY_MOVE_Y * move_vec.y)mv.y = -MAX_VELOCITY_MOVE_Y * move_vec.y;
		}
		{
			if (mv.z >  MAX_VELOCITY_MOVE_Z * move_vec.z)mv.z =  MAX_VELOCITY_MOVE_Z * move_vec.z;
			if (mv.z < -MAX_VELOCITY_MOVE_Z * move_vec.z)mv.z = -MAX_VELOCITY_MOVE_Z * move_vec.z;
		}
	}
	//移動方向ベクトル
    {
        velocity.x += mv.x;
        velocity.y += mv.y;
        velocity.z += mv.z;
    }
}

void Movement::MoveLocal(const DirectX::XMFLOAT3& direction, float elapsedTime)
{
	std::shared_ptr<Actor> actor = GetActor();
	float speed = moveSpeed * elapsedTime;
	DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);
	DirectX::XMVECTOR Velocity = DirectX::XMVectorScale(Direction, speed);
	DirectX::XMVECTOR Rotation = DirectX::XMLoadFloat4(&actor->GetRotation());
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationQuaternion(Rotation);
	DirectX::XMVECTOR Move = DirectX::XMVector3TransformNormal(Velocity, Transform);
	DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&actor->GetPosition());

	Position = DirectX::XMVectorAdd(Position, Move);

	DirectX::XMFLOAT3 position;
	DirectX::XMStoreFloat3(&position, Position);
	actor->SetPosition(position);
}

void Movement::Turn(float elapsedTime, float vx, float vz)
{
	std::shared_ptr<Actor> actor = GetActor();
	float speed = turnSpeed;
	speed *= elapsedTime;

	//進行ベクトルがゼロベクトルの場合は処理する必要なし
	float length = sqrtf(vx * vx + vz * vz);
	if (length < 0.0001f) return;

	//進行ベクトルを単位ベクトル化
	vx /= length;
	vz /= length;


	//自身の回転値から前方向を求める
	float frontX = sinf(actor->GetRotation().y);
	float frontZ = cosf(actor->GetRotation().y);

	//回転角を求めるため、2つの単位ベクトルの内積を計算する
	float dot = (vx * frontX) + (vz * frontZ);

	//内積値は-1.0～1.0で表現されており、2つの単位ベクトルの角度が
	// 小さいほど1.0に近づくという性質を利用して回転速度を調整する
	float rot = 1.0 - dot;
	if (rot > speed) { rot = speed; }
	//speed *= rot;
	//左右判定を行うために2つの単位ベクトルの外積を計算する
	float cross = (vz * frontX) - (vx * frontZ);

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
	on_ground = false;
}

void Movement::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
	velocity = Mathf::Add(velocity, impulse);
}

void Movement::ResetVelocity()
{
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
}

void Movement::ChangeVector(DirectX::XMFLOAT3& v, DirectX::XMFLOAT3& normal)
{
}

void Movement::UpdateAxisX(float elapsedTime)
{
#ifdef VLOCITY_MIN_FLG_X
	//velocity増減処理
	{
		if (velocity.x < 0.0f)
		{
			velocity.x = velocity.x + friction.x;
			if (velocity.x > 0.0f)velocity.x = 0.0f;
		}
		if (velocity.x > 0.0f)
		{
			velocity.x = velocity.x - friction.x;
			if (velocity.x < 0.0f)velocity.x = 0.0f;
		}
	}
#endif // VLOCITY_MIN_FLG_X

#ifdef VLOCITY_MAX_FLG_X
	//velocityの最大値
	{
		//velocityの最大値を超えないようにする
		{
			if (velocity.x >   MAX_MINI_VELOCITY_X + MAX_VELOCITY_X * (move_vec.x+1)) velocity.x =   MAX_MINI_VELOCITY_X + MAX_VELOCITY_X * (move_vec.x+1);
			if (velocity.x < -(MAX_MINI_VELOCITY_X + MAX_VELOCITY_X * (move_vec.x+1)))velocity.x = -(MAX_MINI_VELOCITY_X + MAX_VELOCITY_X * (move_vec.x+1));
			//if(velocity.x > MAX_VELOCITY_X) velocity.x = MAX_VELOCITY_X;
   //         if(velocity.x < -MAX_VELOCITY_X) velocity.x = -MAX_VELOCITY_X;
			//if (velocity.x >   MAX_MINI_VELOCITY_X + MAX_VELOCITY_X) velocity.x =   MAX_MINI_VELOCITY_X + MAX_VELOCITY_X;
			//if (velocity.x < -(MAX_MINI_VELOCITY_X + MAX_VELOCITY_X))velocity.x = -(MAX_MINI_VELOCITY_X + MAX_VELOCITY_X);
		}
	}
#endif // VLOCITY_MAX_FLG_X
}

void Movement::UpdateAxisY(float elapsedTime)
{
#ifdef VLOCITY_MIN_FLG_Y
	//velocity増減処理
	{
		if (velocity.y < 0.0f)
		{
			velocity.y = velocity.y + friction.y;
			if (velocity.y > 0.0f)velocity.y = 0.0f;
		}
		if (velocity.y > 0.0f)
		{
			velocity.y = velocity.y - friction.y;
			if (velocity.y < 0.0f)velocity.y = 0.0f;
		}
	}
#endif // VLOCITY_MIN_FLG_Y
#ifdef VLOCITY_MAX_FLG_Y
	//velocityの最大値
	{
		if(on_ground)
		//velocityの最大値を超えないようにする
		{
			if (velocity.y >  MAX_VELOCITY_Y*move_vec.y)velocity.y =  MAX_VELOCITY_Y*move_vec.y;
			if (velocity.y < -MAX_VELOCITY_Y*move_vec.y)velocity.y = -MAX_VELOCITY_Y*move_vec.y;
		}
	}
#endif // VLOCITY_MAX_FLG_Y
	//重力処理
	{
		{
			now_gravity += gravity;
			if (now_gravity > MAX_GRAVITY)now_gravity = MAX_GRAVITY;
		}
		if (on_ground)
		{
			//velocity.y = 0;
			now_gravity = 0;
		}
		velocity.y -= now_gravity;
	}
}

void Movement::UpdateAxisZ(float elapsedTime)
{
#ifdef VLOCITY_MIN_FLG_Z
	//velocity増減処理
	{
		if (velocity.z < 0.0f)
		{
			velocity.z = velocity.z + friction.z;
			if (velocity.z > 0.0f)velocity.z = 0.0f;
		}
		if (velocity.z > 0.0f)
		{
			velocity.z = velocity.z - friction.z;
			if (velocity.z < 0.0f)velocity.z = 0.0f;
		}
	}
#endif // VLOCITY_MIN_FLG_Z
#ifdef VLOCITY_MAX_FLG_Z
	//velocityの最大値
	{
		//velocityの最大値を超えないようにする
		{
			if (velocity.z >   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1)) velocity.z =   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1);
			if (velocity.z < -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1)))velocity.z = -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1));
			//if (velocity.z >   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z) velocity.z =   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z;
			//if (velocity.z < -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z))velocity.z = -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z);
		}
	}
#endif // VLOCITY_MAX_FLG_Z
}
