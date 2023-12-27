#pragma once
#include "..\State.h"
class Idle:public State
{
public:
	Idle()
	{
		Init();
	}
	~Idle()override { ; }
	// ͨ�� State �̳�
	void Init() override;

	void EnterState(FSMBase* fsm) override;

	void StayState(FSMBase* fsm) override;

	void ExitState(FSMBase* fsm) override;

};
