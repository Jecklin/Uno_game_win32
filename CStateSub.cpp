#include "CStateSub.h"

CStateSub::CStateSub(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateSub::onStateEnter()
{
    ;
}

void CStateSub::onStateTick()
{   
    m_pfsm->curPlayerOutCard();
    
    if (m_pfsm->hasWinner())
    {
        m_pfsm->transState(m_pfsm->State_End);
    }
    else
    {
        m_pfsm->transState(m_pfsm->State_Wait);
    }
    
}

void CStateSub::onStateExit()
{
    ;
}


