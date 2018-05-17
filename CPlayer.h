#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCardBox.h"
#include <string>

class CPlayer
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

    CCardBox GetPlayerBox() const;
    void SetPlayerBox(const CCardBox &box);

private:
    CCardBox        m_player_box;
    int             m_player_score;
    std::string     m_player_name;
};
#endif // CPLAYER_H
