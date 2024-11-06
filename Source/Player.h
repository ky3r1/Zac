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

	//�`��
	void Render(ID3D11DeviceContext* dc, Shader* shader) override;

	//Imgui�`��
	void DrawImGui() override;

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebug() override;

private:
	// �L�����N�^�[����
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