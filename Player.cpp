//
// Created by kamil on 3/30/24.
//

#include "Player.h"


void Player::setCards(std::vector<Card>& dealedCards) {
    CardsArray = dealedCards ;
    calculateStrength() ;
    sortCards() ;
}

std::vector<Card> Player::getCards() {
    return CardsArray ;
}

void Player::makeDummy() {
    isDummy = true ;
}

void Player::removeCardFromHand(Card &card) {
    // remove card from CardsArray
    CardsArray.erase(std::remove(CardsArray.begin(), CardsArray.end(), card), CardsArray.end()) ;
    suitsLength[card.getSuit()]-- ;
    PC -= card.strength ;
}


void Player::removeCardFromArray(Card &card, std::vector<Card> &array) {
    array.erase(std::remove(array.begin(), array.end(), card), array.end()) ;
}

void Player::calculateStrength() {
    for (const auto &card : CardsArray) {
        PC += card.strength ;
        suitsLength[card.getSuit()]++ ;
    }
}

bool Player::balancedHand() {
    int shortHandCounter = 0 ;
    for (const auto &pair : suitsLength) {
        if (pair.second < 2) return false ;
        if (pair.second == 2) shortHandCounter++ ;
    }
    return shortHandCounter < 2 ;
}

std::pair<Suit, int> Player::longestSuit() {
    auto result = *std::max_element(suitsLength.begin(), suitsLength.end(),
                                   [](const std::pair<Suit, int>& p1, const std::pair<Suit, int>& p2) {
        if (p1.second != p2.second) return p1.second < p2.second ;
        else return p1.first < p2.first ;
    }) ;
    return result ;
}

std::pair<Suit, int> Player::shortestNotZeroSuit() {
    auto candidate = std::make_pair(Suit::SPADE, 13) ;
    for (const auto &pair : suitsLength) {
        if (pair.second < candidate.second && pair.second > 0) candidate = pair ;
    }
    return candidate ;
}

void Player::sortCards() {
    std::sort(CardsArray.begin(), CardsArray.end(), [](const Card& c1, const Card& c2) {
        if (c1.getSuit() != c2.getSuit()) return c1.getSuit() > c2.getSuit() ;
        else return c1.getRank() > c2.getRank() ;
    }) ;
}

word Enemy::makeBid(std::vector<word>& previous) {
    word last_word = getLastWord(previous) ;
    std::vector<word> our_words ;
    word last_partner_word = std::make_pair(0, Suit::CLUB) ;

    for (int i = previous.size() - 2; i >= 0; i -= 2) {
        our_words.push_back(previous.at(i)) ;
    }
    if (!our_words.empty()) last_partner_word = our_words.at(0) ;
    // first in our  team to act
    if (last_partner_word == std::make_pair(0, Suit::CLUB)) {
        // opening
        // 3 kolor
        if (PC > 6 && PC < 12 && longestSuit().second > 6) {
            auto bid = std::make_pair(3, longestSuit().first) ;
            if (bid > last_word) return bid ;
        }

        // pas
        if (PC < 12) return std::make_pair(0, Suit::CLUB) ;

        // 2 bez atu
        if (balancedHand() && PC > 18) {
            auto bid = std::make_pair(2, Suit::NT) ;
            if (bid > last_word) return bid ;
        }
        // 2 kolor
        if (longestSuit().second > 5 && PC > 17) {
            auto bid = std::make_pair(2, longestSuit().first) ;
            if (bid > last_word) return bid ;
        }
        // 1 bez atu
        if (balancedHand() && PC > 15 && PC < 19) {
            auto bid = std::make_pair(1, Suit::NT) ;
            if (bid > last_word) return bid ;
        }
        // 1 kolor
        if (PC > 11 && PC < 18) {
            auto longer = longestSuit() ;
            if ((longer.first == Suit::HEART || longer.first == Suit::SPADE) && longer.second > 4) {
                auto bid = std::make_pair(1, longer.first) ;
                if (bid > last_word) return bid ;
            }
            else if ((longer.first == Suit::CLUB || longer.first == Suit::DIAMOND) && longer.second > 3) {
                auto bid = std::make_pair(1, longer.first) ;
                if (bid > last_word) return bid ;
            }
        }
        // pas
        return std::make_pair(0, Suit::CLUB) ;


    }
    else {
        // decision (response)
        last_partner_word = our_words.at(0) ;
        auto partner_suit = last_partner_word.second ;
        auto partner_level = last_partner_word.first ;
        auto my_longer_length = longestSuit().second ;
        auto my_longer_suit = longestSuit().first ;
        // poparcie +2
        if (PC > (10 + partner_level) && suitsLength[partner_suit] > 4) {
            auto bid = std::make_pair(partner_level + 2, partner_suit) ;
            if (bid > last_word) return bid ;
        }
        // poparcie +1
        if (PC > (6 + partner_level) && suitsLength[partner_suit] > 2) {
            auto bid = std::make_pair(partner_level + 1, partner_suit) ;
            if (bid > last_word) return bid ;
        }
        // nowy kolor +1
        if (PC > (10 + last_word.first) && my_longer_length > 5) {
            auto bid = std::make_pair(last_word.first + 1, my_longer_suit) ;
            if (bid > last_word) return bid ;
        }
        // nowy kolor
        if (PC > (5 + last_word.first) && my_longer_length > 4 && my_longer_suit > last_word.second) {
            auto bid = std::make_pair(last_word.first, my_longer_suit) ;
            if (bid > last_word) return bid ;
        }
        // 2 bez atu
        if (PC > 10 && balancedHand()) {
            auto bid = std::make_pair(2, Suit::NT) ;
            if (bid > last_word) return bid ;
        }
        // 1 bez atu
        if (PC > 6 && PC < 10 && balancedHand()) {
            auto bid = std::make_pair(1, Suit::NT) ;
            if (bid > last_word) return bid ;
        }
        // pas
        return std::make_pair(0, Suit::CLUB) ;
    }


   return std::make_pair(0, Suit::CLUB) ;
}

