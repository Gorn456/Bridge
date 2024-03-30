//
// Created by kamil on 3/30/24.
//
#include <vector>
#include <iostream>
#include "Card.h"
#ifndef BRIDGE_PLAYER_H
#define BRIDGE_PLAYER_H


class Player {
protected:
    std::vector<Card> CardsArray ;
public:
    void setCards(std::vector<Card>& dealedCards) ;

};

class Hero : public Player {
public:
    void displayCards() {
        for (const auto &card : CardsArray) {
            std::cout << card.getRank_symbol() << card.getSuit_symbol() << " " ;
        }
        std::cout << std::endl ;
    }

};


#endif //BRIDGE_PLAYER_H
