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

    //�J�n
    virtual void Start() override;
    //�X�V
    virtual void Update(float elapsedTime) override;
    //Imgui�`��
    virtual void DrawImGui() override;
    //�f�o�b�O�v���~�e�B�u�`��
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