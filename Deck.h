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



};


#endif //BRIDGE_DECK_H
