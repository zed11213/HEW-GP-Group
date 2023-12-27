#include "DistanceFar.h"
#include "..\..\player.h"
#include "..\FsmBase.h"

bool DistanceFar::HandleTrigger(FSMBase* fsm)
{
	if (abs(fsm->_target->_pos.x - GetPlayer()->pos.x) >= 650 || (fsm->_target->_Tile[6].attrib == MAP_ATTRIB_NONE || fsm->_target->_Tile[8].attrib == MAP_ATTRIB_NONE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DistanceFar::Init()
{
	triggerID = TriggerID::DistanceFar;
}
