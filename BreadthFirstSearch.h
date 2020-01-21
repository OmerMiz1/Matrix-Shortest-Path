//
// Created by Dor Refaeli on 20/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_BREADTHFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_BREADTHFIRSTSEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

template <class P, class S>
class BreadthFirstSearch : public Searcher<P, S> {
public:
    S search(Searchable<P> problem) override;
};

#endif //ALGORITHMICPROGRAMMING2_BREADTHFIRSTSEARCH_H
