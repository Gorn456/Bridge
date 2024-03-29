#include <iostream>
#include "Deck.h"
#include "Random.h"


int main() {

    Random silniczek = Random() ;
    std::cout << silniczek.randint(1, 5) << std::endl ;

    Deck deck = Deck() ;
    deck.shuffle() ;
    deck.display() ;
    deck.shuffle() ;
    std::cout << "--------------------" << std::endl ;
    deck.display() ;

    return 0;
}
