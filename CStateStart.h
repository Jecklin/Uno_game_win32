#ifndef CSTATESTART_H
#define CSTATESTART_H

#include "CAbState.h"

class CStateStart:public CAbState
{
public:
    CStateStart(FSM *fsm);
    
    void onStateEnter();
    void onStateTick();
    void onStateExit();

};

#endif // CSTATESTART_H
