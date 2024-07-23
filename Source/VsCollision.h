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

    void Update(float elapsedTime) override;

    //球体と球体の衝突判定
    bool SphereVsSphere(ActorType filter);

    //球体と円柱の衝突判定
    //持ち主がSphereならtrue、持ち主がCylinderならfalse
    bool SphereVsCylinder(ActorType filter,bool flg);

    //円柱と球体の衝突判定
    bool CylinderVsCylinder(ActorType filter);

    //レイキャスト
    bool RayCastDown(ActorType filter);
private:
};