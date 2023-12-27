#include "DistanceNear.h"
#include "..\FsmBase.h"
#include "..\..\player.h"

bool DistanceNear::HandleTrigger(FSMBase* fsm)
{
    if (abs(fsm->_target->_pos.x - GetPlayer()->pos.x) < 600&&abs(fsm->_target->_pos.y-GetPlayer()->pos.y)<100)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DistanceNear::Init()
{
    triggerID = TriggerID::DistanceNear;
}
