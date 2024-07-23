#include "Movement.h"
#include "Mathf.h"

#define MAX_GRAVITY 5.0f

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
}

void Movement::Update(float elapsedTime)
{
	DirectX::XMFLOAT3 pos=GetActor()->GetPosition();
	//velocityëùå∏èàóù
	{
		if (velocity.x < 0.0f)
		{
			velocity.x = velocity.x + friction.x;
			if (velocity.x > 0.0f)velocity.x = 0.0f;

		}
		if (velocity.y < 0.0f)
		{
			velocity.y = velocity.y + friction.y;
			if (velocity.y > 0.0f)velocity.y = 0.0f;
		}
		if (velocity.z < 0.0f)
		{
			velocity.z = velocity.z + friction.z;
			if (velocity.z > 0.0f)velocity.z = 0.0f;
		}
		if (velocity.x > 0.0f)
		{
			velocity.x = velocity.x - friction.x;
			if (velocity.x < 0.0f)velocity.x = 0.0f;
		}
		if (velocity.y > 0.0f)
		{
			velocity.y = velocity.y - friction.y;
			if (velocity.y < 0.0f)velocity.y = 0.0f;
		}
		if (velocity.z > 0.0f)
		{
			velocity.z = velocity.z - friction.z;
			if (velocity.z < 0.0f)velocity.z = 0.0f;
		}
	}

	pos = Mathf::Add(velocity, pos);
	now_gravity += gravity;
	if(now_gravity > MAX_GRAVITY)now_gravity = MAX_GRAVITY;
	pos.y -= now_gravity;
	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
		velocity.y = 0;
		now_gravity = 0;
	}
	GetActor()->SetPosition(pos);
}

void Movement::Move(const DirectX::XMFLOAT3& direction, float elapsedTime)
{
	std::shared_ptr<Actor> actor = GetActor();
	float speed = moveSpeed * elapsedTime;
	DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);
	DirectX::XMVECTOR Velocity = DirectX::XMVectorScale(Direction, speed);
	DirectX::XMFLOAT3 v;
	DirectX::XMStoreFloat3(&v, Velocity);
	velocity.x=v.x;
    velocity.z=v.z;
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

void Movement::Turn(const DirectX::XMFLOAT3& direction, float elapsedTime)
{
	std::shared_ptr<Actor> actor = GetActor();
	float speed = turnSpeed * elapsedTime;
	DirectX::XMVECTOR Direction = DirectX::XMLoadFloat3(&direction);
	DirectX::XMVECTOR Rotation = DirectX::XMLoadFloat4(&actor->GetRotation());
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationQuaternion(Rotation);
	DirectX::XMVECTOR OneZ = DirectX::XMVectorSet(0, 0, 1, 0);
	DirectX::XMVECTOR Front = DirectX::XMVector3TransformNormal(OneZ, Transform);

	Direction = DirectX::XMVector3Normalize(Direction);
	DirectX::XMVECTOR Axis = DirectX::XMVector3Cross(Front, Direction);
	if (DirectX::XMVector3Equal(Axis, DirectX::XMVectorZero()))
	{
		return;
	}

	DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Front, Direction);

	float dot;
	DirectX::XMStoreFloat(&dot, Dot);
	speed = (std::min)(1.0f - dot, speed);

	DirectX::XMVECTOR Turn = DirectX::XMQuaternionRotationAxis(Axis, speed);
	Rotation = DirectX::XMQuaternionMultiply(Rotation, Turn);

	DirectX::XMFLOAT4 rotation;
	DirectX::XMStoreFloat4(&rotation, Rotation);
	actor->SetRotation(rotation);
}

void Movement::Jump()
{
	velocity.y += 2.0f;
}

void Movement::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
	velocity = Mathf::Add(velocity, impulse);
}
