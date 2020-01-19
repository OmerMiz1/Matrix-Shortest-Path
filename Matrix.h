//
// Created by doref on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_MATRIX_H
#define ALGORITHMICPROGRAMMING2_MATRIX_H

#include "Point.h"
#include "State.h"

template<typename T>
class Matrix {
protected:
    int rows_count;
    int columns_count;
    T **matrix;

public:
    /*Matrix(int rows, int columns);*/
    ~Matrix();
    const T* getCell(int x, int y);
    int getRowsCount();
    int getColumnsCount();
};

template class Matrix<Vertex>;

#endif //ALGORITHMICPROGRAMMING2_MATRIX_H
