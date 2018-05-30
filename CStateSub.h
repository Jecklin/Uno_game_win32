#ifndef CSTATESUB_H
#define CSTATESUB_H

#include "CAbState.h"

class CStateSub:public CAbState
{
public:
    CStateSub(FSM *fsm);
    
    void onStateEnter();
    void onStateTick();
    void onStateExit();

};

#endif // CSTATESUB_H
