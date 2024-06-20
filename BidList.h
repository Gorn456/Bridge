#include <iostream>
#include <memory>
#include "Card.h"
typedef std::pair<int, Suit> word ;

struct Node {
    word data ;                       
    std::unique_ptr<Node> next ;    

    Node(const word& data) ;
};


class BidList {
private:
    std::unique_ptr<Node> head ;      
    unsigned int size ;               

public:
    BidList() ;

    void push_back(const word& data) ;

    word at(int index) const ;

    unsigned int length() const ;

    bool empty() const ;
};

