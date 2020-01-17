//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_
#define ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_

#include "Solver.h"
#include <string>

using namespace std;

class StringReverser : public Solver<string,string> {
 private:

 public:
    string solve(string problem) override;
};

#endif //ALGORITHMICPROGRAMMING2__STRINGREVERSER_H_
