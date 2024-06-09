//
// Created by kamil on 4/14/24.
//

#ifndef BRIDGE_GAME_H
#define BRIDGE_GAME_H

#include <vector>
#include "Player.h"
#include "InputListener.h"
#include "Deck.h"


class Game {
private:
    int heroPoints = 0 ;
    int heroAdditionalPoints = 0 ;
    int heroGames = 0 ; // number of games won by hero or partner
    int enemyPoints = 0 ;
    int enemyAdditionalPoints = 0 ;
    int enemyGames = 0 ; // number of games won by enemies
    bool endOfAuction(const BidList& biddingHistory) ;
    int declarer(int lastBidder, const BidList& biddingHistory) ;
    int trick(int tricker, int dummy, std::vector<Card>& playedCards, Suit trump) ;
    int trickWinner(const std::vector<Card>& trick, int tricker, Suit trump) ;
public:
    std::array<Player *, 4> pPlayers; // array of pointers to players (types Player and Hero)
    Hero S = Hero() ; // Self
    Partner N = Partner() ; // Partner
    Enemy W = Enemy() ; // Enemy on a left
    Enemy E = Enemy() ; // Enemy on a right

    Game() {
        pPlayers.at(0) = &S ;
        pPlayers.at(1) = &W ;
        pPlayers.at(2) = &N ;
        pPlayers.at(3) = &E ;
    }

    void dealCards(Deck& deck, int dealer) ;

    std::pair<int, word> auction(int dealer) ;

    std::pair<int, int> play(int declarer, word contract) ;

    bool score(int ourTricks, int theirTricks, int declarer, word contract) ;

    void givePoints(int& playerPoints, int& playerAdditionalPoints,int& playerGames, int& defenderAdditionalPoints, int tricks, word contract) ;

    void displayScore() ;

    void reset() ;
};


#endif //BRIDGE_GAME_H
