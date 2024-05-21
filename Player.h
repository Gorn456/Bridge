//
// Created by kamil on 3/30/24.
//
#ifndef BRIDGE_PLAYER_H
#define BRIDGE_PLAYER_H

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "Card.h"
#include "InputListener.h"



/*
 * 0 as the fist element in pair means fold
 * */
typedef std::pair<int, Suit> word ;

class Player {
protected:
    std::vector<Card> CardsArray ;
    int PC = 0 ;
    bool isDummy = false ;
    std::map<Suit, int> suitsLength = {
            {Suit::CLUB, 0},
            {Suit::DIAMOND, 0},
            {Suit::HEART, 0},
            {Suit::SPADE, 0}
    };

    std::vector<Card> cardsSafeToPlay = {
            Card(Rank::ACE, Suit::CLUB, 4),
            Card(Rank::ACE, Suit::DIAMOND, 4),
            Card(Rank::ACE, Suit::HEART, 4),
            Card(Rank::ACE, Suit::SPADE, 4),
    } ;
    Card lowestCardInSuit(Suit suit) ;
    Card highestCardInSuit(Suit suit) ;
    /**
     * Removes the card from CardsArray.
     * @param card The card to be removed.
     */
    void removeCardFromHand(Card &card) ;
    void removeCardFromArray(Card &card, std::vector<Card> &array) ;
    word getLastWord(const std::vector<word>& previous) ;
    void calculateStrength() ;
    /*
    * Hand is balanced when all suits have length above 2
    * except one suit which can be doubleton
    * */
    bool balancedHand() ;
    std::pair<Suit, int> longestSuit() ;
    std::pair<Suit, int> shortestNotZeroSuit() ;
    void sortCards() ;
    /*
     * Returns the strongest card in current trick
     * @param trick The cards that have been played in the trick.
     * @param trump The trump suit.
     * */
    Card strongestCardInTrick(std::vector<Card> &trick, Suit trump) ;
public:

    void setCards(std::vector<Card>& dealedCards) ;

    std::vector<Card> getCards() ;

    void makeDummy() ;

    void displayCards() ;

    void reset() ;

    /**
     * Makes a bid based on the previous bids.
     *
     * @param previous A vector of previous bids.
     * @return The bid made by the AI player.
     */
    virtual word makeBid(std::vector<word>& previous) = 0 ;
    /**
     * Plays a card based on the trick and the cards that have been played.
     *
     * @param trick The cards that have been played in the trick.
     * @param trump The trump suit.
     * @return The card played by the AI player.
     */
    virtual Card playCard(std::vector<Card>& trick, Suit trump) = 0 ;
    /*
     * Updates the cards that are safe to play based on the cards that have been played and
     * dummy's cards.
     */
    void updateCardsSafeToPlay(const std::vector<Card>& playedCards, const std::vector<Card>& dummyCards) ;

};

class Hero : virtual public Player {
public:

    word makeBid(std::vector<word>& previous) override ;

    Card playCard(std::vector<Card>& trick, Suit trump) override ;

};

class Enemy : virtual public Player {
public:
    word makeBid(std::vector<word>& previous) override ;

    Card playCard(std::vector<Card>& trick, Suit trump) override ;
};

class Partner : public Enemy, public Hero {
public:
    word makeBid(std::vector<word>& previous) override ;

    Card playCard(std::vector<Card>& trick, Suit trump) override ;

};



#endif //BRIDGE_PLAYER_H
