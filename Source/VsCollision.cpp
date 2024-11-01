#include "VsCollision.h"
#include "Movement.h"
#include "Gravity.h"
#include <DirectXCollision.h>

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
	Movement* movement = GetActor()->GetComponent<Movement>().get();
	DirectX::XMFLOAT3 vec = movement->GetVelocity();

	DirectX::XMFLOAT3 start = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y + GetActor()->GetHeight()*0.5f,
		GetActor()->GetPosition().z
	};
	raycastcast_y_start = start;

	DirectX::XMFLOAT3 end = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y - 0.5f,
		GetActor()->GetPosition().z
	};
	raycastcast_y_end = end;
	Actor* actor = nullptr;
	HitResult hit_result;
	if (ActorManager::Instance().GetNearActorRayCast(start, end, hit_result, &actor))
	{
		//switch (actor->GetFomY())
		//{
		//case FOM::Normal:
		//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, 0.0f, vec.z));
		//	break;
		//case FOM::Bounse:
		//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, -vec.y * repulsion_coefficient, vec.z));
		//	break;
		//case FOM::Friction:
		//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
		//	break;
		//case FOM::Friction_One:
		//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
		//	break;
		//case FOM::None:
		//	break;
		//	//default:
		//	//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, 0.0f, vec.z));
		//	//	break;
		//}

		if (movement->GetVelocity().y<0)
		{
			GetActor()->SetPosition_Y(hit_result.position.y);
			movement->SetNormal(hit_result.normal);
			//DirectX::XMFLOAT3 up = { GetActor()->GetTransform()._21,GetActor()->GetTransform()._22 ,GetActor()->GetTransform()._23 };
			//movement->AddForce({ GetActor()->GetComponent<Gravity>()->GetPower().y * hit_result.normal.x,-GetActor()->GetComponent<Gravity>()->GetPower().y * hit_result.normal.y, GetActor()->GetComponent<Gravity>()->GetPower().y * hit_result.normal.z });
			//movement->AddForce({ 0,-GetActor()->GetComponent<Gravity>()->GetPower().y * hit_result.normal.y,0});
			movement->SetVelocity({ vec.x,0,vec.z });
			//movement->SetAcceleration({ movement->GetAcceleration().x,0,movement->GetAcceleration().z });
		}
		return true;
	}
	movement->SetNormal({ 0,1,0 });
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

		GetActor()->SetPosition_Y(hit_result.position.y);
		return true;
	}
	return false;
}


bool VsCollision::RayCastAxisXZ()
{
	DirectX::XMFLOAT3 position = {
		GetActor()->GetRayPosition().x,
		GetActor()->GetRayPosition().y,
		GetActor()->GetRayPosition().z
    };
	DirectX::XMFLOAT3 vec = GetActor()->GetComponent<Movement>()->GetVelocity();
	float front_scale = 0.15f;//要調整
	DirectX::XMFLOAT3 front = { GetActor()->GetTransform()._31 * front_scale,GetActor()->GetTransform()._32 * front_scale,GetActor()->GetTransform()._33 * front_scale };

	// 移動ベクトル
	float moveLength = sqrtf(vec.x * vec.x + vec.z * vec.z);
	if (moveLength > 0.0f)
	{
		DirectX::XMFLOAT3 start = {
			position.x,
			position.y + 2.0f,
			position.z
		};
		raycastcast_xz_start = start;
		DirectX::XMFLOAT3 end = {
			position.x + front.x,
			//GetActor()->GetPosition().y + GetActor()->GetHeight() * 0.5f,
			position.y + 2.0f,
			position.z + front.z
		};
		raycastcast_xz_end = end;
		Actor* actor = nullptr;
		HitResult hit_result;
		if (ActorManager::Instance().GetNearActorRayCast(start, end, hit_result, &actor))
		{
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
				GetActor()->SetPosition({ p.x - front.x,GetActor()->GetPosition().y,p.z - front.z });
			}
			else
			{
				GetActor()->SetPosition({ q.x - front.x,GetActor()->GetPosition().y,q.z - front.z });
			}
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, vec.y, 0.0f));

			//switch (actor->GetFomXZ())
			//{
			//case FOM::Normal:
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, vec.y, 0.0f));
			//	break;
			//case FOM::Bounse:
			//	GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(-vec.x * repulsion_coefficient, vec.y, -vec.z * repulsion_coefficient));--
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
	return false;
}

void VsCollision::DrawImGui()
{
}

void VsCollision::DrawDebug()
{
	// //デバッグ球描画
	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0, 1, 0, 1);
	Graphics::Instance().GetDebugRenderer()->DrawCube(raycastcast_y_start, raycastcast_y_end, color);
	color = DirectX::XMFLOAT4(0, 0, 1, 1);
	Graphics::Instance().GetDebugRenderer()->DrawCube(raycastcast_xz_start, raycastcast_xz_end, color);
}
