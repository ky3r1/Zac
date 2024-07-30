#pragma once
#include "Component.h"

// 実行判定
class JudgmentBase: public Component
{
public:
	JudgmentBase() {}
	virtual bool Judgment() = 0;
protected:
};

// BattleNodeに遷移できるか判定
class BattleJudgment : public JudgmentBase
{
public:
	BattleJudgment(){};
	// 判定
	bool Judgment();
};

// AttackNodeに遷移できるか判定
class AttackJudgment : public JudgmentBase
{
public:
	AttackJudgment() {};
	// 判定
	bool Judgment();
};

// SkillNodeに遷移できるか判定
class SkillShotJudgment : public JudgmentBase
{
public:
	SkillShotJudgment(){};
	// 判定
	bool Judgment();
};

// WanderNodeに遷移できるか判定
class WanderJudgment : public JudgmentBase
{
public:
	WanderJudgment(){};
	// 判定
	bool Judgment();
};


// Escapeに遷移できるか判定
class EscapeJudgment : public JudgmentBase
{
public:
	EscapeJudgment() {};
	// 判定
	bool Judgment();
};