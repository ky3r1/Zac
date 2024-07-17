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

	void DrawDebug() override;

private:
	// �L�����N�^�[����
	void CharacterControl(float elapsedTime);

	// �J��������
	void CameraControl(float elapsedTime);

private:
	std::shared_ptr<Movement>	movement;

	//GamePad				gamePad;

	DirectX::XMFLOAT3	angle = DirectX::XMFLOAT3(0, 0, 0);

	DirectX::XMFLOAT3	cameraAngle = DirectX::XMFLOAT3(0, 0, 0);
	float				cameraRollSpeed = DirectX::XMConvertToRadians(90);
	float				cameraMaxPitch = DirectX::XMConvertToRadians(45);
	float				cameraMinPitch = DirectX::XMConvertToRadians(-45);
	float				cameraRange = 100.0f;
	float				characterHeight = 10.0f;
};