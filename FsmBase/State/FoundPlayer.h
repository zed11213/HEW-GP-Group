#pragma once
#include"..\State.h"
class FoundPlayer:public State
{
public:
	FoundPlayer()
	{
		Init();
	}

	~FoundPlayer() { ; }

	// ͨ�� State �̳�
	void Init() override;

	void EnterState(FSMBase* fsm) override;

	void StayState(FSMBase* fsm) override;

	void ExitState(FSMBase* fsm) override;

};
