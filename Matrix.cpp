//
// Created by Dor Refaeli on 18/01/2020.
//


#include "Matrix.h"

/** Might throw exception?
 * Returns a certain cell of the matrix
 * @param x the x coordinate of the cell
 * @param y the y coordinate of the cell
 * @return the cell in the (x,y) place in the matrix
 */
template <typename T>
T* Matrix<T>::at(int x, int y)  {
    try {
        return &this->matrix.at(x).at(y);
    } catch(const char* e) { /*catches out_of_bounds exceptions*/
        return OUT_OF_BOUNDS;
    }
}

template<typename T>
T *Matrix<T>::at(Point point) {
    return at(point.getX(), point.getY());
}

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
    cout<<"HI"<<endl;
    matrix.emplace_back(vector<T>(new_row->size(),0));
    cout<<"BYE"<<endl;
    cout<<matrix.front().size()<<endl;
    for(auto it = new_row->begin(); it != new_row->end(); ++it,++cur_col) {
        matrix.at(rows_count).emplace_back(*it);
        value_point_map[*it] = Point(rows_count,cur_col);
    }
    cout<<"#4"<<endl;
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
Point Matrix<T>::getPoint(T cell) const {
    int row_num=0, col_num=0;

    for(auto row : matrix) {
        for(auto element : row) {
            if(cell == element) {
                return cell.getState();
            }
            ++col_num;
        }
        col_num = 0;
        ++row_num;
    }
}

template<typename T>
T *Matrix<T>::getAbove(T state) {
    auto p = getPoint(state);
    return at(p.getX(), (p.getY()-1));
}

template<typename T>
T *Matrix<T>::getBelow(T state) {
    auto p = getPoint(state);
    return at(p.getX(), (p.getY()+1));
}

template<typename T>
T *Matrix<T>::getLeft(T state) {
    auto p = getPoint(state);
    return at(p.getX()-1, p.getY());
}

template<typename T>
T *Matrix<T>::getRight(T state) {
    auto p = getPoint(state);
    return at(p.getX()+1, p.getY());
}



