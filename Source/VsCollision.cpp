#include "VsCollision.h"
#include "Movement.h"

VsCollision::VsCollision()
{
}

VsCollision::~VsCollision()
{
}

bool VsCollision::SphereVsSpherePushing(ActorType filter,Actor** reactor)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	if (actor == nullptr)return false;
	if (reactor != nullptr)*reactor = actor;
	Sphere pc = GetActor()->GetSphere();
	Sphere ec = actor->GetSphere();
	if (Collision::IntersectSphereVsSphere(pc, ec))
	{
        GetActor()->SetSphere(pc);
        actor->SetSphere(ec);
		return true;
	}
	return false;
}

bool VsCollision::SphereVsSphere(ActorType filter, Actor** reactor)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	if (actor == nullptr)return false;
	if (reactor != nullptr)*reactor = actor;
	Sphere pc = GetActor()->GetSphere();
	Sphere ec = actor->GetSphere();
	if (Collision::IntersectSphereVsSphere(pc, ec))
	{
		return true;
	}
	return false;
}

bool VsCollision::SphereVsCylinderPushing(ActorType filter, Actor** reactor,bool flg)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	if (actor == nullptr)return false;
	if (reactor != nullptr)*reactor = actor;
	//持ち主がSphereならtrue、持ち主がCylinderならfalse
	if (flg)
	{
		Sphere pc = GetActor()->GetSphere();
		Cylinder ec = actor->GetCylinder();
		if (Collision::IntersectSphereVsCylinder(pc, ec))
		{
			GetActor()->SetSphere(pc);
			actor->SetCylinder(ec);
			return true;
		}
	}
	else
	{
		Cylinder pc = GetActor()->GetCylinder();
		Sphere ec = actor->GetSphere();
        if (Collision::IntersectSphereVsCylinder(ec, pc))
        {
            GetActor()->SetCylinder(pc);
            actor->SetSphere(ec);
			return true;
        }
	}
	return false;
}

bool VsCollision::SphereVsCylinder(ActorType filter, Actor** reactor, bool flg)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	if (actor == nullptr)return false;
	if (reactor != nullptr)*reactor = actor;
	//持ち主がSphereならtrue、持ち主がCylinderならfalse
	if (flg)
	{
		Sphere pc = GetActor()->GetSphere();
		Cylinder ec = actor->GetCylinder();
		if (Collision::IntersectSphereVsCylinder(pc, ec))
		{
			return true;
		}
	}
	else
	{
		Cylinder pc = GetActor()->GetCylinder();
		Sphere ec = actor->GetSphere();
		if (Collision::IntersectSphereVsCylinder(ec, pc))
		{
			if (reactor != nullptr)*reactor = actor;
			return true;
		}
	}
	return false;
}

bool VsCollision::CylinderVsCylinderPushing(ActorType filter, Actor** reactor)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);	
	if(actor == nullptr)return false;
	if (reactor != nullptr)*reactor = actor;
	Cylinder pc = GetActor()->GetCylinder();
	Cylinder ec = actor->GetCylinder();
	if (Collision::IntersectCylinderVsCylinder(pc, ec))
	{	
		
		GetActor()->SetCylinder(pc);
		actor->SetCylinder(ec);
		return true;
	}
	return false;
}

bool VsCollision::CylinderVsCylinder(ActorType filter, Actor** reactor)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	if (actor == nullptr)return false;
	if (reactor != nullptr)*reactor = actor;
	Cylinder pc = GetActor()->GetCylinder();
	Cylinder ec = actor->GetCylinder();
	if (Collision::IntersectCylinderVsCylinder(pc, ec))
	{
		return true;
	}
	return false;
}

