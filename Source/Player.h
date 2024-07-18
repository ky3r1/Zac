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

	// カメラ操作
	void CameraControl(float elapsedTime);
};