#ifndef CPLAYER_H
#define CPLAYER_H

#include <string>

#include <list>
#include "CCardInfo.h"

class CPlayer
{
public:
    CPlayer();
    ~CPlayer();
    CPlayer(const CPlayer &other);
    CPlayer& operator =(const CPlayer &other);

public:
    typedef std::list<CCardInfo> CBox;

    //Score
    int             playerGetScore() const;
    void            playerAddScore();
    void            playerSubScore();

    //Name
    std::string     playerGetName() const;
    void            playerSetName(const std::string &name);

    //Action
    bool            isAllowOut(const CCardInfo &card);
    bool            isAllowOut(const CCardInfo &my_card, const CCardInfo &end_card);
    void            playerOutCard(const CCardInfo &card);
    void            playerInCard(const CCardInfo &card);
    CCardInfo       getSimilarCard(const CCardInfo &card);
    CCardInfo&      getNumCard(int num);

    //Loop
    ECardColor      getChangeColor() const;
    int             getBoxSize() const;

    //Test
    void            printPlayer();
    void            printCard(const CCardInfo &card);

private:
    int             m_score;
    std::string     m_name;
    CBox            m_box;
};
#endif // CPLAYER_H
