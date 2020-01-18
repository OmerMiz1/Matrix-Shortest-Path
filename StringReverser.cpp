//
// Created by omer on 17/01/2020.
//

#include "StringReverser.h"

string StringReverser::solve(string problem) {
    string problem_reversed;

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
