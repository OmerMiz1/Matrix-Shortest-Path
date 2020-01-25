//
// Created by Omer Mizrachi on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_
#define ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_

#include "Solver.h"
#include <string>
#include <cstring>
#include <list>
#include <regex>

using namespace std;

/** Reverses strings.
 *
 * @tparam P
 */
template<class P>
class StringReverser : public Solver<P,P> {
 public:
    P solve(P *problem) override;
    StringReverser<P>* clone() const override;

    string str() const override;
};
template class StringReverser<string>;
#endif //ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_
