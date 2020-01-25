//
// Created by Omer Mizrachi on 17/01/2020.
//

#include "StringReverser.h"

/** Returns the string reveresed.
 *
 * @tparam P
 * @param problem
 * @return
 */
template<class P>
P StringReverser<P>::solve(P *problem) {
    P problem_reversed;

    /*Empty word or 1 char, nothing is need to be done*/
    if(problem->length() <= 1) {
        return *problem;
    }

    /*Making sure no garbage inside*/
    problem_reversed.clear();

    /*Iterate problem string in reversed order*/
    for(auto it = problem->rbegin(); it != problem->rend(); ++it) {
        problem_reversed.push_back(*it);
    }
    return problem_reversed.append("\n");
}

template<class P>
StringReverser<P>* StringReverser<P>::clone() const {
    return new StringReverser<P>();
}

template<class P>
string StringReverser<P>::str() const {
   string result = "StringReverser";
   return result;
}
