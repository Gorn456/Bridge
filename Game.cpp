//
// Created by kamil on 4/14/24.
//

#include "Game.h"
#include "InputListener.h"


std::pair<int, word> Game::auction(int dealer)  {
    // BidList biddingHistory ;
    BidList biddingHistory ;
    do
    {
        auto bid = pPlayers.at(dealer)->makeBid(biddingHistory) ;
        biddingHistory.push_back(bid) ;
        InputListener::displayBid(bid, dealer) ;
        dealer = (dealer < 3) ? ++dealer : 0 ;
    } while (!endOfAuction(biddingHistory)) ;
    
    return std::make_pair(declarer(dealer, biddingHistory), biddingHistory.at(biddingHistory.length() - 4)) ;
}

std::pair<int, int> Game::play(int declarer, word contract) {
    std::vector<Card> playedCards ; // trick = lewa
    int heroTricksCounter = 0 ;
    int enemyTricksCounter = 0 ;
    int currentTricker = (declarer + 1) % 4 ;
    int dummy = (declarer + 2) % 4 ;
    pPlayers.at(dummy)->makeDummy() ;
    for (int i = 0; i < 13; i++) {
        currentTricker = trick(currentTricker, dummy, playedCards, contract.second) ;
        if (currentTricker == 0 || currentTricker == 2) heroTricksCounter++ ;
        else enemyTricksCounter++ ;
        InputListener::displayWinner(currentTricker) ;
    }
    return std::make_pair(heroTricksCounter, enemyTricksCounter) ;
}

int Game::trick(int tricker, int dummy, std::vector<Card> &playedCards, Suit trump) {
    std::vector<Card> trick ;
    int firstToAct = tricker ;
    auto dummyCards = pPlayers.at(dummy)->getCards() ;
    for (int i = 0; i < 4; i++) {
        Card playedCard = pPlayers.at(tricker)->playCard(trick, trump) ;
        trick.push_back(playedCard) ;
        playedCards.push_back(playedCard) ;
        InputListener::displayCard(playedCard, tricker) ;
        tricker = (tricker < 3) ? ++tricker : 0 ;
        pPlayers.at(tricker)->updateCardsSafeToPlay(playedCards, dummyCards) ;
    }
    return trickWinner(trick, firstToAct, trump) ;
}

int Game::trickWinner(const std::vector<Card> &trick, int tricker, Suit trump) {
    auto strongest = trick.at(0) ;
    int winner = tricker ;
    for (int i = 1; i < trick.size(); i++) {
        // higher card in the same suit
        if (trick.at(i).getSuit() == strongest.getSuit() && trick.at(i).getRank() > strongest.getRank()) {
            winner = (tricker + i) % 4 ;
            strongest = trick.at(i) ;
        }
            // trump card
        else if (trick.at(i).getSuit() == trump && strongest.getSuit() != trump) {
            winner = (tricker + i) % 4 ;
            strongest = trick.at(i) ;
        }
            // higher trump card
//        else if (trick.at(i).getSuit() == trump && strongest.getSuit() == trump &&
//                 trick.at(i).getRank() > strongest.getRank()) {
//            winner = (tricker + i) % 4 ;
//            strongest = trick.at(i) ;
//        }
    }
    return winner ;
}


bool Game::endOfAuction(const BidList& biddingHistory) {
    if (biddingHistory.length() < 4) return false ;
    for (int i = biddingHistory.length() - 1; i > biddingHistory.length() - 4; i--) {
        if (biddingHistory.at(i).first != 0) return false ;
    }
    return true ;
}

int Game::declarer(int lastBidder, const BidList &biddingHistory) {
    BidList our_words ;
    for (int i = biddingHistory.length() - 4; i >= 0; i -= 2) {
        our_words.push_back(biddingHistory.at(i)) ;
    }
    auto declaredSuit = our_words.at(0).second ;

    int currentBidder = lastBidder ;
    for (int i = 1; i < our_words.length(); i++) {
        currentBidder += 2;
        if (currentBidder > 3) currentBidder -= 4;
        if (our_words.at(i).first != 0 && our_words.at(i).second == declaredSuit) lastBidder = currentBidder;
    }
    return lastBidder ;
}