word Player::getLastWord(const std::vector<word>& previous) {
        word last_word = std::make_pair(0, Suit::CLUB) ;
        for (int i = previous.size() - 1; i >= 0; i--) {
            if (previous.at(i).first != 0) {
                last_word = previous.at(i) ;
                break ;
            }
        }
        return last_word ;
    }

Card Player::strongestCardInTrick(std::vector<Card> &trick, Suit trump) {
    if (trick.size() == 1) return trick.at(0) ;
    else {
        auto strongest = trick.at(0);
        for (int i = 1; i < trick.size(); i++) {
            // higher card in the same suit
            if (trick.at(i).getSuit() == strongest.getSuit() && trick.at(i).getRank() > strongest.getRank()) {
                strongest = trick.at(i);
            }
                // trump card
            else if (trick.at(i).getSuit() == trump && strongest.getSuit() != trump) {
                strongest = trick.at(i);
            }
                // higher trump card
            else if (trick.at(i).getSuit() == trump && strongest.getSuit() == trump &&
                     trick.at(i).getRank() > strongest.getRank()) {
                strongest = trick.at(i);
            }
        }
        return strongest ;
    }

}

Card Player::lowestCardInSuit(Suit suit) {
    for (int i = CardsArray.size() - 1; i >= 0; i--) {
        if (CardsArray.at(i).getSuit() == suit) return CardsArray.at(i);
    }
    throw std::runtime_error("Something goes wrong with lowestCardInSuit") ;
}

Card Player::highestCardInSuit(Suit suit) {
    for (const auto &card: CardsArray) {
        if (card.getSuit() == suit) return card ;
    }
    throw std::runtime_error("Something goes wrong with lowestCardInSuit") ;
}

Card Enemy::playCard(std::vector<Card> &trick, Suit trump) {
    if (isDummy) {
        std::cout << "Dummy's cards: ";
        displayCards();
    }
    if (trick.empty()) { // wist
        std::vector<Card> playable;
        for (const auto &candidateCard: CardsArray) {
            for (const auto &safeCard: cardsSafeToPlay) {
                if (candidateCard == safeCard) {
                    playable.push_back(candidateCard);
                    break;
                }
            }
        }
        // play playable card from the longest suit
        if (!playable.empty()) {
            Card candidate = playable.at(0);
            for (const auto &card: playable) {
                if (suitsLength[card.getSuit()] > suitsLength[candidate.getSuit()]) candidate = card;
                else if (suitsLength[card.getSuit()] == suitsLength[candidate.getSuit()] &&
                         card.getRank() < candidate.getRank())
                    candidate = card;
            }
            // remove candidate from CardsArray
            removeCardFromHand(candidate);
            return candidate;
        }
        else {
            // play the lowest card from the shortest suit (CardsArray is sorted)
            auto shortest = lowestCardInSuit(shortestNotZeroSuit().first);
            removeCardFromHand(shortest);
            return shortest;
        }
    }
    else {
        auto trickSuit = trick.at(0).getSuit();
        auto strongestCard = strongestCardInTrick(trick, trump);
        // player have cards in trick suit but strongest card is trump
        if (trickSuit != trump && suitsLength[trickSuit] > 0 && strongestCard.getSuit() == trump) {
            auto lowestCard = lowestCardInSuit(trickSuit);
            removeCardFromHand(lowestCard);
            return lowestCard;
        }
            /* player have cards in trick suit and strongest card is in the same suit
             * (for now player always play the lowest card which beat the strongest card
             * if not possible, play the lowest card in the trick suit)
             */
        else if (suitsLength[trickSuit] > 0 && strongestCard.getSuit() == trickSuit) {
            Card candidate = highestCardInSuit(trickSuit);
            if (candidate.getRank() < strongestCard.getRank()) {
                auto lowestCard = lowestCardInSuit(trickSuit);
                removeCardFromHand(lowestCard);
                return lowestCard;
            }
            for (const auto &card: CardsArray) {
                if (card.getSuit() == trickSuit && card.getRank() < candidate.getRank() &&
                    card.getRank() > strongestCard.getRank()) {
                    candidate = card ;
                }
            }
            removeCardFromHand(candidate) ;
            return candidate ;
        }
            /* player doesn't have cards in trick suit and strongest card is a trump
             * */
        else if (suitsLength[trickSuit] == 0 && strongestCard.getSuit() == trump) {
            if (suitsLength[trump] > 0 && highestCardInSuit(trump).getRank() > strongestCard.getRank()) {
                Card candidate = highestCardInSuit(trickSuit) ;
                for (const auto &card: CardsArray) {
                    if (card.getSuit() == trump && card.getRank() < candidate.getRank() &&
                        card.getRank() > strongestCard.getRank()) {
                        candidate = card ;
                    }
                }
                removeCardFromHand(candidate) ;
                return candidate ;
            }
            else { // player doesn't have any trump card (play lowest card from shortest suit)
                auto lowest = lowestCardInSuit(shortestNotZeroSuit().first) ;
                removeCardFromHand(lowest) ;
                return lowest ;
            }

        }
        /*
         * player doesn't have cards in trick suit and strongest card is in the same suit
         * */
        else if (suitsLength[trickSuit] == 0 && strongestCard.getSuit() == trickSuit) {
            if (suitsLength[trump] > 0) {
                auto lowestTrump = lowestCardInSuit(trump) ;
                removeCardFromHand(lowestTrump) ;
                return lowestTrump ;
            }
            else {
                auto lowest = lowestCardInSuit(shortestNotZeroSuit().first) ;
                removeCardFromHand(lowest) ;
                return lowest ;
            }
        }
        else return lowestCardInSuit(shortestNotZeroSuit().first) ;
    }
}

