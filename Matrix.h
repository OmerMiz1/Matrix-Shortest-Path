//
// Created by doref on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_MATRIX_H
#define ALGORITHMICPROGRAMMING2_MATRIX_H

template<typename T>
class Matrix {
    int rows_count;
    int columns_count;
    T **matrix;
public:
    Matrix(int rows, int columns);
    ~Matrix();
    const T* getCell(int x, int y) const;
    int getRowsCount() const;
    int getColumnsCount() const;
};


#endif //ALGORITHMICPROGRAMMING2_MATRIX_H
