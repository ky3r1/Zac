#pragma once
#include "All.h"
#include "Actor.h"
#include "Component.h"
// �s���������N���X
class ActionBase :public Component
{
public:
	// ���O�擾
	virtual const char* GetName() const override { return "ActionBase"; }
	// ���s���
	enum class State
	{
		Run,		// ���s��
		Failed,		// ���s���s
		Complete,	// ���s����
	};

	// ���s����(�������z�֐�)
	virtual ActionBase::State Run(float elapsedTime) {}
protected:
	int step = 0;
};

// �ʏ�U��
class NormalAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// �X�L���U���s��
class SkillAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// �ǐՍs��
class PursuitAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// �p�j�s��
class WanderAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// �ҋ@�s��
class IdleAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// �����s��
class LeaveAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// �񕜍s��
class RecoverAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};