void Game::dealCards(Deck& deck, int dealer) {
    deck.shuffle() ;
    auto dealedCards = deck.dealCards() ;
    for (auto & set : dealedCards) {
        pPlayers.at(dealer)->setCards(set) ;
        dealer = (dealer < 3) ? ++dealer : 0 ;
    }
    S.displayCards() ;
}

bool Game::score(int ourTricks, int theirTricks, int declarer, word contract) {
    std::cout << "Our tricks: " << ourTricks << "\nTheir tricks: " << theirTricks << std::endl ;
    bool heroPlayed = (declarer == 0 || declarer == 2);
    if (heroPlayed) {
        givePoints(heroPoints, heroAdditionalPoints, heroGames, enemyAdditionalPoints, ourTricks, contract);
    } else {
        givePoints(enemyPoints, enemyAdditionalPoints, enemyGames, heroAdditionalPoints, theirTricks, contract);
    }
    if (heroPoints >= 100) {
        heroGames++ ;
        heroAdditionalPoints += heroPoints ;
        heroPoints = 0 ;
    }
    if (enemyPoints >= 100) {
        enemyGames++;
        enemyAdditionalPoints += enemyPoints ;
        enemyPoints = 0 ;
    }
    if (heroGames == 2) {
        if (enemyGames == 0) { // punkty za robra
            heroAdditionalPoints += 700 ;
        } else {
            heroAdditionalPoints += 500 ;
        }
        return true ;
    }
    if (enemyGames == 2) {
        if (heroGames == 0) {
            enemyAdditionalPoints += 700 ;
        } else {
            enemyAdditionalPoints += 500 ;
        }
        return true ;
    }
    return false ;

}
void Game::givePoints(int &playerPoints, int &playerAdditionalPoints, int& playerGames, int &defenderAdditionalPoints, int tricks,
                      word contract) {
    int level = contract.first ;
    Suit suit = contract.second ;
    if (tricks >= level + 6) { // win the contract
        if (level == 6) { // szlemik
            if (playerGames == 0) playerAdditionalPoints += 500 ; // przed partią
            else playerAdditionalPoints += 750 ; // po partii
        }
        if (level == 7) { // szlem
            if (playerGames == 0) playerAdditionalPoints += 1000 ;
            else playerAdditionalPoints += 1500 ;
        }
        int extraTricks = tricks - level - 6 ;
        if (suit == Suit::NT) {
            playerPoints += 40 + 30 * (level - 1) ;
            playerAdditionalPoints+= extraTricks * 30 ;
        } else if (suit == Suit::SPADE || suit == Suit::HEART) {
            playerPoints += 30 * level;
            playerAdditionalPoints += extraTricks * 30;
        } else {
            playerPoints += 20 * level;
            playerAdditionalPoints += extraTricks * 20;
        }
    } else { // lose the contract
        int penaltyTricks = level + 6 - tricks ;
        if (playerGames == 0) { // przed partią
            defenderAdditionalPoints += penaltyTricks * 50 ;
        }
        else { // po partii
            defenderAdditionalPoints += penaltyTricks * 100 ;
        }
    }
}

void Game::reset() {
    for (const auto player : pPlayers) {
        player->reset() ;
    }
}

void Game::displayScore() {
    std::cout << "Our games: " << heroGames << "\n Our points: " << heroPoints << "\n Our additional points: "
    << heroAdditionalPoints << std::endl ;

    std::cout << "Their games: " << enemyGames << "\n Their points: " << enemyPoints << "\n Their additional points: "
    << enemyAdditionalPoints << std::endl ;
}




