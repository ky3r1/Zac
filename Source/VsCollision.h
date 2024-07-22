#pragma once
#include "Component.h"
#include "Collision.h"
class VsCollision :public Component
{
public:
    VsCollision();
    virtual ~VsCollision();

    //–¼‘Oæ“¾
    const char* GetName()const override { return "VsCollision"; }

    void SphereVsSphere(ActorType filter);
    //‚¿å‚ªSphere‚È‚çtrueA‚¿å‚ªCylinder‚È‚çfalse
    void SphereVsCylinder(ActorType filter,bool flg);
    void CylinderVsCylinder(ActorType filter);

    //void RayCast(const Ray& ray, float& distance);
private:
};