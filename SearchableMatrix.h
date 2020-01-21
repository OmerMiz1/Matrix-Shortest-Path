//
// Created by doref on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
#define ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H

#include <unordered_map>
#include <list>

#include "State.h"
#include "Point.h"
#include "Searchable.h"
#include "Matrix.h"
//#include "SearchableBuilder.h"

template <class P>
class SearchableMatrix : public Searchable<P>, public Matrix<State<P>> {
 private:
    /*Allows SearchableBuilder::buildMatrix to use setters.*/
    template<typename S>
    friend class SearchableBuilder;

    State<P> *initial_state = nullptr;
    State<P> *goal_state = nullptr;

    void setInitialState(Point initial_point);
    void setGoalState(Point goal_point);

    /*    State<P>* getAbove(State<P> state);
    State<P>* getBelow(State<P> state);
    State<P>* getLeft(State<P> state);
    State<P>* getRight(State<P> state);

    void addRow(vector<State<P>>*) override;
    void removeRow(int) override;
     bool isValidCellInMatrix(int x, int y);*/

 public:
    State<P> getInitialState() override;
    bool isGoalState(State<P> state) override;
    list<State<P>> getAllPossibleStates(State<P> state) override;
/*    State<P>* getCell(int, int) override;
    State<P>* getCell(P*);*/
};
#endif //ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
