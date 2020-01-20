//
// Created by doref on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"/*list<State<P>>*/

template <class P, class S>
class BestFirstSearch : public Searcher<Searchable<P> ,S> {
private:
    int evaluatedNodesCount = 0;

public:
    S search(P problem) override;
};

#endif //ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H
