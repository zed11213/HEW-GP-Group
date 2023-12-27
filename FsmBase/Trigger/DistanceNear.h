#pragma once
#include "..\Trigger.h"

class DistanceNear:public Trigger
{
public:
	DistanceNear()
	{
		Init();
	}

	~DistanceNear()
	{
	}

private:


	// Í¨¹ý Trigger ¼Ì³Ð
	bool HandleTrigger(FSMBase* fsm) override;

	void Init() override;

};
