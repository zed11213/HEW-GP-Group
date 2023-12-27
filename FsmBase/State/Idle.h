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
	// Í¨¹ý State ¼Ì³Ð
	void Init() override;

	void EnterState(FSMBase* fsm) override;

	void StayState(FSMBase* fsm) override;

	void ExitState(FSMBase* fsm) override;

};
