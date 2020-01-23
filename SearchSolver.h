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
class SearchSolver : public Solver<Searchable<P>, list<P>*> {
 private:
    Searcher<P> *my_searcher;
 public:
    SearchSolver(Searcher<P> *searcher);
    list<P>* solve(Searchable<P> *sMatrix) override;
    SearchSolver<P> *clone() const override;
};

template class SearchSolver<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2__SEARCHSOLVER_H_
