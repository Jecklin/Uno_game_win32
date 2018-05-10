#ifndef CCARDINFO_H
#define CCARDINFO_H

#include "datatypedefine.h"

class CCardInfo
{
public:
    CCardInfo();
    CCardInfo(ECardColor color, ECardId id, ECardAction action);
    virtual ~CCardInfo();

    CCardInfo(const CCardInfo &other);
    CCardInfo& operator=(const CCardInfo &other);
    bool operator ==(const CCardInfo &other);

public:
    ECardColor GetColor() const;
    ECardId GetId() const;
    ECardAction GetAction() const;

protected:
    ECardColor   m_color;
    ECardId      m_id;
    ECardAction  m_action;
};
#endif // CCARDINFO_H
