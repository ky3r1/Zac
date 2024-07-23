#pragma once
#include "Component.h"
#include "Collision.h"
class VsCollision :public Component
{
public:
    VsCollision();
    virtual ~VsCollision();

    //ΌOζΎ
    const char* GetName()const override { return "VsCollision"; }

    void Update(float elapsedTime) override;

    //ΜΖΜΜΥΛ»θ
    bool SphereVsSphere(ActorType filter);

    //ΜΖ~ΜΥΛ»θ
    //ΏεͺSphereΘηtrueAΏεͺCylinderΘηfalse
    bool SphereVsCylinder(ActorType filter,bool flg);

    //~ΖΜΜΥΛ»θ
    bool CylinderVsCylinder(ActorType filter);

    //CLXg
    bool RayCastDown(ActorType filter);
private:
};