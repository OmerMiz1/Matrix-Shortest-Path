//
// Created by omer on 19/01/2020.
//

#include "SearchSolver.h"

template<typename P>
SearchSolver<P>::SearchSolver(Searcher<P> *searcher): my_searcher(searcher) {}

/** Solves a SearchableMatrix problem.
 *
 * @tparam P
 * @param sMatrix
 * @return the path from start to end in list. (of State<Point>)
 */
template<typename P>
list<P>* SearchSolver<P>::solve(Searchable<P> *sMatrix) {
    return my_searcher->search(sMatrix);
}

template<typename P>
SearchSolver<P> *SearchSolver<P>::clone() const {
    return new SearchSolver<P>(my_searcher->clone());
}




