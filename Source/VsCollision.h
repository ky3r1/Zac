#pragma once
#include "Component.h"
#include "Collision.h"
class VsCollision :public Component
{
public:
    VsCollision();
    virtual ~VsCollision();

    //名前取得
    const char* GetName()const override { return "VsCollision"; }

    void SphereVsSphere(ActorType filter);
    //持ち主がSphereならtrue、持ち主がCylinderならfalse
    void SphereVsCylinder(ActorType filter,bool flg);
    void CylinderVsCylinder(ActorType filter);

    //void RayCast(const Ray& ray, float& distance);
private:
};