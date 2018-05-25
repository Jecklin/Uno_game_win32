#include "CGameLoop.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

CGameLoop::CGameLoop()
    :m_box_close()
    ,m_box_open()
    ,m_endcard()
    ,m_players(4)
    ,m_winner(-1)
    ,m_toward(1)
    ,m_current(0)
{
    ;
}

CGameLoop::~CGameLoop()
{
    ;
}
void CGameLoop::gameStart()
{
    this->gameMenu();

    this->gameInit();
    //Test
    for (int i = 0; i < 4; ++i)
    {
        CPlayer player = this->m_players[i];
        player.printPlayer();
    }

    this->gameLoop();
    this->gameOver();

}

CPlayer CGameLoop::getPlayer(int number)
{
    return this->m_players[number];
}

CCardInfo CGameLoop::getEndCard()
{
    return this->m_endcard;
}


void CGameLoop::gameMenu()
{
    ;
}

void CGameLoop::gameInit()
{
    //InitPlayerName
    this->initPlayersName();

    //InitCloseBox
    this->initCloseBox();
    this->randCloseBox();

    //InitEndCard
    this->initEndCard();

    //InitBanker
    this->initCurrent();

    //RoundOne
    this->roundOne();

}


void CGameLoop::gameLoop()
{
    do
    {
        //1. Round
        if (this->m_current == 0)       //my
        {
            this->myRound();
        }
        else                           //conputer
        {
            this->otherRound();
        }

        //2. Current player is winner or not
        if (this->m_winner != -1)
        {
            break;
        }
        else
        {
            ;
        }

        //3. Set next player
        this->m_current = this->getNextState();

    }while(true);

}

void CGameLoop::gameOver()
{
    CPlayer *pplayer    = nullptr;

    //other player sub score
    for (unsigned int index = 0; index < this->m_players.size(); ++index)
    {
        pplayer = &(this->m_players[index]);
        pplayer->playerSubScore();
    }

    //winner add score
    pplayer = &(this->m_players[this->m_winner]);
    pplayer->playerAddScore();

    //List
    cout << endl << "*****************   Game over!  ****************" << endl;
    cout << "The winner is: " << pplayer->playerGetName() << endl << endl;
    cout << "*********  The list: ************ " << endl;
    for (int i = 0; i < 4; ++i)
    {
        CPlayer player = this->m_players[i];
        player.printPlayer();
    }

}

void CGameLoop::myRound()
{
    CPlayer *pplayer                          = &(this->m_players[this->m_current]);
    std::list<CCardInfo>::iterator iter_close = this->m_box_close.end();
    CCardInfo                      card_touch = *(--iter_close);
    CCardInfo                      card_out;
    bool                           is_giveup  = false;
    int                            choice = 0;

    //Prompt information
    cout << endl << "Now is your round:" << endl;
    cout << "The end card is: " ;
    pplayer->printCard(this->m_endcard);
    cout << endl;
    cout << "Your box now: " << endl;
    pplayer->printPlayer();

    do
    {
        cout << "Out number(111 to give up) : ";
        cin >> choice;

        //Choice give up
        if (choice == 111)
        {
            is_giveup = true;
        }
        else
        {
            ;
        }

        //Give up
        if (is_giveup)
        {
            pplayer->playerInCard(card_touch);
            this->m_box_close.pop_back();
            break;
        }
        else
        {
            ;
        }

        //Out Card
        card_out = pplayer->getNumCard(choice);
        if (pplayer->isAllowOut(card_out, this->m_endcard))
        {
            this->m_box_open.push_back(card_out);
            this->m_endcard.setCard(card_out);
            pplayer->playerOutCard(card_out);

            //Current player is winner?
            if (pplayer->getBoxSize() == 0)
            {
                this->m_winner = this->m_current;
            }
            else
            {
                ;
            }

            //Do card action
            if (card_out.isFunctionCard())
            {
                this->cardActions();
            }
            else
            {
                ;
            }

            break;
        }

        //Out card error
        else
        {
            cout << "Out Card Error.Choice another card: " << endl;
        }

    }while(true);

}

