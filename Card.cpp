//
// Created by kamil on 3/28/24.
//

#include "Card.h"

std::ostream& operator<<(std::ostream& os, const Suit& suit) {
    switch (suit) {
        case Suit::CLUB :
            os << 'c' ;
            break ;
        case Suit::DIAMOND :
            os << 'd' ;
            break ;
        case Suit::HEART :
            os << 'h' ;
            break ;
        case Suit::SPADE :
            os << 's' ;
            break ;
        case Suit::NT :
            os << 'b' ;
            break ;

    }
    return os ;
}

std::ostream& operator<<(std::ostream& os, const Rank& rank) {
    switch (rank) {
        case Rank::DEUCE :
            os << '2' ;
            break ;
        case Rank::THREE :
            os << '3' ;
            break ;
        case Rank::FOUR :
            os << '4' ;
            break ;
        case Rank::FIVE :
            os << '5' ;
            break ;
        case Rank::SIX :
            os << '6' ;
            break ;
        case Rank::SEVEN :
            os << '7' ;
            break ;
        case Rank::EIGHT :
            os << '8' ;
            break ;
        case Rank::NINE :
            os << '9' ;
            break ;
        case Rank::TEN :
            os << 'T' ;
            break ;
        case Rank::JACK :
            os << 'J' ;
            break ;
        case Rank::QUEEN :
            os << 'Q' ;
            break ;
        case Rank::KING :
            os << 'K' ;
            break ;
        case Rank::ACE :
            os << 'A' ;
            break ;
    }
    return os ;
}

bool operator==(const Card& lhs, const Card& rhs) {
    return lhs.getRank() == rhs.getRank() && lhs.getSuit() == rhs.getSuit() ;
}

Card::Card(const Rank _rank, const Suit _suit, const int _strength) : rank(_rank), suit(_suit), strength(_strength) {}

Card::Card(const Rank _rank, const Suit _suit) : rank(_rank), suit(_suit) {}

Card::Card(char _rank, char _suit) {
    switch (_rank) {
        case '2' :
            rank = Rank::DEUCE ;
            break ;
        case '3' :
            rank = Rank::THREE ;
            break ;
        case '4' :
            rank = Rank::FOUR ;
            break ;
        case '5' :
            rank = Rank::FIVE ;
            break ;
        case '6' :
            rank = Rank::SIX ;
            break ;
        case '7' :
            rank = Rank::SEVEN ;
            break ;
        case '8' :
            rank = Rank::EIGHT ;
            break ;
        case '9' :
            rank = Rank::NINE ;
            break ;
        case 'T' :
            rank = Rank::TEN ;
            break ;
        case 'J' :
            rank = Rank::JACK ;
            break ;
        case 'Q' :
            rank = Rank::QUEEN ;
            break ;
        case 'K' :
            rank = Rank::KING ;
            break ;
        case 'A' :
            rank = Rank::ACE ;
            break ;
        default:
            throw std::runtime_error("Something goes wrong with rank conversion") ;
    }
    switch (_suit) {
        case 'c' :
            suit = Suit::CLUB ;
            break ;
        case 'd' :
            suit = Suit::DIAMOND ;
            break ;
        case 'h' :
            suit = Suit::HEART ;
            break ;
        case 's' :
            suit = Suit::SPADE ;
            break ;
        default:
            throw std::runtime_error("Something goes wrong with suit conversion") ;
    }
}

Rank Card::getRank() const {
    return  rank ;
}

Suit Card::getSuit() const {
    return suit ;
}

