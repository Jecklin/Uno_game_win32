#ifndef CCARDBOX_H
#define CCARDBOX_H

#include "datatypedefine.h"
#include "CCardInfo.h"
#include <list>

class CCardBox
{
public:
    CCardBox();
    virtual ~CCardBox();

    CCardBox(const CCardBox &other);
    CCardBox &operator = (const CCardBox &other);

public:
    typedef std::list<CCardInfo>::iterator IterBox;

    void AddCard(const CCardInfo &card);
    void RemoveCard(const CCardInfo &card);

    int GetSize() const;
    bool IsEmpty() const;
    IterBox GetItBegin();
    IterBox GetItEnd();

public:
    void InitNopenBox();
    void RandNopenBox();

protected:
    std::list<CCardInfo>          m_box;
};

#endif // CCARDBOX_H
