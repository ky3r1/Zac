#pragma once
#include "Object.h"

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
protected:
    bool test_flg2 = false;
    ActorType target_actortype = ActorType::None;
    //Actor* target_actor = nullptr;
    //std::unique_ptr<Actor> target_actor = nullptr;
    std::shared_ptr<Actor> target_actor = nullptr;
};