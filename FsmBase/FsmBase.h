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
	/// �л�״̬
	/// </summary>
	/// <param name="pNewState">Ҫ�л�����״̬��ָՁE/param>
	void ChangeState(StateID stateId)
	{
		_pCurrentState->ExitState(this);
		_pCurrentState = FindState(stateId);
		_pCurrentState->EnterState(this);
	}
	State* FindState(StateID stateId);
	void Update();
	//���õ�ǰ״̬������װ����������������E
	void ConfigFSM();
	
	Enemy* _target;
private:
	State* _pCurrentState;
	std::list<State*> states;

}; 
#endif // !FSMBASE_H_