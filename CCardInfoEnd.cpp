#include "CCardInfoEnd.h"

CCardInfoEnd::CCardInfoEnd()
{
    ;
}

CCardInfoEnd::~CCardInfoEnd()
{
    ;
}

void CCardInfoEnd::SetColor(ECardColor color)
{
    this->m_color = color;
}

void CCardInfoEnd::SetId(ECardId id)
{
    this->m_id = id;
}

void CCardInfoEnd::SetAction(ECardAction action)
{
    this->m_action = action;
}
