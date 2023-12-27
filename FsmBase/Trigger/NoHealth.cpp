#include "NoHealth.h"
#include "..\FsmBase.h"

bool NoHealth::HandleTrigger(FSMBase* fsm)
{
    if (fsm->_target->_hp <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void NoHealth::Init() 
{
    triggerID = TriggerID::NoHealth;
}
