#pragma once
#include "JudgmentBase.h"
//#include "EnemyBlueSlime.h"
#include "Enemy.h"


// BattleNodeに遷移できるか判定
class BattleJudgment : public JudgmentBase
{
public:
	BattleJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// 判定
	bool Judgment();
};

// AttackNodeに遷移できるか判定
class AttackJudgment : public JudgmentBase
{
public:
	AttackJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// 判定
	bool Judgment();
};

// ShortAttackNodeに遷移できるか判定
class ShortAttackJudgment : public JudgmentBase
{
public:
	ShortAttackJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// 判定
	bool Judgment();
};

// LongAttackNodeに遷移できるか判定
class LongAttackJudgment : public JudgmentBase
{
public:
	LongAttackJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// 判定
	bool Judgment();
};

//// SkillNodeに遷移できるか判定
//class SkillShotJudgment : public JudgmentBase
//{
//public:
//	SkillShotJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
//	// 判定
//	bool Judgment();
//};

// WanderNodeに遷移できるか判定
class WanderJudgment : public JudgmentBase
{
public:
	WanderJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// 判定
	bool Judgment();
};


// Escapeに遷移できるか判定
class EscapeJudgment : public JudgmentBase
{
public:
	EscapeJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// 判定
	bool Judgment();
};