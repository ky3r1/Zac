#pragma once
#include "ActionBase.h"
#include "Enemy.h"

// 通常攻撃
class NormalAction : public ActionBase
{
public:
	NormalAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// スキル攻撃行動
class SkillAction : public ActionBase
{
public:
	SkillAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// 追跡行動
class PursuitAction : public ActionBase
{
public:
	PursuitAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// 徘徊行動
class WanderAction : public ActionBase
{
public:
	WanderAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// 待機行動
class IdleAction : public ActionBase
{
public:
	IdleAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// 逃走行動
class LeaveAction : public ActionBase
{
public:
	LeaveAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// 回復行動
class RecoverAction : public ActionBase
{
public:
	RecoverAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};