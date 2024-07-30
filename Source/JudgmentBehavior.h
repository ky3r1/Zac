#pragma once
#include "Actor.h"

// Às”»’è
class JudgmentBase: public Component
{
public:
	JudgmentBase() {}
	virtual bool Judgment() = 0;
protected:
};

// BattleNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
class BattleJudgment : public JudgmentBase
{
public:
	BattleJudgment(){};
	// ”»’è
	bool Judgment();
};

// AttackNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
class AttackJudgment : public JudgmentBase
{
public:
	AttackJudgment() {};
	// ”»’è
	bool Judgment();
};

// SkillNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
class SkillShotJudgment : public JudgmentBase
{
public:
	SkillShotJudgment(){};
	// ”»’è
	bool Judgment();
};

// WanderNode‚É‘JˆÚ‚Å‚«‚é‚©”»’è
class WanderJudgment : public JudgmentBase
{
public:
	WanderJudgment(){};
	// ”»’è
	bool Judgment();
};


// Escape‚É‘JˆÚ‚Å‚«‚é‚©”»’è
class EscapeJudgment : public JudgmentBase
{
public:
	EscapeJudgment() {};
	// ”»’è
	bool Judgment();
};