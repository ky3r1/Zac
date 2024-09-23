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

// ShortAttackNode�ɑJ�ڂł��邩����
class ShortAttackJudgment : public JudgmentBase
{
public:
	ShortAttackJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// ����
	bool Judgment();
};

// LongAttackNode�ɑJ�ڂł��邩����
class LongAttackJudgment : public JudgmentBase
{
public:
	LongAttackJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
	// ����
	bool Judgment();
};

//// SkillNode�ɑJ�ڂł��邩����
//class SkillShotJudgment : public JudgmentBase
//{
//public:
//	SkillShotJudgment(Enemy* enemy) :JudgmentBase(enemy) {};
//	// ����
//	bool Judgment();
//};

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