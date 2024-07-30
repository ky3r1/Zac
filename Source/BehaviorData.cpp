#include "BehaviorData.h"

NodeBase* BehaviorData::PopSequenceNode()
{	
	// ��Ȃ�NULL
	if (sequenceStack.empty() != 0)
	{
		return nullptr;
	}
	NodeBase* node = sequenceStack.top();
	if (node != nullptr)
	{
		// ���o�����f�[�^���폜
		sequenceStack.pop();
	}
	return node;
}

int BehaviorData::GetSequenceStep(std::string name)
{
	if (runSequenceStepMap.count(name) == 0)
	{
		runSequenceStepMap.insert(std::make_pair(name, 0));
	}

	return runSequenceStepMap.at(name);
}

void BehaviorData::SetSequenceStep(std::string name, int step)
{
	runSequenceStepMap.at(name) = step;
}

void BehaviorData::Init()
{
	runSequenceStepMap.clear();
	while (sequenceStack.size() > 0)
	{
		sequenceStack.pop();
	}
}
