#include "EnemyDead.h"
#include "..\..\item.h"

void EnemyDead::Init()
{
	_stateId = StateID::Dead;
}

void EnemyDead::EnterState(FSMBase* fsm)
{                
	
}

void EnemyDead::StayState(FSMBase* fsm)
{
	fsm->_target->_use = false;
	int itemRan = RandomPercent(33, 33, 33);
	switch (itemRan)
	{
	case 1:
		SetItem(fsm->_target->_pos.x, fsm->_target->_pos.y, ITEM_TYPE_PAPER);
		break;
		SetItem(fsm->_target->_pos.x, fsm->_target->_pos.y, ITEM_TYPE_PAPER2);
		break;
		SetItem(fsm->_target->_pos.x, fsm->_target->_pos.y, ITEM_TYPE_PAPER3);
		break;
	default:
		break;
	}
}

void EnemyDead::ExitState(FSMBase* fsm)
{
}