void CGameLoop::otherRound()
{
    CPlayer     *pplayer = &(this->m_players[this->m_current]);
    CCardInfo   card;

    //Player allow out
    if (pplayer->isAllowOut(this->m_endcard))
    {
        //Out card
        card = pplayer->getSimilarCard(this->m_endcard);
        this->m_box_open.push_back(card);
        this->m_endcard.setCard(card);
        pplayer->playerOutCard(card);

        //Current player is winner?
        if (pplayer->getBoxSize() == 0)
        {
            this->m_winner = this->m_current;
        }
        else
        {
            ;
        }

        //Do card action
        if (card.isFunctionCard())
        {
            this->cardActions();
        }
        else
        {
            ;
        }

        //Test
        cout << pplayer->playerGetName() << " out card: ";
        pplayer->printCard(card);
        cout << endl;

    }

    //Player not allow out
    else
    {
        std::list<CCardInfo>::iterator iter = this->m_box_close.end();
        --iter;
        card = *iter;
        pplayer->playerInCard(card);
        this->m_box_close.pop_back();

        //Test
        cout << pplayer->playerGetName() << " in card: ";
        pplayer->printCard(card);
        cout << endl;
    }
}

void CGameLoop::initCloseBox()
{
    //初始化数字牌
    for (int index_eci = ECI_Zero; index_eci != ECI_Nine + 1; ++index_eci)      //id
    {
        CCardInfo index_rcard(ECC_Red, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_rcard);
        this->m_box_close.push_back(index_rcard);

        CCardInfo index_ycard(ECC_Yellow, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_ycard);
        this->m_box_close.push_back(index_ycard);

        CCardInfo index_gcard(ECC_Green, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_gcard);
        this->m_box_close.push_back(index_gcard);

        CCardInfo index_bcard(ECC_Blue, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_bcard);
        this->m_box_close.push_back(index_bcard);

    }

    //初始化 +2 功能牌
    CCardInfo index_atrcard(ECC_Red, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atrcard);
    this->m_box_close.push_back(index_atrcard);

    CCardInfo index_atycard(ECC_Yellow, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atycard);
    this->m_box_close.push_back(index_atycard);

    CCardInfo index_atgcard(ECC_Green, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atgcard);
    this->m_box_close.push_back(index_atgcard);

    CCardInfo index_atbcard(ECC_Blue, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atbcard);
    this->m_box_close.push_back(index_atbcard);

    //初始化 反转 功能牌
    CCardInfo index_rrcard(ECC_Red, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rrcard);
    this->m_box_close.push_back(index_rrcard);

    CCardInfo index_rycard(ECC_Yellow, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rycard);
    this->m_box_close.push_back(index_rycard);

    CCardInfo index_rgcard(ECC_Green, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rgcard);
    this->m_box_close.push_back(index_rgcard);

    CCardInfo index_rbcard(ECC_Blue, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rbcard);
    this->m_box_close.push_back(index_rbcard);

    //初始化 停止 功能牌
    CCardInfo index_srcard(ECC_Red, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_srcard);
    this->m_box_close.push_back(index_srcard);

    CCardInfo index_sycard(ECC_Yellow, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_sycard);
    this->m_box_close.push_back(index_sycard);

    CCardInfo index_sgcard(ECC_Green, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_sgcard);
    this->m_box_close.push_back(index_sgcard);

    CCardInfo index_sbcard(ECC_Blue, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_sbcard);
    this->m_box_close.push_back(index_sbcard);

    //初始化 黑牌 高级牌
    CCardInfo index_bcard(ECC_Black, ECI_Black, ECA_Black);
    this->m_box_close.push_back(index_bcard);
    this->m_box_close.push_back(index_bcard);
    this->m_box_close.push_back(index_bcard);
    this->m_box_close.push_back(index_bcard);

    //初始化 +4黑牌 高级牌
    CCardInfo index_bfcard(ECC_Black, ECI_BlackFour, ECA_BlackFour);
    this->m_box_close.push_back(index_bfcard);
    this->m_box_close.push_back(index_bfcard);
    this->m_box_close.push_back(index_bfcard);
    this->m_box_close.push_back(index_bfcard);
}

void CGameLoop::randCloseBox()
{
    std::list<CCardInfo>::iterator iter_one;
    std::list<CCardInfo>::iterator iter_two;
    CCardInfo                      card_index;
    unsigned int                   sround = 0;

    srand((unsigned int)time(nullptr));
    for (unsigned int change = 0; change < 1000; ++change)  //change < this->m_box_close.size()
    {
        //move iter_one
        sround = rand() % (this->m_box_close.size() - 1);
        iter_one = this->m_box_close.begin();
        for (unsigned int i = 0; i < sround; ++i )
        {
            ++iter_one;
        }

        //move iter_two
        sround = rand() % (this->m_box_close.size() - 1);
        iter_two = this->m_box_close.end();
        --iter_two;
        for (unsigned int i = 0; i < sround; ++i )
        {
            --iter_two;
        }

        //change
        card_index = *iter_one;
        *iter_one = *iter_two;
        *iter_two = card_index;
    }
}

