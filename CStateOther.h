#ifndef CSTATEOTHER_H
#define CSTATEOTHER_H

#include "CAbState.h"

class CStateOther:public CAbState
{
public:
    CStateOther(FSM *fsm);
    
    void onStateEnter();
    void onStateTick();
    void onStateExit();
    
};

#endif // CSTATEOTHER_H
