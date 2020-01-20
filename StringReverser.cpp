//
// Created by omer on 17/01/2020.
//

#include "StringReverser.h"

;template<class P, class S>
S StringReverser<P, S>::solve(P problem) {
    P problem_reversed;

    /*Empty word or 1 char, nothing is need to be done*/
    if(problem.length() <= 1) {
        return problem;
    }

    /*Making sure no garbage inside*/
    problem_reversed.clear();

    /*Iterate problem string in reversed order*/
    for(auto it = problem.rbegin(); it != problem.rend(); ++it) {
        problem_reversed.push_back(*it);
    }
    return problem_reversed.append("\n");
}

template<class P, class S>
StringReverser<P, S>* StringReverser<P, S>::clone() const {
    return new StringReverser<P, S>();
}
