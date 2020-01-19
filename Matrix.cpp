//
// Created by doref on 18/01/2020.
//

#include "Matrix.h"

/**
 * A constructor to Matrix
 * @param rows the number of rows in the matrix
 * @param columns the number columns in the matrix
 */
template <typename T>
/*Matrix<T>::Matrix(int rows, int columns): rows_count(rows), columns_count(columns) {
    this->matrix = new T*[rows_count];
    for(int i = 0; i < rows_count; ++i) {
        this->matrix[i] = new T[columns_count];
    }
}*/

/**
 * A d'tor for Matrix
 */
/*template<typename T>
Matrix<T>::~Matrix() {
    for(int i = 0; i < rows_count; ++i) {
        delete(this->matrix[i]);
    }
    delete(this->matrix);
}*/

/**
 * Returns a certain cell of the matrix
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 * @return the cell in the (x,y) place in the matrix
 */
const T *Matrix<T>::getCell(int x, int y)  {
    return &(this->matrix[x][y]);
}

/**
 * Returns the number of rows in the matrix
 * @return the number of rows in the matrix
 */
template<typename T>
int Matrix<T>::getRowsCount()  {
    return this->rows_count;
}

/**
 * Returns the number of columns in the matrix
 * @return the number of columns in the matrix
 */
template<typename T>
int Matrix<T>::getColumnsCount()  {
    return this->columns_count;
}

