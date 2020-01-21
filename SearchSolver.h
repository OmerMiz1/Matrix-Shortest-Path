//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SEARCHSOLVER_H_
#define ALGORITHMICPROGRAMMING2__SEARCHSOLVER_H_

#include "Solver.h"
#include "State.h"
#include "Point.h"
#include "Searchable.h"
#include "BestFirstSearch.h"

#include <list>
#include <climits>

/*Object Adapter*/
template <typename P>
class SearchSolver : public Solver<Searchable<P>, list<P>> {

 public:
    list<P> solve(Searchable<P> sMatrix) override;
    SearchSolver<P> *clone() const override;
};

#endif //ALGORITHMICPROGRAMMING2__SEARCHSOLVER_H_
