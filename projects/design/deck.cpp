
#include "deck.hpp"

namespace ilrd
{

/****************************** Card Implement ********************************/

Card::Card(RANK rank, SUIT suit):
    m_rank(rank),
    m_suit(suit)
{}
    
RANK Card::GetRank() const
{
    return m_rank;
}

SUIT Card::GetSuit() const
{
    return m_suit;
}

/****************************** Deck Implement ********************************/

Deck::Deck():
    m_cards(new Card[52])
{}

} // namespace ilrd

