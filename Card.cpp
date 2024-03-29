//
// Created by kamil on 3/28/24.
//

#include "Card.h"

Card::Card(const Rank _rank, const Suit _suit) : rank(_rank), suit(_suit) {
    switch (_rank) {
        case Rank::DEUCE:
            rank_symbol = '2' ;
            break ;
        case Rank::THREE:
            rank_symbol = '3' ;
            break ;
        case Rank::FOUR:
            rank_symbol = '4' ;
            break ;
        case Rank::FIVE:
            rank_symbol = '5' ;
            break ;
        case Rank::SIX:
            rank_symbol = '6' ;
            break ;
        case Rank::SEVEN:
            rank_symbol = '7' ;
            break ;
        case Rank::EIGHT:
            rank_symbol = '8' ;
            break ;
        case Rank::NINE:
            rank_symbol = '9' ;
            break ;
        case Rank::TEN:
            rank_symbol = 'T' ;
            break ;
        case Rank::JACK:
            rank_symbol = 'J' ;
            break ;
        case Rank::QUEEN:
            rank_symbol = 'Q' ;
            break ;
        case Rank::KING:
            rank_symbol = 'K' ;
            break ;
        case Rank::ACE:
            rank_symbol = 'A' ;
            break ;
        
    }
    switch (_suit) {
        case Suit::CLUB:
            suit_symbol = 'c' ;
            break ;
        case Suit::DIAMOND:
            suit_symbol = 'd' ;
            break ;
        case Suit::HEART:
            suit_symbol = 'h' ;
            break ;
        case Suit::SPADE:
            suit_symbol = 's' ;
            break ;

    }
}

Rank Card::getRank() const {
    return  rank ;
}

Suit Card::getSuit() const {
    return suit ;
}

char Card::getRank_symbol() const {
    return rank_symbol ;
}

char Card::getSuit_symbol() const {
    return suit_symbol ;
}