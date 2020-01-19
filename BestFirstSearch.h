//
// Created by doref on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

template <typename P, typename S>
class BestFirstSearch : public Searcher<P ,list<State<S>>> {
private:
    int evaluatedNodesCount = 0;
public:
    S solve(P problem);
};

typedef Searchable<Point> SearchableMatrix;


#endif //ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H
