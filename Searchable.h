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
    virtual State<P> getInitialState() = 0;
    virtual bool isGoalState(State<P>) = 0;
    virtual list<State<P>> getAllPossibleStates(State<P>) = 0;
};


#endif //ALGORITHMICPROGRAMMING2_SEARCHABLE_H
