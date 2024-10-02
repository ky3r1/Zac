#include "CollisionObject.h"
#include "VsCollision.h"
#include "Character.h"

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
	Actor* actor = nullptr;
	if (GetActor()->GetComponent<VsCollision>()->SphereVsCylinder(target_actortype, &actor, true))
	{
		switch (hc_type)
		{
		case HitCollisionType::Damage:
			actor->GetComponent<Character>()->TakeDamage(hit_num);
			break;
		case HitCollisionType::Heel:
			actor->GetComponent<Character>()->TakeHeel(hit_num);
			break;
		default:
			break;
		}
		if (deletion_flg)ActorManager::Instance().Remove(GetActor());
	}
	target_actor = actor;
}

void CollisionObject::Render(ID3D11DeviceContext* dc, Shader* shader)
{

}

void CollisionObject::DrawImGui()
{
	{
		// デバッグ文字列表示の変更
		std::string type_str = "";
		// 現在のステート番号に合わせてデバッグ文字列をstrに格納
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
	// デバッグ球描画
	{
		DirectX::XMFLOAT3 position = GetActor()->GetPosition();
		float radius = GetActor()->GetRadius();
		float height = GetActor()->GetHeight();
		DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1, 0, 0, 1);
		Graphics::Instance().GetDebugRenderer()->DrawSphere(position, radius, color);
	}
}
