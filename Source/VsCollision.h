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

    //���̂Ƌ��̂̏Փ˔���
    bool SphereVsSphere(ActorType filter,Actor** reactor);

    //���̂Ɖ~���̏Փ˔���
    //�����傪Sphere�Ȃ�true�A�����傪Cylinder�Ȃ�false
    bool SphereVsCylinder(ActorType filter, Actor** reactor,bool flg);

    //�~���Ƌ��̂̏Փ˔���
    bool CylinderVsCylinder(ActorType filter,Actor** reactor);

    //�������̃��C�L���X�g
    bool RayCastAxisY();

    void RayCastAxisYUnder();

    //�������̃��C�L���X�g
    bool RayCastAxisXZ();
private:
    float repulsion_coefficient = 0.7f;//�����W��
};