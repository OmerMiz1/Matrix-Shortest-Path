//
// Created by Dor Refaeli on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_MATRIX_H
#define ALGORITHMICPROGRAMMING2_MATRIX_H
#define OUT_OF_BOUNDS nullptr

#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

#include "Point.h"
#include "State.h"

using namespace std;

template<typename T>
class Matrix {
 protected:
    int rows_count=0;
    int columns_count=0;
    vector<vector<T*>*> matrix;
    map<T*, Point> value_point_map;

    T* getAbove(T cell) const; /*TODO: possible bug: output when tracing back the path will be inverted.*/
    T* getBelow(T state) const; /*TODO*/
    T* getLeft(T state) const; /*TODO*/
    T* getRight(T state) const; /*TODO*/

    virtual void addRow(vector<T>* new_row);
    virtual void removeRow(int row_num); /*Made it for symmetry, currently no use*/

 public:
//    Matrix();
    ~Matrix();
    T* at(int x, int y) const;
    T* at(Point point) const;
    /*T* find(T cell);*/
    Point getPoint(T cell) const;
    int getRowsCount() const;
    int getColsCount() const;
};

template class Matrix<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_MATRIX_H

