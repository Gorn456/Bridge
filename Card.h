//
// Created by kamil on 3/28/24.
//

#ifndef BRIDGE_CARD_H
#define BRIDGE_CARD_H

enum class Rank {
    DEUCE,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

enum class Suit {
    CLUB,
    DIAMOND,
    HEART,
    SPADE
};


class Card {
private:
    Rank rank ;
    Suit suit ;
    char rank_symbol ;
    char suit_symbol ;
public:
    Card(Rank _rank, Suit _suit) ;

    Rank getRank() const ;

    Suit getSuit() const ;

    char getRank_symbol() const ;

    char getSuit_symbol() const ;
};


#endif //BRIDGE_CARD_H
