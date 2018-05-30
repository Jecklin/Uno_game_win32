#include "CStateEnd.h"

CStateEnd::CStateEnd(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateEnd::onStateEnter()
{
    this->m_pfsm->setAllScores();
    //在这里出去
}

void CStateEnd::onStateTick()
{
    ;
}

void CStateEnd::onStateExit()
{
    ;
}
