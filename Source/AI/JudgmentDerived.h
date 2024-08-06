#pragma once
#include "JudgmentBase.h"
//#include "EnemyBlueSlime.h"
#include "Enemy.h"


// BattleNode�ɑJ�ڂł��邩����
class BattleJudgment : public JudgmentBase
{
public:
	BattleJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// ����
	bool Judgment();
};

// AttackNode�ɑJ�ڂł��邩����
class AttackJudgment : public JudgmentBase
{
public:
	AttackJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// ����
	bool Judgment();
};

//// AttackNode�ɑJ�ڂł��邩����
//class AdjacentAttackJudgment : public JudgmentBase
//{
//public:
//	AdjacentAttackJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
//	// ����
//	bool Judgment();
//};

// SkillNode�ɑJ�ڂł��邩����
class SkillShotJudgment : public JudgmentBase
{
public:
	SkillShotJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// ����
	bool Judgment();
};

// WanderNode�ɑJ�ڂł��邩����
class WanderJudgment : public JudgmentBase
{
public:
	WanderJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// ����
	bool Judgment();
};


// Escape�ɑJ�ڂł��邩����
class EscapeJudgment : public JudgmentBase
{
public:
	EscapeJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// ����
	bool Judgment();
};