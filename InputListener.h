//
// Created by kamil on 4/14/24.
//

#ifndef BRIDGE_INPUTLISTENER_H
#define BRIDGE_INPUTLISTENER_H

#include <string>
#include "Player.h"

class Hero ;
typedef std::pair<int, Suit> word ;


class InputListener {
private:
    static void help() ;
    static bool correctInput(std::string input, int state) ;
public:
    /* state can be 0 or 1
     * 0 - auction
     * 1 - hand play
     * */
    static std::string read(int state, Hero& self) ;

    static word convertInputToBid(std::string input) ;

    static Card convertInputToCard(std::string input) ;

    static void displayBid(const word& bid, int currentPlayer) ;

    static void displayCard(const Card& card, int currentPlayer) ;

    static void displayWinner(int winner) ;

};


#endif //BRIDGE_INPUTLISTENER_H
