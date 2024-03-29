//
// Created by kamil on 3/29/24.
//

#include "Random.h"

Random::Random() : generator(rd()) {}

int Random::randint(const int lower,const int upper) {
    std::uniform_int_distribution<int> range(lower, upper) ;
    return range(generator) ;
}
