#include "CCardInfoEnd.h"

CCardInfoEnd::CCardInfoEnd()
{
    ;
}

CCardInfoEnd::~CCardInfoEnd()
{
    ;
}

void CCardInfoEnd::setCard(const CCardInfo &card)
{
    this->m_action = card.getAction();
    this->m_color = card.getColor();
    this->m_id = card.getId();
}

void CCardInfoEnd::setColor(const ECardColor color)
{
    this->m_color = color;
}

