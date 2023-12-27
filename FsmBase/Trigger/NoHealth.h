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

	// Í¨¹ý Trigger ¼Ì³Ð
	bool HandleTrigger(FSMBase* fsm) override;

	void Init() override;

};
