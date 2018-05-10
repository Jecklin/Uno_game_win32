#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCardBox.h"
#include <string>

class CPlayer:public CCardBox
{
public:
    CPlayer();
    ~CPlayer();

    CPlayer(const CPlayer &other);
    CPlayer& operator =(const CPlayer &other);

public:
    int GetPlayerScore() const;
    void SetPlayerScore(int score);

    std::string GetPlayerName() const;
    void SetPlayerName(const std::string &name);

private:
    int             m_player_score;
    std::string     m_player_name;
};
#endif // CPLAYER_H
