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
    bool RayCastAxisYUnder();
    //������̃��C�L���X�g
    bool RayCastAxisYUp();

    //�������̃��C�L���X�g
    bool RayCastAxisXZ();

    //ImGui�`��
    void DrawImGui()override;
    void DrawDebug()override;
private:
    float repulsion_coefficient = 0.7f;//�����W��
    DirectX::XMFLOAT3 raycastcast_y_start = {};
    DirectX::XMFLOAT3 raycastcast_y_end = {};
    DirectX::XMFLOAT3 raycastcast_xz_start = {};
    DirectX::XMFLOAT3 raycastcast_xz_end = {};
    //bool checke = true;
};