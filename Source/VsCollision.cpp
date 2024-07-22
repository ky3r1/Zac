#include "VsCollision.h"

VsCollision::VsCollision()
{
}

VsCollision::~VsCollision()
{
}

void VsCollision::SphereVsSphere(ActorType filter)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	Sphere pc = GetActor()->GetSphere();
	Sphere ec = actor->GetSphere();
	if (Collision::IntersectSphereVsSphere(pc, ec))
	{
		GetActor()->SetSphere(pc);
		actor->SetSphere(ec);
	}
}

void VsCollision::SphereVsCylinder(ActorType filter,bool flg)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	//‚¿å‚ªSphere‚È‚çtrueA‚¿å‚ªCylinder‚È‚çfalse
	if (flg)
	{
		Sphere pc = GetActor()->GetSphere();
		Cylinder ec = actor->GetCylinder();
		if (Collision::IntersectSphereVsCylinder(pc, ec))
		{
			GetActor()->SetSphere(pc);
			actor->SetCylinder(ec);
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
        }
	}

}

void VsCollision::CylinderVsCylinder(ActorType filter)
{
	Actor* actor = ActorManager::Instance().GetNearActor(GetActor().get(), filter);
	Cylinder pc = GetActor()->GetCylinder();
	Cylinder ec = actor->GetCylinder();
	if (Collision::IntersectCylinderVsCylinder(pc, ec))
	{
		GetActor()->SetCylinder(pc);
		actor->SetCylinder(ec);
	}
}
