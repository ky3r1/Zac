#include "VsCollision.h"
#include "Movement.h"

VsCollision::VsCollision()
{
}

VsCollision::~VsCollision()
{
}

void VsCollision::Update(float elapsedTime)
{
	RayCastDown(ActorType::Stage);
}

bool VsCollision::SphereVsSphere(ActorType filter)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
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

bool VsCollision::SphereVsCylinder(ActorType filter,bool flg)
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

bool VsCollision::CylinderVsCylinder(ActorType filter)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
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

bool VsCollision::RayCastDown(ActorType filter)
{
	Model* model_hit_in_ray = ActorManager::Instance().GetNearActor(GetActor().get(), filter)->GetModel();
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

	HitResult hit_result;
	if(Collision::IntersectRayVsModel(start, end, model_hit_in_ray, hit_result))
    {
		GetActor()->GetComponent<Movement>()->SetOnGround(true);
		GetActor()->SetPosition(hit_result.position);
		return true;
    }
	GetActor()->GetComponent<Movement>()->SetOnGround(false);
	return false;
}
