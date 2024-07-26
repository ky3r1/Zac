#include "CollisionObject.h"
#include "VsCollision.h"

CollisionObject::CollisionObject()
{
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::Start()
{
}

void CollisionObject::Update(float elapsedTime)
{
	Object::Update(elapsedTime);
	Actor* actor = nullptr;
	if (GetActor()->GetComponent<VsCollision>()->SphereVsSphere(target_actortype, &actor))
	{
		switch (hc_type)
		{
		case HitCollisionType::Damage:
            actor->TakeDamage(hit_num);
			break;
        case HitCollisionType::Heel:
			actor->TakeHeel(hit_num);
            break;
        default:
            break;
		}
		GetActor()->SetDeadFlag(true);
		ActorManager::Instance().Remove(GetActor());
	}
	target_actor = actor;
}

void CollisionObject::DrawImGui()
{
	{
		// �f�o�b�O������\���̕ύX
		std::string type_str = "";
		// ���݂̃X�e�[�g�ԍ��ɍ��킹�ăf�o�b�O�������str�Ɋi�[
		switch (target_actortype)
		{
		case ActorType::Player:
			type_str = "Player";
			break;
		case ActorType::Enemy:
			type_str = "Enemy";
			break;
		case ActorType::Stage:
			type_str = "Stage";
			break;
		case ActorType::Object:
			type_str = "Object";
			break;
		case ActorType::Camera:
			type_str = "Camera";
			break;
        case ActorType::Bullet:
			type_str = "Bullet";
			break;
		case ActorType::None:
			type_str = "None";
			break;
		default:
			type_str = "Unknown";
			break;
		}
		ImGui::Text(u8"TargetActorType:%s", type_str.c_str());
	}
}

void CollisionObject::DrawDebug()
{
}
