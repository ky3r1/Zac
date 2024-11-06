#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Graphics/sprite.h"

//#include "Character.h"
//#include "ProjectileManager.h"
#include "Effect.h"

#include "Component.h"

class Player : public Component
{
public:
	Player();
	~Player() override;

	// 名前取得
	const char* GetName() const override { return "Player"; }

	// 開始処理
	void Start() override;

	// 更新処理
	void Update(float elapsedTime) override;

	//描画
	void Render(ID3D11DeviceContext* dc, Shader* shader) override;

	//Imgui描画
	void DrawImGui() override;

	//デバッグプリミティブ描画
	void DrawDebug() override;

private:
	// キャラクター操作
	void CharacterControl(float elapsedTime);

	DirectX::XMFLOAT3 GetMoveVec();
private:
	float jumpPower = 1000.0f;

private:
	enum Animation
	{
		Anim_shot_auto,
		Anim_shot_semiauto,
		Anim_reload,
		Anim_idle,
		Anim_jump,
		Anim_run_front,
		Anim_run_back,
		Anim_run_left,
		Anim_walk_left,
		Anim_walk_right,
		Anim_run_right,
		Anim_throw,
		Anim_aim_left,
		Anim_aim_right,
		Anim_aim_back,
		Anim_aim_front,
		None,
	};
private:
	//Model Gun = "Data/Model/AK47/AK47.mdl";
};