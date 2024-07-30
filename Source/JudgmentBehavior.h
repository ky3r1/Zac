#pragma once
#include "Actor.h"

// ���s����
class JudgmentBase: public Component
{
public:
	JudgmentBase() {}
	virtual bool Judgment() = 0;
protected:
};

// BattleNode�ɑJ�ڂł��邩����
class BattleJudgment : public JudgmentBase
{
public:
	BattleJudgment(){};
	// ����
	bool Judgment();
};

// AttackNode�ɑJ�ڂł��邩����
class AttackJudgment : public JudgmentBase
{
public:
	AttackJudgment() {};
	// ����
	bool Judgment();
};

// SkillNode�ɑJ�ڂł��邩����
class SkillShotJudgment : public JudgmentBase
{
public:
	SkillShotJudgment(){};
	// ����
	bool Judgment();
};

// WanderNode�ɑJ�ڂł��邩����
class WanderJudgment : public JudgmentBase
{
public:
	WanderJudgment(){};
	// ����
	bool Judgment();
};


// Escape�ɑJ�ڂł��邩����
class EscapeJudgment : public JudgmentBase
{
public:
	EscapeJudgment() {};
	// ����
	bool Judgment();
};