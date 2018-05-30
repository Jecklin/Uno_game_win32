#include "CStateMy.h"


CStateMy::CStateMy(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateMy::onStateEnter()
{
    test_counter = 0;
    m_pfsm->showMyPrompt();
}

void CStateMy::onStateTick()
{
//    test_counter++;
//    可以设置定时器，暂未添加
    do
    {
        int choice;
        cout << "Out number:(111 to give up) ";
        cin >> choice;
     
        bool is_giveup = m_pfsm->curPlayerGiveUp(choice);
        if (is_giveup)
        {
            m_pfsm->transState(m_pfsm->State_Add);
            break;
        }
        else
        {
            bool is_allow = m_pfsm->curPlayerAllowOut(choice);
            if (is_allow)
            {
                m_pfsm->transState(m_pfsm->State_Sub);
                break;
            }
            else
            {
                cout << "Not allow" << endl;
            }
        }
    }while(true);
    
}

void CStateMy::onStateExit()
{
    ;
}
