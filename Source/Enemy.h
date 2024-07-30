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

//Gl~[
class Enemy : public Character
{
public:
	Enemy() {}
    ~Enemy() override {}
	// ¼Oæ¾
	virtual const char* GetName() const override { return "Enemy"; }

	// Jn
	void Start() override;

	// XV
	void Update(float elapsedTime) override;

	// GUI`æ
	virtual void DrawImGui() override;

	void DrawDebug() override;
public:
    // õÍÍ
    float GetSearchRange() const { return search_range; }
    void SetSearchRange(float range) { search_range = range; }
	// UÍÍ
	float GetAttackRange() const { return attack_range; }
	void SetAttackRange(float range) { attack_range = range; }
protected:
	float search_range = 10.0f;
	float attack_range = 4.0f;
};