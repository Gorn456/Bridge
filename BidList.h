#include <iostream>
#include <memory>
#include "Card.h"
typedef std::pair<int, Suit> word ;

// Definicja węzła listy
struct Node {
    word data ;                        // Dane przechowywane w węźle
    std::unique_ptr<Node> next ;      // Wskaźnik do następnego węzła

    // Konstruktor węzła
    Node(const word& data) ;
};

// Definicja klasy listy jednokierunkowej
class BidList {
private:
    std::unique_ptr<Node> head ;      // Wskaźnik do pierwszego węzła listy
    unsigned int size ;               // Długosc listy

public:
    // Konstruktor
    BidList() ;

    // Metoda dodająca element na koniec listy
    void push_back(const word& data) ;

    // Metoda dos†ępu do wybranego elementu listy
    word at(int index) const ;

    // Metoda zwracająca rozmiar listy
    unsigned int length() const ;

    // Metoda mowiąca czy lista jest pusta
    bool empty() const ;
};

// int main() {
//     BidList list;

//     // Dodajemy kilka elementów na koniec listy
//     // list.push_back(10);
//     // list.push_back(20);
//     // list.push_back(30);

//     // Wypisujemy zawartość listy
//     // list.printList(); // Output: 10 -> 20 -> 30 -> nullptr

//     return 0;
// }