void Player::updateCardsSafeToPlay(const std::vector<Card> &playedCards, const std::vector<Card> &dummyCards) {
    /*For now cards are updated only based on playedCards history, without
    * analyzing dummyCards. */
   // check if in played Cards are safeCards if that's true add to safe card
   // card from the same suit but lower rank
   auto cardsToCheck = cardsSafeToPlay ;
   while (!cardsToCheck.empty()) {
        auto safeCard = cardsToCheck.at(0) ;
        for (int i = 0; i < playedCards.size(); i++) {
            auto card = playedCards.at(i) ;
            if (safeCard == card) {
                if (static_cast<int>(safeCard.getRank()) - 1 >= 0) {
                    auto newSafeCard = Card(static_cast<Rank>(static_cast<int>(safeCard.getRank()) - 1), safeCard.getSuit()) ;
                    cardsToCheck.push_back(newSafeCard) ;
                    removeCardFromArray(safeCard, cardsSafeToPlay) ;
                    cardsSafeToPlay.push_back(newSafeCard) ;
                }
                break ;
            }
        }
        removeCardFromArray(safeCard, cardsToCheck) ;
   }
}

void Player::displayCards() {
    for (const auto &card : CardsArray) {
        std::cout << card.getRank() << card.getSuit() << " " ;
    }
    std::cout << std::endl ;
}

void Player::reset() {
    isDummy = false ;
    PC = 0 ;
    CardsArray.clear() ;
    suitsLength = {
            {Suit::CLUB, 0},
            {Suit::DIAMOND, 0},
            {Suit::HEART, 0},
            {Suit::SPADE, 0}
    } ;
    cardsSafeToPlay = {
            {Rank::ACE, Suit::CLUB, 4},
            {Rank::ACE, Suit::DIAMOND, 4},
            {Rank::ACE, Suit::HEART, 4},
            {Rank::ACE, Suit::SPADE, 4},
    } ;
}

word Hero::makeBid(std::vector<word>& previous) {
    bool correct = false ;
    word bid ;
    word last_word = getLastWord(previous) ;
    do {
        bid = InputListener::convertInputToBid(InputListener::read(0, *this)) ;
        if (bid == std::make_pair(0, Suit::CLUB) || bid > last_word) correct = true ;
        else std::cout << "Bid is to small" << std::endl ;
    } while(!correct) ;
    return bid ;
}

Card Hero::playCard(std::vector<Card> &trick, Suit trump) {
    bool correct = false ;
    Card card ;
    do {
        card = InputListener::convertInputToCard(InputListener::read(1, *this)) ;
        if (std::find(CardsArray.begin(), CardsArray.end(), card) == CardsArray.end()) std::cout << "You don't have this card" << std::endl ;
        else {
            if (trick.empty()) correct = true ;
            else {
                auto trickSuit = trick.at(0).getSuit() ;
                if (card.getSuit() == trickSuit) correct = true ;
                else {
                    if (suitsLength[trickSuit] > 0) {
                        std::cout << "You have to play card from the " << trickSuit << std::endl ;
                    }
                    else correct = true ;
                }
            
            }
        }
    } while(!correct) ;
    removeCardFromHand(card) ;
    return card ;
}

word Partner::makeBid(std::vector<word>& previous) {
    return Enemy::makeBid(previous) ;
}

Card Partner::playCard(std::vector<Card> &trick, Suit trump) {
    if (isDummy) {
        std::cout << "Dummy's cards: " ;
        displayCards() ;
        std::cout << "Choose card for dummy: " ;
        return Hero::playCard(trick, trump) ;
    }
    else return Enemy::playCard(trick, trump) ;
}