#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "CCardBox.h"

CCardBox::CCardBox()
    :m_box(0)
{
    ;
}

CCardBox::~CCardBox()
{
    ;
}

CCardBox::CCardBox(const CCardBox &other)
    :m_box(other.m_box)
{
    *this = other;
}

CCardBox &CCardBox::operator =(const CCardBox &other)
{
    if (&other == this)
    {
        ;
    }
    else
    {
        this->m_box = other.m_box;
    }
    return *this;
}

void CCardBox::AddCard(const CCardInfo &card)
{
    this->m_box.push_back(card);
}

void CCardBox::RemoveCard(const CCardInfo &card)
{
    CCardBox::IterBox it_index;

    it_index = std::find(this->m_box.begin(), this->m_box.end(), card);
    if (it_index != this->m_box.end())
    {
        this->m_box.erase(it_index);
    }
    else
    {
        ;
    }
}

int CCardBox::GetSize() const
{
    return this->m_box.size();
}

bool CCardBox::IsEmpty() const
{
    return this->m_box.empty();
}

CCardBox::IterBox CCardBox::GetItBegin()
{
    return this->m_box.begin();
}

CCardBox::IterBox CCardBox::GetItEnd()
{
    return this->m_box.end();
}

void CCardBox::InitNopenBox()
{
    //初始化数字牌
    for (int index_eci = ECI_Zero; index_eci != ECI_Nine + 1; ++index_eci)      //id
    {
        CCardInfo index_rcard(ECC_Red, ECardId(index_eci), ECA_None);
        this->AddCard(index_rcard);
        this->AddCard(index_rcard);

        CCardInfo index_ycard(ECC_Yellow, ECardId(index_eci), ECA_None);
        this->AddCard(index_ycard);
        this->AddCard(index_ycard);

        CCardInfo index_gcard(ECC_Green, ECardId(index_eci), ECA_None);
        this->AddCard(index_gcard);
        this->AddCard(index_gcard);

        CCardInfo index_bcard(ECC_Blue, ECardId(index_eci), ECA_None);
        this->AddCard(index_bcard);
        this->AddCard(index_bcard);

    }

    //初始化 +2 功能牌
    CCardInfo index_atrcard(ECC_Red, ECI_AddTwo, ECA_ActionTwo);
    this->AddCard(index_atrcard);
    this->AddCard(index_atrcard);

    CCardInfo index_atycard(ECC_Yellow, ECI_AddTwo, ECA_ActionTwo);
    this->AddCard(index_atycard);
    this->AddCard(index_atycard);

    CCardInfo index_atgcard(ECC_Green, ECI_AddTwo, ECA_ActionTwo);
    this->AddCard(index_atgcard);
    this->AddCard(index_atgcard);

    CCardInfo index_atbcard(ECC_Blue, ECI_AddTwo, ECA_ActionTwo);
    this->AddCard(index_atbcard);
    this->AddCard(index_atbcard);

    //初始化 反转 功能牌
    CCardInfo index_rrcard(ECC_Red, ECI_Resverse, ECA_Reverse);
    this->AddCard(index_rrcard);
    this->AddCard(index_rrcard);

    CCardInfo index_rycard(ECC_Yellow, ECI_Resverse, ECA_Reverse);
    this->AddCard(index_rycard);
    this->AddCard(index_rycard);

    CCardInfo index_rgcard(ECC_Green, ECI_Resverse, ECA_Reverse);
    this->AddCard(index_rgcard);
    this->AddCard(index_rgcard);

    CCardInfo index_rbcard(ECC_Blue, ECI_Resverse, ECA_Reverse);
    this->AddCard(index_rbcard);
    this->AddCard(index_rbcard);

    //初始化 停止 功能牌
    CCardInfo index_srcard(ECC_Red, ECI_Stop, ECA_Stop);
    this->AddCard(index_srcard);
    this->AddCard(index_srcard);

    CCardInfo index_sycard(ECC_Yellow, ECI_Stop, ECA_Stop);
    this->AddCard(index_sycard);
    this->AddCard(index_sycard);

    CCardInfo index_sgcard(ECC_Green, ECI_Stop, ECA_Stop);
    this->AddCard(index_sgcard);
    this->AddCard(index_sgcard);

    CCardInfo index_sbcard(ECC_Blue, ECI_Stop, ECA_Stop);
    this->AddCard(index_sbcard);
    this->AddCard(index_sbcard);

    //初始化 黑牌 高级牌
    CCardInfo index_bcard(ECC_Black, ECI_Black, ECA_Black);
    this->AddCard(index_bcard);
    this->AddCard(index_bcard);
    this->AddCard(index_bcard);
    this->AddCard(index_bcard);

    //初始化 +4黑牌 高级牌
    CCardInfo index_bfcard(ECC_Black, ECI_BlackFour, ECA_BlackFour);
    this->AddCard(index_bfcard);
    this->AddCard(index_bfcard);
    this->AddCard(index_bfcard);
    this->AddCard(index_bfcard);
}

void CCardBox::RandNopenBox()
{
    IterBox it_box1;
    IterBox it_box2;
    CCardInfo index_card;
    int index_sround = 0;

    srand((unsigned int)time(nullptr));
    for (unsigned int change = 0; change < this->m_box.size(); ++change)
    {
        index_sround = rand()%(this->m_box.size() - 1);
        it_box1 = this->m_box.begin();
        it_box2 = this->m_box.begin();

        for (int i = 0; i < index_sround; ++i)
        {
            ++it_box1;
        }

        index_sround = rand()%(this->m_box.size() - 1);
        for (int i = 0; i < index_sround; ++i)
        {
            ++it_box2;
        }

        index_card = *it_box1;
        *it_box1 = *it_box2;
        *it_box2 = index_card;
    }
}

