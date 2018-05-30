#ifndef CSTATEWAIT_H
#define CSTATEWAIT_H

#include "CAbState.h"

class CStateWait:public CAbState
{
public:
    CStateWait(FSM *fsm);

    void onStateEnter();
    void onStateTick();
    void onStateExit();
};

#endif // CSTATEWAIT_H
