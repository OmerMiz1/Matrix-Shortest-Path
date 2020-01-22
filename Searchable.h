//
// Created by doref on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_SEARCHABLE_H
#define ALGORITHMICPROGRAMMING2_SEARCHABLE_H

#include "State.h"

using namespace std;

template <typename P>
class Searchable {
public:
    virtual P getInitialState() = 0;
    virtual bool isGoalState(P) = 0;
    virtual list<P> getAllPossibleStates(P) = 0;
    virtual string toString() = 0;
};

template class Searchable<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_SEARCHABLE_H
