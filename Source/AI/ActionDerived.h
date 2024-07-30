#pragma once
#include "ActionBase.h"
#include "Enemy.h"

// �ʏ�U��
class NormalAction : public ActionBase
{
public:
	NormalAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// �X�L���U���s��
class SkillAction : public ActionBase
{
public:
	SkillAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// �ǐՍs��
class PursuitAction : public ActionBase
{
public:
	PursuitAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// �p�j�s��
class WanderAction : public ActionBase
{
public:
	WanderAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// �ҋ@�s��
class IdleAction : public ActionBase
{
public:
	IdleAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// �����s��
class LeaveAction : public ActionBase
{
public:
	LeaveAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};

// �񕜍s��
class RecoverAction : public ActionBase
{
public:
	RecoverAction(Enemy* enemy) :ActionBase(enemy) {}
	ActionBase::State Run(float elapsedTime);
};