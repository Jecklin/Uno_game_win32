#include "CGameLoop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CTest.h"
using namespace std;

CGameLoop::CGameLoop()
    :m_player_count(4)
    ,m_toward(1)
    ,m_current(0)
    ,m_box_notopen()
    ,m_box_hasopen()
    ,m_endcard()
    ,m_players()
    ,m_winner()
    ,m_banker()
{
    ;
}

CGameLoop::~CGameLoop()
{
    ;
}
void CGameLoop::GameStart()
{
    this->GameMenu();
    this->GameInit();
    this->GameLoop();
    this->GameOver();
}
void CGameLoop::GameMenu()
{
    cout << "**********  Uno Begin  **********" << endl;
}

void CGameLoop::GameInit()
{
    cout << "**********  Game Init  **********" << endl;
    CCardBox::IterBox it_nbox;
    CCardInfo card_index;
    int len_nbox = 0;

    //InitPlayerName
    this->m_players[0].SetPlayerName("*Zero*");
    this->m_players[1].SetPlayerName("*One*");
    this->m_players[2].SetPlayerName("*Two*");
    this->m_players[3].SetPlayerName("*Three*");

    //InitNopenBox
    this->m_box_notopen.InitNopenBox();
    this->m_box_notopen.RandNopenBox();

    //InitEndCard
    bool end_is_black = false;
    do
    {
        it_nbox = this->m_box_notopen.GetItBegin();
        len_nbox = this->m_box_notopen.GetSize();

        srand((unsigned int)time(nullptr));
        int index_sround = rand()%(len_nbox - 1);

        for (int i = 0; i < index_sround; ++i)
        {
            ++it_nbox;
        }
        card_index = *it_nbox;

    }while(end_is_black);

    this->m_endcard.SetAction(card_index.GetAction());
    this->m_endcard.SetColor(card_index.GetColor());
    this->m_endcard.SetId(card_index.GetId());

    //InitBanker
    srand((unsigned int)time(nullptr));
    this->m_current = rand() % 3;
    this->m_banker = this->m_players[this->m_current];

    //RoundOne
    for (int round = 0; round < 7; ++round)
    {
        for (int i = 0; i < 4; ++i)
        {
            it_nbox = this->m_box_notopen.GetItBegin();
            card_index = *it_nbox;

            this->m_players[i].AddCard(card_index);
            this->m_box_notopen.RemoveCard(card_index);

        }
    }

    //*测试  ******************************************//
    CTest test;
    cout << "end card: ";
    test.PrintCard(this->m_endcard);
    cout << endl;

    cout << "banker: " << this->m_banker.GetPlayerName() << endl;

    for (int i = 0; i < 4; ++i)
    {
        CPlayer player;
        player = this->m_players[i];
        test.PrintPlayer(player);
    }
    //*************************************************//
}

void CGameLoop::GameLoop()
{
    cout << "**********  Game Loop  **********" << endl;
    CPlayer *pplayer = nullptr;
    do
    {
        pplayer = &this->m_players[this->m_current];
        //**1.判定当前玩家是否为胜者
        if (pplayer->IsEmpty())
        {
            this->m_winner = *pplayer;
            break;
        }
        else
        {
            ;
        }

        //**2.玩家出牌
        if (this->m_current == 0)       //我出牌
        {
            this->MyRound(pplayer);
        }
        else                           //电脑出牌
        {
            this->OtherRound(pplayer);
        }


        //**3.设置下一玩家
        this->m_current += this->m_toward;

        if (this->m_current > this->m_player_count - 1)
        {
            this->m_current -= this->m_player_count;
        }
        else if (this->m_current < 0)
        {
            this->m_current += this->m_player_count;
        }
        else
        {
            ;
        }

    }while(true);

    //**4.统计玩家分数
    int score = 0;
    for (int index = 0; index < this->m_player_count; ++index)
    {
        pplayer = &this->m_players[index];
        score = pplayer->GetPlayerScore() - pplayer->GetSize();
        pplayer->SetPlayerScore(score);
    }
    this->m_winner.SetPlayerScore(this->m_winner.GetPlayerScore() + 10);

}

void CGameLoop::GameOver()
{
    cout << "**********  Game Over  **********" << endl;
    cout << "The winner is:" << this->m_winner.GetPlayerName() << endl;
    cout << "The players's scores are: " << endl;
    for (int index = 0; index < this->m_player_count; ++index)
    {
        CPlayer player = this->m_players[index];
        cout << player.GetPlayerName() << " : " << player.GetPlayerScore() << endl;
    }
}

