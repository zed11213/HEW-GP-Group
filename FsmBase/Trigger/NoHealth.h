#pragma once
#include "..\Trigger.h"
class NoHealth:public Trigger
{
public:
	NoHealth() 
	{ 
		Init();
	}
	~NoHealth() { ; }

private:

	// ͨ�� Trigger �̳�
	bool HandleTrigger(FSMBase* fsm) override;

	void Init() override;

};
