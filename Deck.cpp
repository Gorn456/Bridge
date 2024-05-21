//
// Created by kamil on 3/29/24.
//

#include "Deck.h"


Deck::Deck() {
    int card_strength ;
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; ++j) {
            card_strength = (j < 9) ? 0 : ++card_strength ;
            CardsArray.push_back(Card(static_cast<Rank>(j), static_cast<Suit>(i), card_strength)) ;
        }
    }
}

void Deck::display() {
    for (const Card& card : CardsArray) {
        std::cout << card.getRank() << card.getSuit() << std::endl ;
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

std::vector<std::vector<Card>> Deck::dealCards() {
    std::vector<std::vector<Card>> temp(4) ;
    for (size_t i = 0; i < CardsArray.size(); i++) {
        temp.at(i % 4).push_back(CardsArray.at(i));
    }
    return temp ;
}



