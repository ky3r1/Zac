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

    //球体と球体の衝突判定
    bool SphereVsSpherePushing(ActorType filter,Actor** reactor);
    bool SphereVsSphere(ActorType filter, Actor** reactor);

    //球体と円柱の衝突判定
    //持ち主がSphereならtrue、持ち主がCylinderならfalse
    bool SphereVsCylinderPushing(ActorType filter, Actor** reactor,bool flg);
    bool SphereVsCylinder(ActorType filter, Actor** reactor, bool flg);

    //円柱と球体の衝突判定
    bool CylinderVsCylinderPushing(ActorType filter,Actor** reactor);
    bool CylinderVsCylinder(ActorType filter, Actor** reactor);

    //下方向のレイキャスト
    bool RayCastAxisY();

    void RayCastAxisYUnder();

    //横方向のレイキャスト
    bool RayCastAxisXZ();

    //bool CheckRayAxisY();
private:
    float repulsion_coefficient = 0.7f;//反発係数
    //bool checke = true;
};