void CGameLoop::MyRound(CPlayer *pplayer)
{
    CCardBox::IterBox it_box;
    CCardInfo out_card;
    CTest test;
    int number = 0;
    int choice = 0;

    cout << "-------------------------------" << endl;
    cout << "Now you have " << pplayer->GetSize() << " cards: " << endl;

    for (it_box = pplayer->GetItBegin(); it_box != pplayer->GetItEnd(); ++it_box)
    {
        cout << number << " : ";
        test.PrintCard(*it_box);
        ++number;
    }

    cout << endl << "The end card is: " ;
    test.PrintCard(this->m_endcard);
    cout << endl << "Which one you want out? (No card out, put in 111)";
    cin >> choice;
    do
    {
        it_box = pplayer->GetItBegin();
        for (int index = 0; index < choice; ++index)
        {
            ++it_box;
        }

        out_card = *it_box;

        //牌可出，出牌
        if ( (out_card.GetColor() & this->m_endcard.GetColor())
             ||(out_card.GetId() == this->m_endcard.GetId()))
        {
            //已出牌库加牌
            this->m_box_hasopen.AddCard(out_card);

            //设置底牌
            this->m_endcard.SetAction(out_card.GetAction());
            this->m_endcard.SetColor(out_card.GetColor());
            this->m_endcard.SetId(out_card.GetId());

            //我出牌
            pplayer->RemoveCard(out_card);

            //执行功能牌
            if (out_card.GetAction() & 0xF)
            {
                this->FunctionCardAction(out_card);
            }
            else
            {
                ;
            }

            break;
        }
        //选择不出，摸牌
        else if (number == 111)
        {
            CCardInfo add_card;
            CCardBox::IterBox it_not_box = this->m_box_notopen.GetItBegin();
            if (this->m_box_notopen.IsEmpty())
            {
                this->RecycleOpenBox();;
            }
            add_card = *it_not_box;
            pplayer->AddCard(add_card);
            this->m_box_notopen.RemoveCard(add_card);
            break;
        }
        //牌不可出，重新选
        else
        {
            cout << "This card cann't out";
        }

        cout << "Which one you want out? (No card out, put in 111)";
        cin >> choice;

    }while(number != 111);
}

void CGameLoop::OtherRound(CPlayer *pplayer)
{
    CCardBox::IterBox it_box;
    CCardInfo out_card;
    CCardInfo index_card;
    bool allow_out = false;

    //查询电脑牌库
    for (it_box = pplayer->GetItBegin(); it_box != pplayer->GetItEnd(); ++it_box)
    {
        index_card = *it_box;

        if ( (index_card.GetColor() & this->m_endcard.GetColor())
             ||(index_card.GetId() == this->m_endcard.GetId()))
        {
            allow_out = true;
            out_card = index_card;
            break;
        }
        else
        {
            ;
        }
    }

    //电脑出牌
    if (allow_out)
    {
        //已出牌库加牌
        this->m_box_hasopen.AddCard(out_card);

        //变换底牌
        this->m_endcard.SetAction(out_card.GetAction());
        this->m_endcard.SetColor(out_card.GetColor());
        this->m_endcard.SetId(out_card.GetId());

        //玩家牌库减牌
        pplayer->RemoveCard(out_card);

        //*********** 测试 ************//
        cout << pplayer->GetPlayerName() << " Out card: ";
        CTest test;
        test.PrintCard(out_card);
        cout << endl;
        //****************************//

        if (out_card.GetAction() & 0xF)
        {
            this->FunctionCardAction(out_card);
        }
        else
        {
            ;
        }
        allow_out = false;
    }

    //电脑摸牌
    else
    {
        CCardInfo add_card;
        CCardBox::IterBox it_not_box = this->m_box_notopen.GetItBegin();
        if (this->m_box_notopen.IsEmpty())
        {
            this->RecycleOpenBox();;
        }
        add_card = *it_not_box;
        pplayer->AddCard(add_card);
        this->m_box_notopen.RemoveCard(add_card);

        //*********** 测试 ************//
        cout << pplayer->GetPlayerName() << " In card: ";
        CTest test;
        test.PrintCard(add_card);
        cout << endl;
        //****************************//
    }
}

void CGameLoop::FunctionCardAction(const CCardInfo &card)
{
    if (card.GetId() == ECI_AddTwo)
    {
        this->ActionCardIn(2);
        this->ActionCardStop();
    }
    else if (card.GetId() == ECI_Resverse)
    {
        this->ActionCardReverse();
    }
    else if (card.GetId() == ECI_Stop)
    {
        this->ActionCardStop();
    }
    else if (card.GetId() == ECI_Black)
    {
        this->ActionCardChangeColor();
        this->ActionCardStop();
    }
    else if (card.GetId() == ECI_BlackFour)
    {
        this->ActionCardChangeColor();
        this->ActionCardIn(4);
        this->ActionCardStop();
    }
    else
    {
        ;
    }
}

