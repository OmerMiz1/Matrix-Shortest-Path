//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MATRIXSHORTESTPATHS_H_
#define ALGORITHMICPROGRAMMING2__MATRIXSHORTESTPATHS_H_

#include "Solver.h"
#include "State.h"
#include "Point.h"
#include "Searchable.h"
#include "BestFirstSearch.h"

#include <list>
#include <climits>

/*Object Adapter*/
template <typename P, typename S>
class MatrixShortestPaths : public Solver<Searchable<P>, list<Searchable<P>>> {
 public:
    S solve(Searchable<P> sMatrix) override;
    Solver<Searchable<P>, S> clone() const override;
};

#endif //ALGORITHMICPROGRAMMING2__MATRIXSHORTESTPATHS_H_
