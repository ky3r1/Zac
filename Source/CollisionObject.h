#pragma once
#include "Object.h"

enum class HitCollisionType
{
    Damage,
    Heel,
    None
};

class CollisionObject : public Object
{
public:
    CollisionObject();
    ~CollisionObject();
    const char* GetName()const override { return "CollisionObject"; }

    //開始
    virtual void Start() override;
    //更新
    virtual void Update(float elapsedTime) override;
    //Imgui描画
    virtual void DrawImGui() override;
    //デバッグプリミティブ描画
    virtual void DrawDebug() override;
public:
    void SetTargetActorType(ActorType type){ target_actortype = type; }
    ActorType GetTargetActorType(){ return target_actortype; }
    void SetHitCollisionType(HitCollisionType type){ hc_type = type; }
    HitCollisionType GetHitCollisionType(){ return hc_type; }
    void SetHitNum(float num){ hit_num = num; }
private:

protected:
        HitCollisionType hc_type = HitCollisionType::None;
    ActorType target_actortype = ActorType::None;
    float hit_num = 0.0f;
    Actor* target_actor = nullptr;
    
};