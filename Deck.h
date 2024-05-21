//
// Created by kamil on 3/29/24.
//

#include <vector>
#include <iostream>
#include <random>
#include "Card.h"
#include "Random.h"

#ifndef BRIDGE_DECK_H
#define BRIDGE_DECK_H


class Deck {
private:
    std::vector<Card> CardsArray ;
    Random generator ;

public:
    Deck() ;

    void display() ;

    void shuffle() ;

    std ::vector<std::vector<Card>> dealCards() ;



};


#endif //BRIDGE_DECK_H
