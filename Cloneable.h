//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__CLONEABLE_H_
#define ALGORITHMICPROGRAMMING2__CLONEABLE_H_

template<typename T>
class Cloneable {
 public:
    virtual T* clone() const = 0;
};

#endif //ALGORITHMICPROGRAMMING2__CLONEABLE_H_
