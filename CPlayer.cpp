#include "CPlayer.h"
#include <iostream>

CPlayer::CPlayer()
    :m_score()
    ,m_name()
    ,m_box()
    ,m_outcard()
{
    ;
}

CPlayer::~CPlayer()
{
    ;
}

CPlayer::CPlayer(const CPlayer &other)
{
    *this = other;
}

CPlayer &CPlayer::operator =(const CPlayer &other)
{
    if (this == &other)
    {
        ;
    }
    else
    {
        this->m_score = other.m_score;
        this->m_name = other.m_name;
        this->m_box = other.m_box;
    }
    return *this;
}

//Score
int CPlayer::playerGetScore() const
{
    return this->m_score;
}

void CPlayer::playerAddScore()
{
    this->m_score += 10;
}

void CPlayer::playerSubScore()
{
    this->m_score -= this->m_box.size();
}

//Name
std::string CPlayer::playerGetName() const
{
    return this->m_name;
}

void CPlayer::playerSetName(const std::string &name)
{
    this->m_name = name;
}

//Action
bool CPlayer::isAllowOut(const CCardInfo &card)
{
    bool is_allow = false;
    CCardInfo card_index;
    std::list<CCardInfo>::iterator iter;

    //end card is black
    if ((card.getId() == ECI_Black) || (card.getId() == ECI_BlackFour))
    {
        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
        {
            card_index = *iter;
            if (card_index.getColor() & card.getColor())
            {
                is_allow = true;
                this->m_outcard = card_index;
            }
            else
            {
                ;
            }

        }
    }

    //end card is normal
    else
    {
        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
        {
            card_index = *iter;
            if ((card_index.getId() == card.getId()) || (card_index.getColor() & card.getColor()))
            {
                is_allow = true;
                this->m_outcard = card_index;
            }
            else
            {
                ;
            }
        }
    }
    return is_allow;
}

bool CPlayer::isAllowOut(const CCardInfo &my_card, const CCardInfo &end_card)
{
    bool is_allow = false;
    //end card is black
    if ((end_card.getId() == ECI_Black) || (end_card.getId() == ECI_BlackFour))
    {
        if (my_card.getColor() & end_card.getColor())
        {
            is_allow = true;
            this->m_outcard = my_card;
        }
        else
        {
            ;
        }
    }

    //end card is normal
    else
    {
        if ((my_card.getId() == end_card.getId()) || (my_card.getColor() & end_card.getColor()) )
        {
            is_allow = true;
            this->m_outcard = my_card;
        }
        else
        {
            ;
        }
    }
    return is_allow;
}

CCardInfo CPlayer::getOutCard()
{
    return this->m_outcard;
}

void CPlayer::playerOutCard(const CCardInfo &card)
{
    std::list<CCardInfo>::iterator iter;
    CCardInfo card_index;
    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
    {
        card_index = *iter;
        if (card == card_index)
        {
            this->m_box.erase(iter);
            
            //Test
            std::cout << this->m_name << " Out card: ";
            this->printCard(card);
            std::cout << std::endl;
            
            break;
        }
        else
        {
            ;
        }
    }

}

void CPlayer::playerInCard(const CCardInfo &card)
{
    this->m_box.push_back(card);
    
    //Test
    std::cout << this->m_name << " In card: ";
    this->printCard(card);
    std::cout << std::endl;
}

CCardInfo CPlayer::getSimilarCard(const CCardInfo &card)
{
    CCardInfo card_index;
    CCardInfo card_return;
    std::list<CCardInfo>::iterator iter;

    //end card is black
    if ((card.getId() == ECI_Black) || (card.getId() == ECI_BlackFour))
    {
        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
        {
            card_index = *iter;
            if (card_index.getColor() & card.getColor())
            {
                card_return = card_index;
            }
            else
            {
                ;
            }

        }
    }

    //end card is normal
    else
    {
        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
        {
            card_index = *iter;
            if ((card_index.getId() == card.getId()) || (card_index.getColor() & card.getColor()))
            {
                card_return = card_index;
            }
            else
            {
                ;
            }
        }
    }
    return card_return;

}

