#pragma once
#pragma once
#include "Actor.h"
#include <vector>

class State
{
public:
	// �R���X�g���N�^
	State(Actor* actor) :owner(actor) {}
	virtual ~State() {}
	// �S�Čp����Ŏ���������K�v�����邽�ߏ������z�֐��Ŏ���
	// �X�e�[�g�ɓ��������̃��\�b�h
	virtual void Enter() = 0;
	// �X�e�[�g�Ŏ��s���郁�\�b�h
	virtual void Execute(float elapsedTime) = 0;
	// �X�e�[�g����o�Ă����Ƃ��̃��\�b�h
	virtual void Exit() = 0;
	//Anim_num�ύX
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
	// �S�Čp����Ŏ���������K�v�����邽�ߏ������z�֐��Ŏ���
	// �X�e�[�g�ɓ��������̃��\�b�h
	virtual void Enter() = 0;
	// �X�e�[�g�Ŏ��s���郁�\�b�h
	virtual void Execute(float elapsedTime) = 0;
	// �X�e�[�g����o�Ă����Ƃ��̃��\�b�h
	virtual void Exit() = 0;
	//�T�u�X�e�[�g�o�^
	virtual void SetSubState(int newState);
	//�T�u�X�e�[�g�ύX
	virtual void ChangeSubState(int newState);
	//�T�u�X�e�[�g�o�^
	virtual void RegisterSubState(State* state);
	//�T�u�X�e�[�g�擾
	virtual State* GetSubState() { return subState; }
	//�T�u�X�e�[�g�ԍ��擾
	virtual int GetSubStateIndex();
protected:
	std::vector<State*> subStatePool;
	State* subState = nullptr;
};