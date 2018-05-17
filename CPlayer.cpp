#include "CPlayer.h"

CPlayer::CPlayer()
    :m_player_box()
    ,m_player_score()
    ,m_player_name()
{
    ;
}

CPlayer::~CPlayer()
{
    ;
}

CPlayer::CPlayer(const CPlayer &other)
{
    *this = other;
}

CPlayer &CPlayer::operator =(const CPlayer &other)
{
    if (this == &other)
    {
        ;
    }
    else
    {
        this->m_player_box = other.m_player_box;
        this->m_player_name = other.m_player_name;
        this->m_player_score = other.m_player_score;
    }
    return *this;
}

int CPlayer::GetPlayerScore() const
{
    return this->m_player_score;
}

void CPlayer::SetPlayerScore(int score)
{
    this->m_player_score += score;
}

std::string CPlayer::GetPlayerName() const
{
    return this->m_player_name;
}

void CPlayer::SetPlayerName(const std::string &name)
{
    this->m_player_name = name;
}

CCardBox CPlayer::GetPlayerBox() const
{
    return this->m_player_box;
}

void CPlayer::SetPlayerBox(const CCardBox &box)
{
    this->m_player_box = box;
}
