#pragma once
#include "Graphics/Shader.h"
#include "Character.h"
#include "Player.h"

enum class EnemySlimeAnimation
{
	Hit,
	Walk,
	Attack01,
	Death,
};

enum
{
	Enemy01_Num,
	Enemy02_Num,
	Enemy03_Num,
	EnemyBoss_Num,
};

//エネミー
class Enemy : public Character
{
public:
	Enemy() {}
    ~Enemy() override {}
	// 名前取得
	virtual const char* GetName() const override { return "Enemy"; }

	// 開始処理
	void Start() override;

	// 更新処理
	void Update(float elapsedTime) override;

	// GUI描画
	virtual void DrawImGui() override;

	void DrawDebug() override;
public:
    // 検索範囲
    float GetSearchRange() const { return search_range; }
    void SetSearchRange(float range) { search_range = range; }
protected:
	float search_range = 10.0f;
};