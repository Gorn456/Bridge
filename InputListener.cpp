//
// Created by kamil on 4/14/24.
//

#include "InputListener.h"
#include <iostream>
#include <string>
#include <array>
#include "Game.h"

std::string InputListener::read(int state, Hero& self) {
    bool correct = false ;
    std::string buf ;
    if (state == 0) std::cout << "Your turn in auction" << std::endl ;
    else std::cout << "Choose card to play" << std::endl ;
    do {
        std::getline(std::cin, buf) ;
        if (buf == "help" || buf == "-h") help() ;
        else if (buf == "cards" || buf == "-c") self.displayCards() ;

        else if (correctInput(buf, state)) {
            correct = true ;
        }

        else std::cout << "Incorrect input, try again or type help or -h for help" << std::endl ;
    } while (!correct) ;
    return buf ;
}

void InputListener::help() {
    std::cout << "Placeholder" << std::endl ;
}

bool InputListener::correctInput(std::string input, int state) {
    if (state == 0 && (input == "pass" || input == "p" || input == "P")) return true ;
    if (input.size() != 2) return false ;
    if (state == 0) { // auction
        std::array<char, 5> miano = {'c', 'd', 'h', 's', 'b'} ;
        auto level = input.at(0) - '0' ; // conversion to int
        auto suit = _tolower(input.at(1)) ;
        if (level < 1 || level > 7) return false ;

        auto it = std::find(miano.begin(), miano.end(), suit) ;
        if (it == miano.end()) return false ;
        return true ;
    }
    else { // hand play
        // try create card based on input, where first is rank and second is suit if it's possible return true else return false
        try {
            Card card = Card(input.at(0), input.at(1)) ;
            return true ;
        } catch (std::runtime_error& e) {
            return false ;
        }
    }
}

word InputListener::convertInputToBid(std::string input) {
    if (input == "pass" || input == "p" || input == "P") return std::make_pair(0, Suit::CLUB) ;
    Suit suit ;
    int level = input.at(0) - '0' ;
    char char_suit = input.at(1) ;
    switch (char_suit) {
        case 'c':
            suit = Suit::CLUB ;
            break ;
        case 'd':
            suit = Suit::DIAMOND ;
            break ;
        case 'h':
            suit = Suit::HEART ;
            break ;
        case 's':
            suit = Suit::SPADE ;
            break ;
        case 'b':
            suit = Suit::NT ;
            break ;

        default:
            throw std::runtime_error("Something goes wrong with input conversion") ;
    }
    return std::make_pair(level, suit) ;
}

Card InputListener::convertInputToCard(std::string input) {
    return Card(input.at(0), input.at(1)) ;
}

void InputListener::displayBid(const word& bid, int currentPlayer) {
    char playerPosition ;
    switch (currentPlayer) {
        case 0:
            playerPosition = 'S' ;
            break ;
        case 1:
            playerPosition = 'W' ;
            break ;
        case 2:
            playerPosition = 'N' ;
            break ;
        case 3:
            playerPosition = 'E' ;
            break ;
        default:
            throw std::runtime_error("Something goes wrong with player position") ;
    }
    if (bid.first == 0) std::cout << "Player " << playerPosition << " passes" << std::endl ;
    else 
    std::cout << "Player " << playerPosition << " bids " << bid.first << bid.second << std::endl ;
}

void InputListener::displayCard(const Card &card, int currentPlayer) {
    char playerPosition ;
    switch (currentPlayer) {
        case 0:
            playerPosition = 'S' ;
            break ;
        case 1:
            playerPosition = 'W' ;
            break ;
        case 2:
            playerPosition = 'N' ;
            break ;
        case 3:
            playerPosition = 'E' ;
            break ;
        default:
            throw std::runtime_error("Something goes wrong with player position") ;
    }
    std::cout << "Player " << playerPosition << " plays "
    << card.getRank() << card.getSuit() << std::endl ;
}

void InputListener::displayWinner(int winner) {
    char playerPosition ;
    switch (winner) {
        case 0:
            playerPosition = 'S' ;
            break ;
        case 1:
            playerPosition = 'W' ;
            break ;
        case 2:
            playerPosition = 'N' ;
            break ;
        case 3:
            playerPosition = 'E' ;
            break ;
        default:
            throw std::runtime_error("Something goes wrong with player position") ;
    }
    std::cout << "Player " << playerPosition << " wins the trick" << std::endl ;
}


