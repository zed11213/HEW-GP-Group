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


	// ͨ�� Trigger �̳�
	bool HandleTrigger(FSMBase* fsm) override;

	void Init() override;

};
