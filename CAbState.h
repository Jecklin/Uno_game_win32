#ifndef CABSTATE_H
#define CABSTATE_H

#include <iostream>
#include "FSM.h"

using namespace std;

class FSM;

class CAbState
{
public:
    CAbState(FSM *pfsm)
    {
        m_pfsm = pfsm;
    }
    virtual ~CAbState(){}
    
public:
    virtual void onStateEnter() = 0;
    virtual void onStateTick()  = 0;
    virtual void onStateExit()  = 0;
    
protected:
    FSM     *m_pfsm;
};

#endif // CABSTATE_H
