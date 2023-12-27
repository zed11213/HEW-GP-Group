#pragma once
#ifndef STATE_H_
#define STATE_H_
#include<map>
#include<list>
#include "Trigger.h"
#include "TriggerID.h"
#include "StateID.h"


class FSMBase;
class State
{
public:
	std::map<TriggerID, StateID> maps;
	std::list<Trigger*> triggers;
	StateID _stateId;
	virtual ~State() { ; }
	virtual void Init()= 0;										//��Init�����ֱ�ЁE�StateId���и�ֵ
	virtual void EnterState(FSMBase* fsm) = 0;
	virtual void StayState(FSMBase* fsm) = 0;
	virtual void ExitState(FSMBase* fsm) = 0;
	void AddMaps(TriggerID tId, StateID sId);
	void AddTiggerList(Trigger* pTrigger);
	//��E������Ƿ���?
	void TriggerCheck(FSMBase* fsm);
};
#endif // !STATE_H