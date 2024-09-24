#pragma once
#include "Component.h"

enum class HitCollisionType
{
    Damage,
    Heel,
    None
};

class CollisionObject : public Component
{
public:
    CollisionObject();
    ~CollisionObject();
    const char* GetName()const override { return "CollisionObject"; }

    //�J�n
    virtual void Start() override;
    //�X�V
    virtual void Update(float elapsedTime) override;

    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) override;

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
    Actor* GetTargetActor(){ return target_actor; }
    void SetDeletionFlg(bool flg){ deletion_flg = flg; }
private:

private:
    HitCollisionType hc_type = HitCollisionType::None;
    ActorType target_actortype = ActorType::None;
    float hit_num = 0.0f;
    Actor* target_actor = nullptr;
    bool deletion_flg = true;// �^:���������������-�U:�������Ă������Ȃ�
};