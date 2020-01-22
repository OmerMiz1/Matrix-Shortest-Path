//
// Created by omer on 22/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STRINGABLE_H_
#define ALGORITHMICPROGRAMMING2__STRINGABLE_H_
#include <string>
using namespace std;

template <class T>
class Stringable {
    virtual string str() =0;
};
#endif //ALGORITHMICPROGRAMMING2__STRINGABLE_H_
