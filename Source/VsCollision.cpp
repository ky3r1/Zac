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
	
	Sphere pc = GetActor()->GetSphere();
	Sphere ec = actor->GetSphere();
	if (Collision::IntersectSphereVsSphere(pc, ec))
	{
        GetActor()->SetSphere(pc);
        actor->SetSphere(ec);
		if (reactor != nullptr)*reactor = actor;
		return true;
	}
	return false;
}

bool VsCollision::SphereVsSphere(ActorType filter, Actor** reactor)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	
	Sphere pc = GetActor()->GetSphere();
	Sphere ec = actor->GetSphere();
	if (Collision::IntersectSphereVsSphere(pc, ec))
	{
		if (reactor != nullptr)*reactor = actor;
		return true;
	}
	return false;
}

bool VsCollision::SphereVsCylinderPushing(ActorType filter, Actor** reactor,bool flg)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	//Ž‚¿Žå‚ªSphere‚È‚çtrueAŽ‚¿Žå‚ªCylinder‚È‚çfalse
	if (flg)
	{
		Sphere pc = GetActor()->GetSphere();
		Cylinder ec = actor->GetCylinder();
		if (Collision::IntersectSphereVsCylinder(pc, ec))
		{
			GetActor()->SetSphere(pc);
			actor->SetCylinder(ec);
			if (reactor != nullptr)*reactor = actor;
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
			if (reactor != nullptr)*reactor = actor;
			return true;
        }
	}
	return false;
}

bool VsCollision::SphereVsCylinder(ActorType filter, Actor** reactor, bool flg)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	//Ž‚¿Žå‚ªSphere‚È‚çtrueAŽ‚¿Žå‚ªCylinder‚È‚çfalse
	if (flg)
	{
		Sphere pc = GetActor()->GetSphere();
		Cylinder ec = actor->GetCylinder();
		if (Collision::IntersectSphereVsCylinder(pc, ec))
		{
			if (reactor != nullptr)*reactor = actor;
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
	Cylinder pc = GetActor()->GetCylinder();
	Cylinder ec = actor->GetCylinder();
	if (Collision::IntersectCylinderVsCylinder(pc, ec))
	{	
		
		GetActor()->SetCylinder(pc);
		actor->SetCylinder(ec);
		if(reactor!=nullptr)*reactor = actor;
		return true;
	}
	return false;
}

bool VsCollision::CylinderVsCylinder(ActorType filter, Actor** reactor)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	Cylinder pc = GetActor()->GetCylinder();
	Cylinder ec = actor->GetCylinder();
	if (Collision::IntersectCylinderVsCylinder(pc, ec))
	{
		if (reactor != nullptr)*reactor = actor;
		return true;
	}
	return false;
}

bool VsCollision::RayCastAxisY()
{
	DirectX::XMFLOAT3 position = {
	GetActor()->GetPosition().x,
	GetActor()->GetPosition().y,
	GetActor()->GetPosition().z
	};
	DirectX::XMFLOAT3 vec = GetActor()->GetComponent<Movement>()->GetVelocity();

	DirectX::XMFLOAT3 start = { 
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y+ 1.0f,
		GetActor()->GetPosition().z
	};

	DirectX::XMFLOAT3 end = { 
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y+ GetActor()->GetComponent<Movement>()->GetVelocity().y,
		GetActor()->GetPosition().z
	};

	Actor* actor = nullptr;
	HitResult hit_result;
	if (ActorManager::Instance().GetNearActorRayCast(start, end, hit_result,&actor))
	{
		GetActor()->GetComponent<Movement>()->SetOnGround(true);
		switch (actor->GetFomY())
		{
		case FOM::Normal:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, 0.0f, vec.z));
			break;
		case FOM::Bounse:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(vec.x, -vec.y* repulsion_coefficient, vec.z));
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
	GetActor()->GetComponent<Movement>()->SetOnGround(false);
	return false;
}

void VsCollision::RayCastAxisYUnder()
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
	static float gravity = GetActor()->GetComponent<Movement>()->GetGravity();

	DirectX::XMFLOAT3 position = {
		GetActor()->GetPosition().x,
		GetActor()->GetPosition().y,
		GetActor()->GetPosition().z
    };
	DirectX::XMFLOAT3 vec = GetActor()->GetComponent<Movement>()->GetVelocity();

	DirectX::XMFLOAT3 start = {
		position.x,
		//GetActor()->GetPosition().y + GetActor()->GetHeight() * 0.5f,
		position.y+1.0f,
		position.z
	};

	DirectX::XMFLOAT3 end = {
		position.x + vec.x,
		//GetActor()->GetPosition().y + GetActor()->GetHeight() * 0.5f,
		position.y+1.0f,
		position.z + vec.z
	};
	Actor* actor = nullptr;
	HitResult hit_result;
	if (ActorManager::Instance().GetNearActorRayCast(start, end, hit_result, &actor))
	{
		if (abs(vec.x) > abs(vec.z))
		{
			if (vec.x > 0)position.x = hit_result.position.x - 0.1f;
			if (vec.x < 0)position.x = hit_result.position.x + 0.1f;
		}
		else
		{
			if (vec.z > 0)position.z = hit_result.position.z - 0.1f;
			if (vec.z < 0)position.z = hit_result.position.z + 0.1f;
		}
		switch (actor->GetFomXZ())
		{
		case FOM::Normal:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, vec.y, 0.0f));
			break;
		case FOM::Bounse:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(-vec.x* repulsion_coefficient, vec.y, -vec.z * repulsion_coefficient));
			break;
		case FOM::Friction:
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			break;
		case FOM::Friction_One:
			GetActor()->GetComponent<Movement>()->SetGravity(0.0f);
			GetActor()->GetComponent<Movement>()->SetNowGravity(0.0f);
			GetActor()->GetComponent<Movement>()->SetVelocity(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
			break;
		case FOM::None:
			break;
		}
		//vec.x *= -1;
		//vec.z *= -1;
		//GetActor()->GetComponent<Movement>()->SetVelocity(vec);

		
		GetActor()->SetPosition(position);
		return true;
	}
	GetActor()->GetComponent<Movement>()->SetGravity(gravity);
	return false;
}