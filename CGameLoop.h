#ifndef CGAMELOOP_H
#define CGAMELOOP_H

#include "FSM.h"
#include "CAbState.h"

class CGameLoop
{
public:
    CGameLoop();
    ~CGameLoop();
    void                    gameStart();

private:    
    FSM                     *m_fsm;
    CAbState                *m_stateWait;
    CAbState                *m_stateStart;
    CAbState                *m_stateMy;
    CAbState                *m_stateOther;
    CAbState                *m_stateAdd;
    CAbState                *m_stateSub;
    CAbState                *m_stateEnd;

};
#endif // CGAMELOOP_H
