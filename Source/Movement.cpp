#include "Movement.h"
#include "Mathf.h"

#define MAX_GRAVITY 1.0f

//Velocity�̍ő�l(�ړ��x�N�g���Ɋ|���邽��0�ɂȂ�ꍇ������̂ŉ��̐��l�A��)
#define MAX_VELOCITY_X 1.00f
#define MAX_VELOCITY_Y 1.00f
#define MAX_VELOCITY_Z 1.00f
//Velocity�̍Œ���̍ő�l
#define MAX_MINI_VELOCITY_X 0.00f
#define MAX_MINI_VELOCITY_Y 0.00f
#define MAX_MINI_VELOCITY_Z 0.00f

//�ړ��x�N�g�����͎��̍ő�l
#define MAX_VELOCITY_MOVE_X 0.50f
#define MAX_VELOCITY_MOVE_Y 0.50f
#define MAX_VELOCITY_MOVE_Z 0.50f

//Velocity�ő�l�̗L����
#define VLOCITY_MAX_FLG_X
//#define VLOCITY_MAX_FLG_Y
#define VLOCITY_MAX_FLG_Z
//Velocity�ŏ��l�̗L����
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

	//�X���[�v�̌X��
	{
		//�X�Η��̌v�Z
		float normalLengthXZ = sqrtf(normal.x* normal.x + normal.z * normal.z);
		slope_rate = 1.0 - (normal.y / (normalLengthXZ + normal.y));
		DirectX::XMFLOAT2 vel = { velocity.x, velocity.z };
		DirectX::XMVECTOR velVel = DirectX::XMLoadFloat2(&vel);
		float length = DirectX::XMVectorGetX(DirectX::XMVector2Length(velVel));
		//�����ŃK�^�K�^���Ȃ��悤�ɂ���
		if (on_ground && slope_rate > 0.0f)
		{
			velocity.y -= length * slope_rate * elapsedTime;
		}
	}



	//�n�ʂ̌����ɉ����悤��XZ����]
	if(GetActor()->GetAttitudeControlFlag())
	{
		//Y�����@���x�N�g�������Ɍ����I�C���[�p��]���Z�o
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
	//�ړ������x�N�g��
	//velocity.x += v.x * moveSpeed*0.01f;
	//velocity.y += v.y * moveSpeed*0.01f;
	//velocity.z += v.z * moveSpeed*0.01f;

	//velocity�̍ő�l
	{
		//velocity�̍ő�l�𒴂��Ȃ��悤�ɂ���
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
	//�ړ������x�N�g��
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

	//�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
	float length = sqrtf(vx * vx + vz * vz);
	if (length < 0.0001f) return;

	//�i�s�x�N�g����P�ʃx�N�g����
	vx /= length;
	vz /= length;


	//���g�̉�]�l����O���������߂�
	float frontX = sinf(actor->GetRotation().y);
	float frontZ = cosf(actor->GetRotation().y);

	//��]�p�����߂邽�߁A2�̒P�ʃx�N�g���̓��ς��v�Z����
	float dot = (vx * frontX) + (vz * frontZ);

	//���ϒl��-1.0�`1.0�ŕ\������Ă���A2�̒P�ʃx�N�g���̊p�x��
	// �������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
	float rot = 1.0 - dot;
	if (rot > speed) { rot = speed; }
	//speed *= rot;
	//���E������s�����߂�2�̒P�ʃx�N�g���̊O�ς��v�Z����
	float cross = (vz * frontX) - (vx * frontZ);

	//2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
	//���E������s�����Ƃɂ���č��E��]��I������

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
	//velocity��������
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
	//velocity�̍ő�l
	{
		//velocity�̍ő�l�𒴂��Ȃ��悤�ɂ���
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
	//velocity��������
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
	//velocity�̍ő�l
	{
		if(on_ground)
		//velocity�̍ő�l�𒴂��Ȃ��悤�ɂ���
		{
			if (velocity.y >  MAX_VELOCITY_Y*move_vec.y)velocity.y =  MAX_VELOCITY_Y*move_vec.y;
			if (velocity.y < -MAX_VELOCITY_Y*move_vec.y)velocity.y = -MAX_VELOCITY_Y*move_vec.y;
		}
	}
#endif // VLOCITY_MAX_FLG_Y
	//�d�͏���
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
	//velocity��������
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
	//velocity�̍ő�l
	{
		//velocity�̍ő�l�𒴂��Ȃ��悤�ɂ���
		{
			if (velocity.z >   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1)) velocity.z =   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1);
			if (velocity.z < -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1)))velocity.z = -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z * (move_vec.z+1));
			//if (velocity.z >   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z) velocity.z =   MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z;
			//if (velocity.z < -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z))velocity.z = -(MAX_MINI_VELOCITY_Z + MAX_VELOCITY_Z);
		}
	}
#endif // VLOCITY_MAX_FLG_Z
}
