//
// Created by omer on 19/01/2020.
//

#include "MatrixShortestPaths.h"

template<typename P, typename S>
S MatrixShortestPaths<P, S>::solve(Searchable<P> sMatrix) {
    auto my_searcher = new BestFirstSearch<Searchable<P>,P*>();
    return my_searcher->search(sMatrix);
}

template<typename P, typename S>
MatrixShortestPaths<P, S> *MatrixShortestPaths<P, S>::clone() const {
    return new MatrixShortestPaths<P,S>();
}



