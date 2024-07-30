#pragma once
#include "All.h"
#include "Actor.h"
#include "Component.h"
// 行動処理基底クラス
class ActionBase :public Component
{
public:
	// 名前取得
	virtual const char* GetName() const override { return "ActionBase"; }
	// 実行情報
	enum class State
	{
		Run,		// 実行中
		Failed,		// 実行失敗
		Complete,	// 実行成功
	};

	// 実行処理(純粋仮想関数)
	virtual ActionBase::State Run(float elapsedTime) {}
protected:
	int step = 0;
};

// 通常攻撃
class NormalAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// スキル攻撃行動
class SkillAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// 追跡行動
class PursuitAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// 徘徊行動
class WanderAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// 待機行動
class IdleAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// 逃走行動
class LeaveAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};

// 回復行動
class RecoverAction : public ActionBase
{
public:
	ActionBase::State Run(float elapsedTime)override;
};