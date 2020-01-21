//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SOLVER_H_
#define ALGORITHMICPROGRAMMING2__SOLVER_H_
#include <string>
#include "Point.h"
#include "State.h"
using namespace std;

template <typename P, typename S>
class Solver : virtual public Cloneable<Solver<P,S>> {
 public:
    virtual S solve(P problem)=0;
};

#endif //ALGORITHMICPROGRAMMING2__SOLVER_H_
