//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_
#define ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_

#include "Solver.h"
#include <string>
#include <cstring>
#include <list>
#include <regex>

using namespace std;

template<class P, class S>
class StringReverser : public Solver<P,S> {
 public:
    S solve(P problem) override;
    Solver<P,S> clone() const override;
};

#endif //ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_
