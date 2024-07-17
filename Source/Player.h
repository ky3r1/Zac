#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Graphics/sprite.h"

//#include "Character.h"
//#include "ProjectileManager.h"
#include "Effect.h"

#include "Component.h"
#include "Movement.h"


class Player : public Component
{
public:
	Player();
	~Player() override;
	// インスタンス取得
	static Player& Instance()
	{
		static Player instance;
		return instance;
	}

	// 名前取得
	const char* GetName() const override { return "Player"; }

	// 開始処理
	void Start() override;

	// 更新処理
	void Update(float elapsedTime) override;

private:
	// キャラクター操作
	void CharacterControl(float elapsedTime);

	// カメラ操作
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