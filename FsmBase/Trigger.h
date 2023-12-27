#pragma once
#include"TriggerID.h"

class FSMBase;
class Trigger
{
public:
	TriggerID triggerID;
	virtual ~Trigger() { ; }
	virtual bool HandleTrigger(FSMBase *fsm) = 0;
	virtual void Init() = 0;
};