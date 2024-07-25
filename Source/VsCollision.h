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
    bool SphereVsSpherePushing(ActorType filter,Actor** reactor);
    bool SphereVsSphere(ActorType filter, Actor** reactor);

    //���̂Ɖ~���̏Փ˔���
    //�����傪Sphere�Ȃ�true�A�����傪Cylinder�Ȃ�false
    bool SphereVsCylinderPushing(ActorType filter, Actor** reactor,bool flg);
    bool SphereVsCylinder(ActorType filter, Actor** reactor, bool flg);

    //�~���Ƌ��̂̏Փ˔���
    bool CylinderVsCylinderPushing(ActorType filter,Actor** reactor);
    bool CylinderVsCylinder(ActorType filter, Actor** reactor);

    //�������̃��C�L���X�g
    bool RayCastAxisY();

    void RayCastAxisYUnder();

    //�������̃��C�L���X�g
    bool RayCastAxisXZ();

    //bool CheckRayAxisY();
private:
    float repulsion_coefficient = 0.7f;//�����W��
    //bool checke = true;
};