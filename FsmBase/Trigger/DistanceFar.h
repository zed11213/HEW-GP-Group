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


	// ͨ�� Trigger �̳�
	bool HandleTrigger(FSMBase* fsm) override;

	void Init() override;

};