bool VsCollision::RayCastAxisYUnder()
{
	DirectX::XMFLOAT3 position = {
	GetActor()->GetRayPosition().x,
	GetActor()->GetRayPosition().y,
	GetActor()->GetRayPosition().z
	};
	DirectX::XMFLOAT3 vec = GetActor()->GetComponent<Movement>()->GetVelocity();

	DirectX::XMFLOAT3 start = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y + 1.0f,
		GetActor()->GetPosition().z
	};

	DirectX::XMFLOAT3 end = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y + GetActor()->GetComponent<Movement>()->GetVelocity().y,
		GetActor()->GetPosition().z
	};

	Actor* actor = nullptr;
	HitResult hit_result;
	if (ActorManager::Instance().GetNearActorRayCast(start, end, hit_result, &actor))
	{
		switch (actor->GetFomY())
		{
		case FOM::Normal:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, 0.0f, vec.z));
			break;
		case FOM::Bounse:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, -vec.y * repulsion_coefficient, vec.z));
			break;
		case FOM::Friction:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			break;
		case FOM::Friction_One:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			break;
		case FOM::None:
			break;
			//default:
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, 0.0f, vec.z));
			//	break;
		}

		GetActor()->SetPosition(hit_result.position);
		GetActor()->GetComponent<Movement>()->SetNormal(hit_result.normal);
		return true;
	}
	//GetActor()->GetComponent<Movement>()->SetNormal(DirectX::XMFLOAT3(0, 1, 0));
	return false;
}

bool VsCollision::RayCastAxisYUp()
{
	DirectX::XMFLOAT3 position = {
		GetActor()->GetRayPosition().x,
		GetActor()->GetRayPosition().y,
		GetActor()->GetRayPosition().z
	};
	DirectX::XMFLOAT3 vec = GetActor()->GetComponent<Movement>()->GetVelocity();

	DirectX::XMFLOAT3 start = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y + GetActor()->GetHeight(),
		GetActor()->GetPosition().z
	};

	DirectX::XMFLOAT3 end = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y + GetActor()->GetHeight() + GetActor()->GetComponent<Movement>()->GetVelocity().y,
		GetActor()->GetPosition().z
	};

	Actor* actor = nullptr;
	HitResult hit_result;
	if (ActorManager::Instance().GetNearActorRayCast(start, end, hit_result, &actor))
	{
		switch (actor->GetFomY())
		{
		case FOM::Normal:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, 0.0f, vec.z));
			break;
		case FOM::Bounse:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, -vec.y * repulsion_coefficient, vec.z));
			break;
		case FOM::Friction:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			break;
		case FOM::Friction_One:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			break;
		case FOM::None:
			break;
			//default:
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, 0.0f, vec.z));
			//	break;
		}
		hit_result.position.y = hit_result.position.y
			- GetActor()->GetHeight()
			;

		GetActor()->SetPosition(hit_result.position);
		GetActor()->GetComponent<Movement>()->SetNormal(hit_result.normal);
		return true;
	}
	//GetActor()->GetComponent<Movement>()->SetNormal(DirectX::XMFLOAT3(0, 1, 0));
	return false;
}

void VsCollision::RayCastAxisYUnderEx()
{
	DirectX::XMFLOAT3 position = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y,
		GetActor()->GetPosition().z
	};
	DirectX::XMFLOAT3 vec = GetActor()->GetComponent<Movement>()->GetVelocity();

	DirectX::XMFLOAT3 start = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y + 1.0f,
		GetActor()->GetPosition().z
	};

	DirectX::XMFLOAT3 end = {
		GetActor()->GetPosition().x,
		-FLT_MAX,
		GetActor()->GetPosition().z
	};

	Actor* actor = nullptr;
	HitResult hit_result;
	ActorManager::Instance().GetNearActorRayCast(start, end, hit_result, &actor);
	GetActor()->GetComponent<Movement>()->SetNormal(hit_result.normal);
}

