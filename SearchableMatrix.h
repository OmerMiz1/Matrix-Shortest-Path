//
// Created by Dor Refaeli on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
#define ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H

#include <unordered_map>
#include <list>

#include "State.h"
#include "Point.h"
#include "Matrix.h"
#include "Searchable.h"

template <typename P>
class SearchableMatrix : public Searchable<P>, public Matrix<P> {
 private:
    /*Allows SearchableBuilder::buildMatrix to use setters.*/
    template <typename S>
    friend class SearchableBuilder;

    P *initial_state = nullptr;
    P *goal_state = nullptr;

    void setInitialState(P initial_point_state);
    void setGoalState(P goal_point_state);

 protected:
    void addRow(vector<P> *new_row) override;
    void removeRow(int row_num) override;

 public:
    P getInitialState() const override;
    P getGoalState() const override;
    bool isGoalState(P state) const override;
    list<P> getAllPossibleStates(P state) override;
    string str() const override;

};

template class SearchableMatrix<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
