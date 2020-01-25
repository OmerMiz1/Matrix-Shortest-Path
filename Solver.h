//
// Created by Omer Mizrachi on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SOLVER_H_
#define ALGORITHMICPROGRAMMING2__SOLVER_H_
#include <string>
#include "Point.h"
#include "State.h"
#include "Searchable.h"
using namespace std;

/*Interface*/
template <typename P, typename S>
class Solver : virtual public Cloneable<Solver<P,S>>, virtual public Stringable<Solver<P,S>> {
 public:
    virtual S solve(P *problem)=0;
    virtual string str() const =0;
};

template class Solver<string,string>;
template class Solver<Searchable<State<Point>>,list<State<Point>>>;
#endif //ALGORITHMICPROGRAMMING2__SOLVER_H_