bool VsCollision::RayCastAxisXZ()
{
	static float movespeed = GetActor()->GetComponent<Movement>()->GetMoveSpeed();
	float ms = movespeed;
	DirectX::XMFLOAT3 position = {
		GetActor()->GetRayPosition().x,
		GetActor()->GetRayPosition().y,
		GetActor()->GetRayPosition().z
    };
	DirectX::XMFLOAT3 vec = GetActor()->GetComponent<Movement>()->GetVelocity();

	// 移動ベクトル
	float moveLength = sqrtf(vec.x * vec.x + vec.z * vec.z);
	if (moveLength > 0.0f)
	{
		DirectX::XMFLOAT3 start = {
			position.x,
			//GetActor()->GetPosition().y + GetActor()->GetHeight() * 0.5f,
			position.y + 1.0f,
			position.z
		};

		DirectX::XMFLOAT3 end = {
			position.x + vec.x,
			//GetActor()->GetPosition().y + GetActor()->GetHeight() * 0.5f,
			position.y + 1.0f,
			position.z + vec.z
		};
		Actor* actor = nullptr;
		HitResult hit_result;
		if (ActorManager::Instance().GetNearActorRayCast(start, end, hit_result, &actor))
		{
			DirectX::XMFLOAT3 offset = {};
			ms = 0;
			float offset_length = 1.5f;
			//if (hit_result.position.x > position.x)offset.x = -offset_length;
			//else if (hit_result.position.x < position.x)offset.x = offset_length;
			//if (hit_result.position.z > position.z)offset.z = -offset_length;
			//else if (hit_result.position.z < position.z)offset.z = offset_length;
			if (hit_result.position.x > position.x)offset.x = -vec.x;
			else if (hit_result.position.x < position.x)offset.x = vec.x;
			if (hit_result.position.z > position.z)offset.z = -vec.z;
			else if (hit_result.position.z < position.z)offset.z = vec.z;

			//if (abs(vec.x) > abs(vec.z))
			//{
			//	if (vec.x > 0)offset.x = -offset_length;
			//	if (vec.x < 0)offset.x = +offset_length;
			//}
			//else
			//{
			//	if (vec.z > 0)offset.z = -offset_length;
			//	if (vec.z < 0)offset.z = +offset_length;
			//}
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, vec.y, 0.0f));

			// 交点から終点へのベクトルを求める
			DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&hit_result.position);
			DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&end);
			DirectX::XMVECTOR PE = DirectX::XMVectorSubtract(E, P);

			// 三角形で終点から壁までのベクトルを求める
			DirectX::XMVECTOR N = DirectX::XMLoadFloat3(&hit_result.normal);
			DirectX::XMVECTOR A = DirectX::XMVector3Dot(DirectX::XMVectorScale(PE, -1.0f), N);
			// 壁までの長さを少しだけ長くなるように補正する
			float a = DirectX::XMVectorGetX(A) + 0.001f;

			// 壁ずりベクトルを求める
			DirectX::XMVECTOR R = DirectX::XMVectorAdd(PE, DirectX::XMVectorScale(N, a));

			// 壁ずり後の位置を求める
			DirectX::XMVECTOR Q = DirectX::XMVectorAdd(P, R);
			DirectX::XMFLOAT3 q;
			DirectX::XMStoreFloat3(&q, Q);

			// 壁際で壁ずり後の位置がめり込んでいないかレイキャストでチェックする
			if (ActorManager::Instance().GetNearActorRayCast(start, q, hit_result, &actor))
			{
				// めり込んでいた場合はプレイヤーの位置に今回レイキャストした交点を設定する
				// ※プレイヤーの位置が壁にピッタリくっつかないように補正する
				P = DirectX::XMLoadFloat3(&hit_result.position);
				DirectX::XMVECTOR S = DirectX::XMLoadFloat3(&start);
				DirectX::XMVECTOR PS = DirectX::XMVectorSubtract(P, S);
				DirectX::XMVECTOR V = DirectX::XMVector3Normalize(PS);
				P = DirectX::XMVectorAdd(P, DirectX::XMVectorScale(V, -0.001f));
				DirectX::XMFLOAT3 p;
				DirectX::XMStoreFloat3(&p, P);
				GetActor()->SetPosition({ p.x + offset.x,GetActor()->GetPosition().y,p.z + offset.z });
			}
			else
			{
				GetActor()->SetPosition({ q.x + offset.x,GetActor()->GetPosition().y,q.z + offset.z });
			}


			//switch (actor->GetFomXZ())
			//{
			//case FOM::Normal:
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, vec.y, 0.0f));
			//	break;
			//case FOM::Bounse:
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(-vec.x * repulsion_coefficient, vec.y, -vec.z * repulsion_coefficient));
			//	break;
			//case FOM::Friction:
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			//	break;
			//case FOM::Friction_One:
			//	GetActor()->GetComponent<Movement>()->SetGravity(0.0f);
			//	GetActor()->GetComponent<Movement>()->SetNowGravity(0.0f);
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			//	break;
			//case FOM::None:
			//	break;
			//}
			//vec.x *= -1;
			//vec.z *= -1;
			//GetActor()->GetComponent<Movement>()->SetVelocity(vec);


			//GetActor()->SetPosition(position);
			return true;
		}
	}
	GetActor()->GetComponent<Movement>()->SetMoveSpeed(ms);
	return false;
}