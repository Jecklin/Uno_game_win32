#include "CStateAdd.h"

CStateAdd::CStateAdd(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateAdd::onStateEnter()
{
    ;
}

void CStateAdd::onStateTick()
{
    m_pfsm->curPlayerInCard();
    m_pfsm->transState(m_pfsm->State_Wait);     
}

void CStateAdd::onStateExit()
{
    ;
}
