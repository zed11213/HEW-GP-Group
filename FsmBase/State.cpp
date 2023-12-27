#include "State.h"
#include "FsmBase.h"

void State::AddMaps(TriggerID tId, StateID sId)
{
	maps.insert(std::pair<TriggerID, StateID>(tId, sId));
}

void State::AddTiggerList(Trigger* pTrigger)
{
	triggers.push_back(pTrigger);
}

void State::TriggerCheck(FSMBase* fsm)
{
	for (auto it = triggers.begin(); it != triggers.end(); ++it)
	{
		if ((*it)->HandleTrigger(fsm))
		{
			StateID stateid = maps[(*it)->triggerID];
			fsm->ChangeState(stateid);
		}
	}
}
