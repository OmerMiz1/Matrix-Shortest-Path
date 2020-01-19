//
// Created by doref on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_MATRIX_H
#define ALGORITHMICPROGRAMMING2_MATRIX_H

#include <vector>
#include <algorithm>

#include "Point.h"
#include "State.h"

using namespace std;

template<typename T>
class Matrix {

 protected:
    friend class SearcableBuilder;
    int rows_count;
    int columns_count;
    vector<vector<T>> matrix;

    virtual void addRow(vector<T>* new_row);
    virtual void removeRow(int row_num); /*Made it for symmetry, currently no use*/
    /*void addCol(vector<T>);TODO: is it necessary?
     *void removeCol(int*/

 public:
    /*Matrix(int rows, int columns);*/
    /*~Matrix();*/
    const T *getCell(int x, int y);
    int getRowsCount();
    int getColsCount();
};

template
class Matrix<Vertex>;

#endif //ALGORITHMICPROGRAMMING2_MATRIX_H
