//
// Created by doref on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

template <class P>
class BestFirstSearch : public Searcher<P ,list<Vertex>> {
private:
    int evaluatedNodesCount = 0;

public:
    list<Vertex> search(Searchable<P> problem) override;
};

#endif //ALGORITHMICPROGRAMMING2_BESTFIRSTSEARCH_H
