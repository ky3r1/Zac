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

class Player : public Character
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

	// �J��������
	void CameraControl(float elapsedTime);
};