void CGameLoop::ActionCardIn(int num)
{
    int action_state = this->m_current + this->m_toward;

    if (action_state > this->m_player_count - 1)
    {
        action_state -= this->m_player_count;
    }
    else if (action_state < 0)
    {
        action_state += this->m_player_count;
    }
    else
    {
        ;
    }

    CPlayer *pplayer_act = &this->m_players[action_state];
    CCardInfo action_card;
    CCardBox::IterBox it_box_not;
    for (int touch = 0; touch < num; ++touch)
    {
        if (this->m_box_notopen.IsEmpty())
        {
            this->RecycleOpenBox();
        }

        it_box_not = this->m_box_notopen.GetItBegin();
        action_card = *it_box_not;

        pplayer_act->AddCard(action_card);
        this->m_box_notopen.RemoveCard(action_card);


        //*********** 测试 ************//
        cout << pplayer_act->GetPlayerName() << " In card: ";
        CTest test;
        test.PrintCard(action_card);
        cout << endl;
        //****************************//
    }
    pplayer_act = nullptr;
}

void CGameLoop::ActionCardStop()
{
    this->m_current += this->m_toward;

    if (this->m_current > this->m_player_count - 1)
    {
        this->m_current -= this->m_player_count;
    }
    else if (this->m_current < 0)
    {
        this->m_current += this->m_player_count;
    }
    else
    {
        ;
    }

    //*********** 测试 ************//
    cout << this->m_players[m_current].GetPlayerName() << " Stop " << endl;
    //****************************//

}

void CGameLoop::ActionCardReverse()
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
    cout << "** Action ** --- Reverse" << endl;
}

void CGameLoop::ActionCardChangeColor()
{
    CPlayer *pplayer_act = &this->m_players[this->m_current];
    CCardBox::IterBox it_box = pplayer_act->GetItBegin();
    CCardInfo index_card;

    int sum_red    = 0;
    int sum_yellow = 0;
    int sum_blue   = 0;
    int sum_green  = 0;

    for (it_box = pplayer_act->GetItBegin(); it_box != pplayer_act->GetItEnd(); ++it_box)
    {
        index_card = *it_box;
        if (index_card.GetColor() == ECC_Red)
        {
            ++sum_red;
        }
        else if (index_card.GetColor() == ECC_Yellow)
        {
            ++sum_yellow;
        }
        else if (index_card.GetColor() == ECC_Blue)
        {
            ++sum_blue;
        }
        else if (index_card.GetColor() == ECC_Green)
        {
            ++sum_green;
        }
    }

    int max_color_name = 0;
    int max_sum = sum_red;
    int color[4] = {sum_red, sum_yellow, sum_blue, sum_green};

    for (int index = 1; index < 4; ++index)
    {
        if (color[index] > max_sum)
        {
            max_color_name = index;
            max_sum = color[index];
        }
    }

    if (max_color_name == 0)
    {
        this->m_endcard.SetColor(ECC_Red);

        //*********** 测试 ************//
        cout << "Change color to Red" << endl;
        //****************************//
    }
    else if(max_color_name == 1)
    {
        this->m_endcard.SetColor(ECC_Yellow);

        //*********** 测试 ************//
        cout << "Change color to Yellow" << endl;
        //****************************//
    }
    else if (max_color_name == 2)
    {
        this->m_endcard.SetColor(ECC_Blue);

        //*********** 测试 ************//
        cout << "Change color to Blue" << endl;
        //****************************//
    }
    else if (max_color_name == 3)
    {
        this->m_endcard.SetColor(ECC_Green);

        //*********** 测试 ************//
        cout << "Change color to Green" << endl;
        //****************************//
    }
    else
    {
        ;
    }

    pplayer_act = nullptr;
}

void CGameLoop::RecycleOpenBox()
{
    cout << "**********  Recycle Open Box  **********" << endl;
    CCardInfo index_card;
    CCardBox::IterBox it_open;

    for (it_open = this->m_box_hasopen.GetItBegin(); it_open != this->m_box_hasopen.GetItEnd(); ++it_open)
    {
        index_card = *it_open;
        this->m_box_notopen.AddCard(index_card);
        this->m_box_hasopen.RemoveCard(index_card);
    }
    this->m_box_notopen.RandNopenBox();
}

