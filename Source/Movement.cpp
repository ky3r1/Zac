#include "Movement.h"
#include "Mathf.h"

#define MAX_GRAVITY 1.0f

//Velocity�̍ő�l(�ړ��x�N�g���Ɋ|���邽��0�ɂȂ�ꍇ������̂ŉ��̐��l�A��)
#define MAX_VELOCITY_X 7.00f
#define MAX_VELOCITY_Y 7.00f
#define MAX_VELOCITY_Z 7.00f
//Velocity�̍Œ���̍ő�l
#define MAX_MINI_VELOCITY_X 0.00f
#define MAX_MINI_VELOCITY_Y 0.00f
#define MAX_MINI_VELOCITY_Z 0.00f

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

	//�X���[�v�̌X��
	if(false)
	{
		//�X�Η��̌v�Z
		float normalLengthXZ = sqrtf(normal.x* normal.x + normal.z * normal.z);
		slope_rate = 1.0 - (normal.y / (normalLengthXZ + normal.y));
		DirectX::XMFLOAT2 vel = { velocity.x, velocity.z };
		DirectX::XMVECTOR velVel = DirectX::XMLoadFloat2(&vel);
		float length = DirectX::XMVectorGetX(DirectX::XMVector2Length(velVel));
		//�����ŃK�^�K�^���Ȃ��悤�ɂ���
		if (slope_rate > 0.0f)
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
	//���C
	{

		{
			DirectX::XMVECTOR f = DirectX::XMLoadFloat3(&velocity);
			f=DirectX::XMVectorScale(f, -1);
			f = DirectX::XMVectorAdd(DirectX::XMVectorScale(f, friction), DirectX::XMLoadFloat3(&velocity));
			DirectX::XMStoreFloat3(&velocity, f);
		}
	}
	//���x�X�V
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
		//�ړ������x�N�g��
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

	//�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
	float length = sqrtf(v.x * v.x + v.z * v.z);
	if (length < 0.0001f) return;

	//�i�s�x�N�g����P�ʃx�N�g����
	v.x /= length;
	v.z /= length;


	//���g�̉�]�l����O���������߂�
	float frontX = sinf(actor->GetRotation().y);
	float frontZ = cosf(actor->GetRotation().y);

	//��]�p�����߂邽�߁A2�̒P�ʃx�N�g���̓��ς��v�Z����
	float dot = (v.x * frontX) + (v.z * frontZ);

	//���ϒl��-1.0�`1.0�ŕ\������Ă���A2�̒P�ʃx�N�g���̊p�x��
	// �������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
	float rot = 1.0 - dot;
	if (rot > speed) { rot = speed; }
	//speed *= rot;
	//���E������s�����߂�2�̒P�ʃx�N�g���̊O�ς��v�Z����
	float cross = (v.z * frontX) - (v.x * frontZ);

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
