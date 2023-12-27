#pragma once
#ifndef FSMBASE_H_
#define FSMBASE_H_
#include <map>
#include <list>
#include "State.h"
#include "..\Enemy.h"


class FSMBase
{
public:
	FSMBase(Enemy* target):_target(target) {; }
	~FSMBase() { ; }
	/// <summary>
	/// 切换状态
	/// </summary>
	/// <param name="pNewState">要切换到的状态的指諄E/param>
	void ChangeState(StateID stateId)
	{
		_pCurrentState->ExitState(this);
		_pCurrentState = FindState(stateId);
		_pCurrentState->EnterState(this);
	}
	State* FindState(StateID stateId);
	void Update();
	//设置当前状态，铁赜装来链柄滞条件链眮E
	void ConfigFSM();
	
	Enemy* _target;
private:
	State* _pCurrentState;
	std::list<State*> states;

}; 
#endif // !FSMBASE_H_