//
// Created by omer on 19/01/2020.
//

#include "MatrixShortestPaths.h"

template<typename P, typename S>
S MatrixShortestPaths<P, S>::solve(Searchable<P> sMatrix) {
    auto my_searcher = new BestFirstSearch<P>();
    return my_searcher.search(sMatrix);
}

template<typename P, typename S>
Solver<Searchable<P>, S> MatrixShortestPaths<P, S>::clone() const {
    return Solver<Searchable<P>, S>();
}

