#include <iostream>
#include "Deck.h"
#include "Random.h"
#include "Player.h"

class Game {
public:
    std::vector<Player *> pPlayers; // array of pointers to players (types Player and Hero)
    int heroPoints = 0 ;
    int heroAdditionalPoints = 0 ;
    Hero S = Hero() ; // Self
    Player N = Player() ; // Partner

    int enemyPoints = 0 ;
    int enemyAdditionalPoints = 0 ;
    Player W = Player() ; // Enemy on a left
    Player E = Player() ; // Enemy on a right

    Game() {
        pPlayers.push_back(&S) ;
        pPlayers.push_back(&W) ;
        pPlayers.push_back(&N) ;
        pPlayers.push_back(&E) ;
    }
};


int main() {
    int handCounter = 0 ;
    Game game ;
    Deck deck ;

    deck.shuffle() ;
    auto dealedCards = deck.dealCards() ;
    int dealer = handCounter % 4 ;
    for (auto & set : dealedCards) {
        game.pPlayers.at(dealer)->setCards(set) ;
        dealer = (dealer < 3) ? ++dealer : 0 ;
    }
    game.S.displayCards() ;

    return 0;
}
