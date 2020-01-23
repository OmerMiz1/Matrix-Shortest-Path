//
// Created by Dor Refaeli on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

template <class P>
class BestFS : public Searcher<P> {
private:
    int evaluatedNodesCount = 0;

public:
    list<P>* search(Searchable<P> *problem) override;
    Searcher<P> *clone() const override;
};

template class BestFS<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H