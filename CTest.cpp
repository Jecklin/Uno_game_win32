#include "CTest.h"
#include <iostream>
using namespace std;

CTest::CTest()
{
    ;
}

CTest::~CTest()
{
    ;
}

void CTest::PrintCard(CCardInfo &card)
{
    string color;
    if (card.GetColor() == ECC_Red)
    {
        color = "R";
    }
    else if (card.GetColor() == ECC_Yellow)
    {
        color = "Y";
    }
    else if (card.GetColor() == ECC_Blue)
    {
        color = "B";
    }
    else if (card.GetColor() == ECC_Green)
    {
        color = "G";
    }
    else if (card.GetColor() == ECC_Black)
    {
        color = "BL";
    }
    else
    {
        ;
    }

    string id;
    if (card.GetId() == ECI_Zero)
    {
        id = "0";
    }
    else if (card.GetId() == ECI_One)
    {
        id = "1";
    }
    else if (card.GetId() == ECI_Two )
    {
        id = "2";
    }
    else if (card.GetId() == ECI_Three )
    {
        id = "3";
    }
    else if (card.GetId() == ECI_Four )
    {
        id = "4";
    }
    else if (card.GetId() == ECI_Five)
    {
        id = "5";
    }
    else if (card.GetId() == ECI_Six)
    {
        id = "6";
    }
    else if (card.GetId() == ECI_Seven)
    {
        id = "7";
    }
    else if (card.GetId() == ECI_Eight)
    {
        id = "8";
    }
    else if (card.GetId() == ECI_Nine )
    {
        id = "9";
    }
    else if (card.GetId() == ECI_AddTwo )
    {
        id = "add_2";
    }
    else if (card.GetId() == ECI_Resverse )
    {
        id = "reverse";
    }
    else if (card.GetId() == ECI_Stop)
    {
        id = "stop";
    }
    else if (card.GetId() == ECI_Black )
    {
        id = "black";
    }
    else if (card.GetId() == ECI_BlackFour )
    {
        id = "black_4";
    }
    else
    {
        ;
    }
    cout << color << "  "
         << id << "  "
         << "\t";
}

void CTest::PrintBox(CCardBox &box)
{
    CCardBox::IterBox it;
    CCardInfo card;
    cout << "box: "
         << "( " << box.GetSize() << " )" << endl;
    for (it = box.GetItBegin(); it != box.GetItEnd(); ++it)
    {
        card = *it;
        this->PrintCard(card);
    }
    cout << endl;

}

void CTest::PrintPlayer(CPlayer &player)
{
    CCardBox::IterBox it;
    CCardInfo card;
    cout << "name: " << player.GetPlayerName() << " "
         << "score:" << player.GetPlayerScore() << " "
         << "box size: " << player.GetSize() << endl;
    cout << "cards:" << endl;
    for (it = player.GetItBegin(); it != player.GetItEnd(); ++it)
    {
        card = *it;
        this->PrintCard(card);
    }
    cout << endl;

}
