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

/** Might throw exception?
 * Returns a certain cell of the matrix
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 * @return the cell in the (x,y) place in the matrix
 */
T* Matrix<T>::at(int x, int y)  {
    try {
        return &this->matrix.at(x).at(y);
    } catch(const char* e) { /*catches out_of_bounds exceptions*/
        return nullptr;
    }
}

template<typename T>
T *Matrix<T>::at(Point point) {
    return at(point.getX(), point.getY());
}

/*template<typename T>
T* Matrix<T>::find(T cell) {
    if(value_point_map.count(cell)) {
        return value_point_map.find(cell);
    }
    *//*for(auto row : matrix) {
        for(auto element : row) {
            if((*element) == cell) {
                return &element;
            }
        }
    }*//*
    return nullptr;
}*/

/**
 * Returns the number of rows in the matrix
 * @return the number of rows in the matrix
 */
template<typename T>
int Matrix<T>::getRowsCount()  {
    return rows_count;
}

/**
 * Returns the number of columns in the matrix
 * @return the number of columns in the matrix
 */
template<typename T>
int Matrix<T>::getColsCount()  {
    return columns_count;
}

/** Add an entire row to matrix.
 * TODO: PROBLEM: new_row length can be different than cols_count!
 *  POSSIBLE SOLUTION1: first element of each row vector will specify the count.
 *  POSSIBLE SOLUTION2: keep a map for sizes of each row.
 * @tparam T
 * @param new_row
 */
template <typename T>
void Matrix<T>::addRow(vector<T>* new_row) {
    int cur_col = 0;
    for(auto it = new_row->begin(); it != new_row->end(); ++it,++cur_col) {
        matrix.at(rows_count).at(cur_col) = *it;
        value_point_map[*it] = Point(rows_count,cur_col);
    }
    row_size_map[matrix.at(rows_count)] = new_row->size();
    this->rows_count++;
}


/** Removes specific row.
 *
 * @tparam T
 * @param row_num index of row to be removed
 */
template<typename T>
void Matrix<T>::removeRow(int row_num) {
    auto startIt = this->matrix.at(row_num).begin();
    auto endIt = this->matrix.at(row_num).end();
    this->matrix.at(row_num).erase(startIt, endIt);
    this->rows_count--;
}

template<typename T>
Point* Matrix<T>::getPoint(T cell) const {
    if(value_point_map.count(cell)) {
        return value_point_map.find(cell)->clone();
    }
}

template<typename T>
T *Matrix<T>::getAbove(T state) {
    auto p = getPoint(state);
    return at(p->getX(), (p->getY()-1));
}

template<typename T>
T *Matrix<T>::getBelow(T state) {
    auto p = this->getPoint(state);
    return at(p->getX(), (p->getY()+1));
}

template<typename T>
T *Matrix<T>::getLeft(T state) {
    auto p = this->getPoint(state);
    return at(p->getX()-1, p->getY());
}

template<typename T>
T *Matrix<T>::getRight(T state) {
    auto p = this->getPoint(state);
    return at(p->getX()+1, p->getY());
}



