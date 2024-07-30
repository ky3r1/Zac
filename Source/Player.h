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

#include "StateBase.h"

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

	void AnimationControl(float elapsedTime);

private:
	//Animation
	void UpdateIdle();
	void UpdateRun();
	void UpdateSpown();
	void UpdateLand();
	void UpdateGoesDown();
	void UpdateDeath();
private:
	enum
	{
		Anim_Combo01, //0
		Anim_Combo02,
		Anim_Combo03,
		Anim_Combo04,
		Anim_Death,
		Anim_GunIdle,
		Anim_GunPutAway,
		Anim_GunShoot,
		Anim_GunTakeOut,
		Anim_HitBack,
		Anim_HitFront,
		Anim_HitLeft,
		Anim_HitRight,
		Anim_Idle,
		Anim_IdleLand,
		Anim_IdleLandFast,
		Anim_IdleShort,
		Anim_JumpGoesDown,
		Anim_JumpGoesDown2,
		Anim_JumpUp,
		Anim_JumpUp2,
		Anim_JumpPeak,
		Anim_JumpTakeOff,
		Anim_QuiclTurnLeft,
		Anim_QuiclTurnRight,
		Anim_RandomIdle01,
		Anim_RandomIdle02,
		Anim_RandomIdle03,
		Anim_RunForward,
		Anim_RunForwardInPlace,
		Anim_RunForwardLanding,
		Anim_RunForwardLandingFast,
		Anim_Spawn,
		Anim_WalkForward,
		Anim_WalkForwardInPlace,
		Anim_walkForwardsLanding,
		None,
	};
private:
	//class IdleState :public StateBase
	//{
	//public:
	//	void Start(float elapsedTime,Actor** actor)override;
	//	void Update(float elapsedTime) override;
	//	void End(float elapsedTime) override;
	//};

	//class MoveState :public StateBase
	//{
	//public:
	//	void Start(float elapsedTime)override;
	//	void Update(float elapsedTime) override;
	//	void End(float elapsedTime) override;
	//};

	//class SpownState :public StateBase
	//{
	//public:
	//	void Start(float elapsedTime)override;
	//	void Update(float elapsedTime) override;
	//	void End(float elapsedTime) override;
	//};

	//class LandState :public StateBase
	//{
	//public:
	//	void Start(float elapsedTime)override;
	//	void Update(float elapsedTime) override;
	//	void End(float elapsedTime) override;
	//};

	//class GoesDownState :public StateBase
	//{
	//public:
	//	void Start(float elapsedTime)override;
	//	void Update(float elapsedTime) override;
	//	void End(float elapsedTime) override;
	//};

	//class DeathState :public StateBase
	//{
	//public:
	//	void Start(float elapsedTime)override;
	//	void Update(float elapsedTime) override;
	//	void End(float elapsedTime) override;
	//};
};