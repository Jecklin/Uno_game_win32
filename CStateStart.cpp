#include "CStateStart.h"

CStateStart::CStateStart(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateStart::onStateEnter()
{
    ;
}

void CStateStart::onStateTick()
{
    
    if (m_pfsm->curIsMy())
    {
        m_pfsm->transState(m_pfsm->State_My);
    }
    else
    {
        m_pfsm->transState(m_pfsm->State_Other);
    }

}

void CStateStart::onStateExit()
{
    ;
}


