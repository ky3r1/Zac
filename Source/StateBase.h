#pragma once
#pragma once
#include "Actor.h"
#include <vector>

class State
{
public:
	// コンストラクタ
	State(Actor* actor) :owner(actor) {}
	virtual ~State() {}
	// 全て継承先で実装させる必要があるため純粋仮想関数で実装
	// ステートに入った時のメソッド
	virtual void Enter() = 0;
	// ステートで実行するメソッド
	virtual void Execute(float elapsedTime) = 0;
	// ステートから出ていくときのメソッド
	virtual void Exit() = 0;
	//Anim_num変更
	void SetAnimNum(int num) { anim_num = num; }
protected:
	Actor* owner = nullptr;
	int health = 0;
	int anim_num = 0;
};

class HierarchicalState :public State
{
public:
	HierarchicalState(Actor* actor) :State(actor) {}
	virtual ~HierarchicalState() {}
	// 全て継承先で実装させる必要があるため純粋仮想関数で実装
	// ステートに入った時のメソッド
	virtual void Enter() = 0;
	// ステートで実行するメソッド
	virtual void Execute(float elapsedTime) = 0;
	// ステートから出ていくときのメソッド
	virtual void Exit() = 0;
	//サブステート登録
	virtual void SetSubState(int newState);
	//サブステート変更
	virtual void ChangeSubState(int newState);
	//サブステート登録
	virtual void RegisterSubState(State* state);
	//サブステート取得
	virtual State* GetSubState() { return subState; }
	//サブステート番号取得
	virtual int GetSubStateIndex();
protected:
	std::vector<State*> subStatePool;
	State* subState = nullptr;
};