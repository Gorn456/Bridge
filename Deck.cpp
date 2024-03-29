//
// Created by kamil on 3/29/24.
//

#include "Deck.h"


Deck::Deck() {
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; ++j) {
            CardsArray.push_back(*(new Card(static_cast<Rank>(j), static_cast<Suit>(i)))) ;
        }
    }
}

void Deck::display() {
    for (const Card& card : CardsArray) {
        std::cout << card.getRank_symbol() << card.getSuit_symbol() << std::endl ;
    }
}

void Deck::shuffle() {
    // Fisher–Yates shuffle
    for (size_t i = CardsArray.size() - 1; i > 0; i--) {
        size_t j = generator.randint(0, i) ;
        Card temp = CardsArray.at(i) ;
        CardsArray.at(i) = CardsArray.at(j) ;
        CardsArray.at(j) = temp ;
    }
}


