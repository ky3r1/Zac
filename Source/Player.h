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

	// ���O�擾
	const char* GetName() const override { return "Player"; }

	// �J�n����
	void Start() override;

	// �X�V����
	void Update(float elapsedTime) override;

	//Imgui�`��
	void DrawImGui() override;

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebug() override;

private:
	// �L�����N�^�[����
	void CharacterControl(float elapsedTime);

	DirectX::XMFLOAT3 GetMoveVec();

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
};