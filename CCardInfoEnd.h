#ifndef CCARDINFOEND_H
#define CCARDINFOEND_H

#include "CCardInfo.h"

class CCardInfoEnd:public CCardInfo
{
public:
    CCardInfoEnd();
    ~CCardInfoEnd();

public:
    void setColor(const ECardColor color);
    void setCard(const CCardInfo &card);
};

#endif // CCARDINFOEND_H