CCardInfo& CPlayer::getNumCard(int num)
{
    std::list<CCardInfo>::iterator iter = this->m_box.begin();

    for (int n = 0; n < num; ++n)
    {
        ++iter;
    }

    return *iter;
}

//Player
ECardColor CPlayer::getChangeColor() const
{
    std::list<CCardInfo>::const_iterator iter;
    CCardInfo   index_card;
    ECardColor  return_color;

    int         sum_red    = 0;
    int         sum_yellow = 0;
    int         sum_blue   = 0;
    int         sum_green  = 0;

    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
    {
        index_card = *iter;
        if (index_card.getColor() == ECC_Red)
        {
            ++sum_red;
        }
        else if (index_card.getColor() == ECC_Yellow)
        {
            ++sum_yellow;
        }
        else if (index_card.getColor() == ECC_Blue)
        {
            ++sum_blue;
        }
        else if (index_card.getColor() == ECC_Green)
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
        return_color = ECC_Red;
    }
    else if(max_color_name == 1)
    {
        return_color = ECC_Yellow;
    }
    else if (max_color_name == 2)
    {
        return_color = ECC_Blue;
    }
    else if (max_color_name == 3)
    {
        return_color = ECC_Green;
    }
    else
    {
        ;
    }
    return return_color;
}

int CPlayer::getBoxSize() const
{
    return this->m_box.size();
}

void CPlayer::printPlayer()
{
    std::list<CCardInfo>::iterator iter;
    CCardInfo card;
    int i = 0;

    std::cout << "Name: " << this->playerGetName() << " ";
    std::cout << "Score: " << this->playerGetScore() << " ";
    std::cout << "Box: " << "(" << this->getBoxSize() << "): " << std::endl;
    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
    {
        std::cout << i << " : ";
        card = *iter;
        this->printCard(card);
        ++i;
    }
    std::cout << std::endl << std::endl;

}

void CPlayer::printCard(const CCardInfo &card)
{
    if (card.getColor() == ECC_Red)
    {
        std::cout << "R";
    }
    else if (card.getColor() == ECC_Yellow)
    {
        std::cout << "Y";
    }
    else if (card.getColor() == ECC_Blue)
    {
        std::cout << "B";
    }
    else if (card.getColor() == ECC_Green)
    {
        std::cout << "G";
    }
    else if (card.getColor() == ECC_Black)
    {
        std::cout << "BLACK";
    }


    std::cout << " ";


    if (card.getId() == ECI_Zero)
    {
        std::cout << "0";
    }
    else if (card.getId() == ECI_One)
    {
        std::cout << "1";
    }
    else if (card.getId() == ECI_Two)
    {
        std::cout << "2";
    }
    else if (card.getId() == ECI_Three)
    {
        std::cout << "3";
    }
    else if (card.getId() == ECI_Four)
    {
        std::cout << "4";
    }
    else if (card.getId() == ECI_Five)
    {
        std::cout << "5";
    }
    else if (card.getId() == ECI_Six)
    {
        std::cout << "6";
    }
    else if (card.getId() == ECI_Seven)
    {
        std::cout << "7";
    }
    else if (card.getId() == ECI_Eight)
    {
        std::cout << "8";
    }
    else if (card.getId() == ECI_Nine)
    {
        std::cout << "9";
    }
    else if (card.getId() == ECI_AddTwo)
    {
        std::cout << "+2";
    }
    else if (card.getId() == ECI_Resverse)
    {
        std::cout << "reverse";
    }
    else if (card.getId() == ECI_Stop)
    {
        std::cout << "stop";
    }
    else if (card.getId() == ECI_Black)
    {
        std::cout << "black";
    }
    else if (card.getId() == ECI_BlackFour)
    {
        std::cout << "black+4";
    }
    else
    {
        ;
    }

    std::cout << "   ";
}
