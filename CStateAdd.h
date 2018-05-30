#ifndef CSTATEADD_H
#define CSTATEADD_H

#include "CAbState.h"

class CStateAdd:public CAbState
{
public:
    CStateAdd(FSM *fsm);
    
    void onStateEnter();
    void onStateTick();
    void onStateExit();
    
};

#endif // CSTATEADD_H
