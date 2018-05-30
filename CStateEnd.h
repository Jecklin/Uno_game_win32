#ifndef CSTATEEND_H
#define CSTATEEND_H

#include "CAbState.h"

class CStateEnd:public CAbState
{
public:
    CStateEnd(FSM *fsm);
    
    void onStateEnter();
    void onStateTick();
    void onStateExit();

};

#endif // CSTATEEND_H
