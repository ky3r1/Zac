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

    //‹…‘Ì‚Æ‹…‘Ì‚ÌÕ“Ë”»’è
    bool SphereVsSphere(ActorType filter);

    //‹…‘Ì‚Æ‰~’Œ‚ÌÕ“Ë”»’è
    //‚¿å‚ªSphere‚È‚çtrueA‚¿å‚ªCylinder‚È‚çfalse
    bool SphereVsCylinder(ActorType filter,bool flg);

    //‰~’Œ‚Æ‹…‘Ì‚ÌÕ“Ë”»’è
    bool CylinderVsCylinder(ActorType filter);

    //void RayCast(const Ray& ray, float& distance);
private:
};