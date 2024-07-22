#pragma once
#include "Component.h"
#include "Collision.h"
class VsCollision :public Component
{
public:
    VsCollision();
    virtual ~VsCollision();

    //���O�擾
    const char* GetName()const override { return "VsCollision"; }

    void SphereVsSphere(ActorType filter);
    //�����傪Sphere�Ȃ�true�A�����傪Cylinder�Ȃ�false
    void SphereVsCylinder(ActorType filter,bool flg);
    void CylinderVsCylinder(ActorType filter);

    //void RayCast(const Ray& ray, float& distance);
private:
};