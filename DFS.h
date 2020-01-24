//
// Created by Dor Refaeli on 21/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_DEPTHFIRSTSEARCH_H
#define ALGORITHMICPROGRAMMING2_DEPTHFIRSTSEARCH_H

#include <iostream>
#include <stack>
#include <set>

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"

/** DFS algorithm.
 *
 * @tparam P
 */
template <class P>
class DFS : public Searcher<P> {
public:
    list<P>* search(Searchable<P> *problem) override;
    Searcher<P> *clone() const override;
};
template class DFS<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_DEPTHFIRSTSEARCH_H
