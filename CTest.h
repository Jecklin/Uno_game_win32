#ifndef CTEST_H
#define CTEST_H
#include "CPlayer.h"

class CTest
{
public:
    CTest();
    ~CTest();

public:
    void PrintCard(CCardInfo &card);
    void PrintBox(CCardBox &box);
    void PrintPlayer(CPlayer &player);

};

#endif // CTEST_H
