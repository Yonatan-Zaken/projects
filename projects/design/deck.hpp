#include <boost/shared_ptr.hpp>

namespace ilrd
{

/****************************** Card Definition *******************************/

class Card
{
public:
    enum RANK
    {
        ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    };

    enum SUIT
    {
        SPADE, CLUB, DIAMOND, HEART
    };

    explicit Card();
    RANK GetRank() const;
    SUIT GetSuit() const;

protected:
    void SetRank(RANK rank);
    void SetSuit(SUIT suit);

private:
    RANK m_rank;
    SUIT m_suit;
};

/****************************** Deck Definition *******************************/

class Deck
{
public:
    explicit Deck();
    void Shuffle();
    virtual void Deal() = 0;
private:
    boost::shared_ptr<Card[]> m_cards;
}

} // namespce ilrd



