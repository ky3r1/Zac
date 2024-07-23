#pragma once
#include "Component.h"
#include "Collision.h"
class VsCollision :public Component
{
public:
    VsCollision();
    virtual ~VsCollision();

    //ผOๆพ
    const char* GetName()const override { return "VsCollision"; }

    //ฬฦฬฬีหป่
    bool SphereVsSphere(ActorType filter);

    //ฬฦ~ฬีหป่
    //ฟๅชSphereศ็trueAฟๅชCylinderศ็false
    bool SphereVsCylinder(ActorType filter,bool flg);

    //~ฦฬฬีหป่
    bool CylinderVsCylinder(ActorType filter);

    //void RayCast(const Ray& ray, float& distance);
private:
};