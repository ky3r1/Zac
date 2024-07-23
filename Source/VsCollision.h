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

    void Update(float elapsedTime) override;

    //���̂Ƌ��̂̏Փ˔���
    bool SphereVsSphere(ActorType filter);

    //���̂Ɖ~���̏Փ˔���
    //�����傪Sphere�Ȃ�true�A�����傪Cylinder�Ȃ�false
    bool SphereVsCylinder(ActorType filter,bool flg);

    //�~���Ƌ��̂̏Փ˔���
    bool CylinderVsCylinder(ActorType filter);

    //���C�L���X�g
    bool RayCastDown(ActorType filter);
private:
};