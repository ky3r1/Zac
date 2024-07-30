#pragma once

class Enemy;

// �s���������N���X
class ActionBase
{
public:
	ActionBase(Enemy* enemy):owner(enemy){}
	// ���s���
	enum class State
	{
		Run,		// ���s��
		Failed,		// ���s���s
		Complete,	// ���s����
	};

	// ���s����(�������z�֐�)
	virtual ActionBase::State Run(float elapsedTime) = 0;
protected:
	Enemy* owner;
	int step = 0;
};
