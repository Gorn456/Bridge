//
// Created by kamil on 3/28/24.
//

#ifndef BRIDGE_CARD_H
#define BRIDGE_CARD_H

#include <iostream>

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
    SPADE,
    NT // bez atu
};

std::ostream& operator<<(std::ostream& os, const Suit& suit) ;
std::ostream& operator<<(std::ostream& os, const Rank& rank) ;


class Card {
private:
    Rank rank ;
    Suit suit ;
public:
    int strength ;

    Card(Rank _rank, Suit _suit, int _strength) ;
    Card(Rank _rank, Suit _suit) ;
    Card(char _rank, char _suit) ;
    Card() = default;

    Rank getRank() const ;

    Suit getSuit() const ;

};

std::istream& operator>>(std::istream& is, Card& card) ;
bool operator==(const Card& lhs, const Card& rhs) ;


#endif //BRIDGE_CARD_H
