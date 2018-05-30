#include "CStateOther.h"


CStateOther::CStateOther(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateOther::onStateEnter()
{    
    m_pfsm->printCurBox();
}

void CStateOther::onStateTick()
{   
    bool is_allow = false;
    is_allow = m_pfsm->curPlayerAllowOut();
    if (is_allow)
    {
        m_pfsm->transState(m_pfsm->State_Sub);
    }
    else
    {
        m_pfsm->transState(m_pfsm->State_Add);
    }
    
}

void CStateOther::onStateExit()
{
    ;
}
