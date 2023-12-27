#include "FsmBase.h"
#include "State.h"
#include "Trigger.h"
#include "State/Idle.h"
#include "State/FoundPlayer.h"
#include "Trigger/DistanceNear.h"
#include "Trigger/DistanceFar.h"
#include "State/FoundPlayer.h"
#include "Trigger/NoHealth.h"
#include "State/EnemyDead.h"

Idle g_Idle;
DistanceNear g_Near;
DistanceFar g_Far;
FoundPlayer g_Found;
EnemyDead g_Dead;
NoHealth g_NoHp;



State* FSMBase::FindState(StateID stateId)
{
	for (auto x : states)
	{
		if (x->_stateId== stateId)
		{
			return x;
		}
	}
	return nullptr;
}

void FSMBase::Update()
{
	if(_pCurrentState)
		_pCurrentState->StayState(this);
		_pCurrentState->TriggerCheck(this);
}

void FSMBase::ConfigFSM()
{
	g_Idle.AddMaps(TriggerID::DistanceNear,StateID::FoundPlayer);
	g_Idle.AddMaps(TriggerID::NoHealth, StateID::Dead);
	g_Idle.AddTiggerList(&g_NoHp);
	g_Idle.AddTiggerList(&g_Near);
	states.emplace_back(&g_Idle);
	g_Found.AddMaps(TriggerID::DistanceFar, StateID::Idle);
	g_Found.AddMaps(TriggerID::NoHealth, StateID::Dead);
	g_Found.AddTiggerList(&g_NoHp);
	g_Found.AddTiggerList(&g_Far);
	states.push_back(&g_Found);
	states.emplace_back(&g_Dead);
	_pCurrentState = &g_Idle;
	ChangeState(StateID::Idle);
}


