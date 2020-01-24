//
// Created by Dor Refaeli on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_SEARCHABLE_H
#define ALGORITHMICPROGRAMMING2_SEARCHABLE_H

#include "State.h"
#include "Stringable.h"

using namespace std;
/**
 * Searchable must be Stringable!
 * @tparam State<P>
 */
 /*Interface*/
template <typename P>
class Searchable : Stringable<P>, Stringable<Searchable<P>> {
public:
    virtual P getInitialState() const = 0;
    virtual bool isGoalState(P) const = 0;
    virtual list<P> getAllPossibleStates(P) = 0;
    virtual P getGoalState() const =0;
    virtual string str() const=0;
};

template class Searchable<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_SEARCHABLE_H
