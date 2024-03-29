//
// Created by kamil on 3/29/24.
//

#include <random>

#ifndef BRIDGE_RANDOM_H
#define BRIDGE_RANDOM_H


class Random {
private:
    std::random_device rd ;
    std::mt19937 generator ;

public:
    Random() ;

    int randint(int lower, int upper) ;

};


#endif //BRIDGE_RANDOM_H
