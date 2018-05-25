#ifndef CGAMELOOP_H
#define CGAMELOOP_H

#include "CPlayer.h"
#include "CCardInfoEnd.h"
#include <vector>

class CGameLoop
{
public:
    CGameLoop();
    ~CGameLoop();
    typedef std::list<CCardInfo> CBox;

public:
    void        gameStart();
    CPlayer     getPlayer(int number);
    CCardInfo   getEndCard();

private:
    //Loop
    void        gameMenu();
    void        gameInit();
    void        gameLoop();
    void        gameOver();

    //Round
    void        myRound();
    void        otherRound();

    //Member variable method
    void        initCloseBox();
    void        randCloseBox();
    void        openBoxRecycle();
    void        initEndCard();
    void        initPlayersName();
    void        roundOne();

    //Rules
    void        initCurrent();
    int         getNextState();
    void        cardActions();
    void        actInCard(int num);
    void        actStop();
    void        actReverse();
    void        actChangeColor();


private:
    CBox                    m_box_close;                    //未起牌库
    CBox                    m_box_open;                     //已出牌库
    CCardInfoEnd            m_endcard;                      //底牌
    std::vector<CPlayer>    m_players;                      //玩家数组
    int                     m_winner;                       //赢家位置标识
    int                     m_toward;                       //出牌方向标识
    int                     m_current;                      //当前出牌玩家位置

};
#endif // CGAMELOOP_H
