#pragma once

#include "Scene.h"
#include "Spown.h"
#include "CameraController.h"
#include "Graphics/Sprite.h"
#include "Graphics/Font.h"

// ゲームシーン
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// 初期化
	void Initialize() override;

	// 終了化
	void Finalize() override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;
private:
	std::unique_ptr<Spown> spown = nullptr;
	std::unique_ptr<Sprite> gauge = nullptr;
	std::unique_ptr<Font> font;

	CameraController camera_controller;

	int mapcategory = 0;

	bool checker_actor[6] = {};
	bool checker_control = {};
};