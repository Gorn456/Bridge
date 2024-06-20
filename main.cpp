// http://www.pilsener.fr.pl/brydz/brydz_abc.php?a=4



#include "Game.h"
#include "Deck.h"
#include "Random.h"



int main() {
    int handCounter = 0 ;
    bool end = false ;
    Game game ;
    Deck deck ;

    do {
        int dealer = handCounter % 4 ;

        game.dealCards(deck, dealer) ;

        auto [declarer, contract] = game.auction(dealer) ;

        if (contract.first) { // if contract is not passed
            auto [ourTricks, theirTricks] = game.play(declarer, contract) ;

            end = game.score(ourTricks, theirTricks, declarer, contract) ;
        }

        game.displayScore() ;

        handCounter++ ;

        game.reset() ;

    } while (!end) ;



    return 0;
}
