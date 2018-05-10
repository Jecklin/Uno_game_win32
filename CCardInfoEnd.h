#ifndef CCARDINFOEND_H
#define CCARDINFOEND_H
#include "CCardInfo.h"

class CCardInfoEnd:public CCardInfo
{
public:
    CCardInfoEnd();
    ~CCardInfoEnd();

public:
    void SetColor(ECardColor color);
    void SetId(ECardId id);
    void SetAction(ECardAction action);
};

#endif // CCARDINFOEND_H
