#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Graphics/sprite.h"

//#include "Character.h"
//#include "ProjectileManager.h"
#include "Effect.h"

#include "Component.h"
#include "Movement.h"
#include "Character.h"

enum
{
	Anim_Player_Combo01, //0
	Anim_Player_Combo02,
	Anim_Player_Combo03,
	Anim_Player_Combo04,
	Anim_Player_Death,
	Anim_Player_GunIdle,
	Anim_Player_GunPutAway,
	Anim_Player_GunShoot,
	Anim_Player_GunTakeOut,
	Anim_Player_HitBack,
	Anim_Player_HitFront,
	Anim_Player_HitLeft,
	Anim_Player_HitRight,
	Anim_Player_Idle,
	Anim_Player_IdleLand,
	Anim_Player_IdleLandFast,
	Anim_Player_IdleShort,
	Anim_Player_JumpGoesDown,
	Anim_Player_JumpGouesDown2,
	Anim_Player_JumpUp,
	Anim_Player_JumpUp2,
	Anim_Player_JumpPeak,
	Anim_Player_JumpTakeOff,
	Anim_Player_QuiclTurnLeft,
	Anim_Player_QuiclTurnRight,
	Anim_Player_RandomIdle01,
	Anim_Player_RandomIdle02,
	Anim_Player_RandomIdle03,
	Anim_Player_RunForward,
	Anim_Player_RunForwardInPlace,
	Anim_Player_RunForwardLanding,
	Anim_Player_RunForwardLandingFast,
	Anim_Player_Spawn,
	Anim_Player_WalkForward,
	Anim_Player_WalkForwardInPlace,
	Anim_Player_walkForwardsLanding,
};

class Player : public Character
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

	//Imgui描画
	void DrawImGui() override;

	//デバッグプリミティブ描画
	void DrawDebug() override;

private:
	// キャラクター操作
	void CharacterControl(float elapsedTime);

	DirectX::XMFLOAT3 GetMoveVec();
private:
};