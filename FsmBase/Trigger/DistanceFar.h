#pragma once
#include "..\Trigger.h"

class DistanceFar:public Trigger
{
public:
	DistanceFar()
	{
		Init();
	}

	~DistanceFar()
	{
	}

private:


	// Í¨¹ý Trigger ¼Ì³Ð
	bool HandleTrigger(FSMBase* fsm) override;

	void Init() override;

};
