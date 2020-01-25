//
// Created by Dor Refaeli on 18/01/2020.
//

#include "Matrix.h"

/**
 * D'TOR
 */
template<typename T>
Matrix<T>::~Matrix() {
    for (vector<T *> *row : this->matrix) {
        for (T *cell : *row) {
            delete (cell);
        }
        delete (row);
    }
}

/** Returns the cell at (x,y).
 *
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 * @return the cell in the (x,y) place in the matrix, nullptr if out of bounds.
 */
template<typename T>
T* Matrix<T>::at(int x, int y) const {
    //bounds check
    if (x < 0 || x >= matrix.size() || y < 0 || y >= this->matrix.at(x)->size()) {
        return OUT_OF_BOUNDS;
    }
    return matrix.at(x)->at(y);
}

/** Returns the cell given a point (x,y) object.
 *
 * @tparam T
 * @param point
 * @return
 */
template<typename T>
T* Matrix<T>::at(Point point) const {
    return at(point.getX(), point.getY());
}

/**
 * Returns the number of rows in the matrix
 * @return the number of rows in the matrix
 */
template<typename T>
int Matrix<T>::getRowsCount() const {
    return rows_count;
}

/**
 * Returns the number of columns in the matrix
 * @return the number of columns in the matrix
 */
template<typename T>
int Matrix<T>::getColsCount() const {
    return columns_count;
}

/** Add an entire row to matrix.
 * @tparam State<Point>
 * @param new_row vector.
 */
template<typename T>
void Matrix<T>::addRow(vector<T> *new_row) {
    int cur_col = 0;
    /*Allocate memory for new row*/
    auto tempRow = new vector<T *>();
    matrix.push_back(tempRow);

    /*Add cell by cell*/
    for (auto it = new_row->begin(); it != new_row->end(); ++it, ++cur_col) {
        T temp = *it;
        T *cell = new T(temp);
        matrix.at(rows_count)->push_back(cell);
        value_point_map[&temp] = Point(rows_count, cur_col);
    }

    /*Assuming all matrices are of order NxN*/
    this->columns_count = new_row->size();
    this->rows_count++;
}

/** Removes specific row, still needs to be tested!
 * Not in use currently.
 *
 * @tparam T
 * @param row_num index of row to be removed
 */
template<typename T>
void Matrix<T>::removeRow(int row_num) {
    auto startIt = this->matrix.at(row_num)->begin();
    auto endIt = this->matrix.at(row_num)->end();
    this->matrix.at(row_num)->erase(startIt, endIt);
    this->rows_count--;
}

/**
 * Given a cell, returns its point in the matrix.
 *
 * @tparam State<Point>
 * @param cell to get point.
 * @return
 */
template<typename T>
Point Matrix<T>::getPoint(T cell) const {
    int row_num = 0, col_num = 0;

    for (auto row : matrix) {
        for (auto element : *row) {
            if (cell.getState() == element->getState()) {
                return cell.getState();
            }
            ++col_num;
        }
        col_num = 0;
        ++row_num;
    }
}

/** Returns the cell above given.
 *
 * @tparam State<T>
 * @param state
 * @return
 */
template<typename T>
T* Matrix<T>::getAbove(T state) const {
    auto p = getPoint(state);
    return at(p.getX(), (p.getY() - 1));
}

/** Returns the cell below given.
 *
 * @tparam State<Point>
 * @param state
 * @return
 */
template<typename T>
T* Matrix<T>::getBelow(T state) const {
    auto p = getPoint(state);
    return at(p.getX(), (p.getY() + 1));
}

/** Returns the cell to the left of given.
 *
 * @tparam State<Point>
 * @param state
 * @return
 */
template<typename T>
T* Matrix<T>::getLeft(T state) const {
    auto p = getPoint(state);
    return at(p.getX() - 1, p.getY());
}

/** Returns the cell to the right of given.
 *
 * @tparam State<Point>
 * @param state
 * @return
 */
template<typename T>
T* Matrix<T>::getRight(T state) const {
    auto p = getPoint(state);
    return at(p.getX() + 1, p.getY());
}