void CGameLoop::openBoxRecycle()
{
    std::list<CCardInfo>::iterator iter_open;
    CCardInfo                      card;
    do
    {
        iter_open = this->m_box_open.end();
        --iter_open;
        card = *iter_open;

        this->m_box_close.push_back(card);
        this->m_box_open.pop_back();

    }while(!this->m_box_open.empty());
}

void CGameLoop::initEndCard()
{
    std::list<CCardInfo>::iterator iter;
    unsigned int                   sround = 0;
    CCardInfo                      card_index;

    do
    {
        //Get srand card
        iter = this->m_box_close.begin();
        srand((unsigned int)time(nullptr));
        sround = rand() % (this->m_box_close.size() - 1);

        //Move card
        for (unsigned int move = 0; move < sround; ++ move)
        {            
            ++iter;
        }
        card_index = *iter;

        //Card is black or not
        if (card_index.getColor() == ECC_Black)
        {
            ;
        }
        else
        {
            break;
        }

    }while(true);

    //Set end card
    this->m_endcard.setCard(card_index);
}

void CGameLoop::initPlayersName()
{
    CPlayer   *gi_player;
    gi_player = &(this->m_players[0]);
    gi_player->playerSetName("*Tom*");

    gi_player = &(this->m_players[1]);
    gi_player->playerSetName("*Jack*");

    gi_player = &(this->m_players[2]);
    gi_player->playerSetName("*Anna*");

    gi_player = &(this->m_players[3]);
    gi_player->playerSetName("*Lili*");
}

void CGameLoop::roundOne()
{
    CPlayer                         *pplayer;
    CCardInfo                       card;
    std::list<CCardInfo>::iterator  iter;

    for (int round = 0; round < 7; ++round)
    {
        for (unsigned int i = 0; i < this->m_players.size(); ++i)
        {
            iter = this->m_box_close.end();
            --iter;
            pplayer = &(this->m_players[i]);
            card = *iter;

            pplayer->playerInCard(card);
            this->m_box_close.pop_back();
        }
    }
}

void CGameLoop::initCurrent()
{
    srand((unsigned int)time(nullptr));
    this->m_current = rand()%(this->m_players.size() - 1);
}

int CGameLoop::getNextState()
{
    int next = this->m_current + this->m_toward;
    if (next > 3 )//this->m_players.size() - 1
    {
        next -= this->m_players.size();
    }
    else if (next < 0)
    {
        next += this->m_players.size();
    }
    else
    {
        ;
    }
    return next;
}

void CGameLoop::cardActions()
{
    if (this->m_endcard.getId() == ECI_AddTwo)
    {
        this->actInCard(2);
        this->actStop();
    }
    else if (this->m_endcard.getId() == ECI_Resverse)
    {
        this->actReverse();
    }
    else if (this->m_endcard.getId() == ECI_Stop)
    {
        this->actStop();
    }
    else if (this->m_endcard.getId() == ECI_Black)
    {
        this->actChangeColor();
        this->actStop();
    }
    else if (this->m_endcard.getId() == ECI_BlackFour)
    {
        this->actChangeColor();
        this->actInCard(4);
        this->actStop();
    }
}

void CGameLoop::actInCard(int num)
{
    CPlayer                         *pplayer_next = &(this->m_players[this->getNextState()]);
    CCardInfo                       card;
    std::list<CCardInfo>::iterator  iter          = this->m_box_close.end();

    for (int touch = 0; touch < num; ++touch)
    {
        if (this->m_box_close.empty())
        {
            this->openBoxRecycle();
        }
        else
        {
            ;
        }

        --iter;
        card = *iter;

        pplayer_next->playerInCard(card);
        this->m_box_close.pop_back();
    }
}

void CGameLoop::actStop()
{
    this->m_current = this->getNextState();
}

void CGameLoop::actReverse()
{
    if (this->m_toward == 1)
    {
        this->m_toward = -1;
    }
    else if (this->m_toward == -1)
    {
        this->m_toward = 1;
    }
    else
    {
        ;
    }
}

void CGameLoop::actChangeColor()
{
    CPlayer *pplayer_cur = &(this->m_players[this->m_current]);
    this->m_endcard.setColor(pplayer_cur->getChangeColor());
}




