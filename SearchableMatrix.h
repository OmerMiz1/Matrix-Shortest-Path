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

class SearchableMatrix : public Searchable<Point>, public Matrix<State<Point>> {
 private:
    State<Point> *initial_state = nullptr;
    State<Point> *goal_state;

    State<Point>* getAbove(State<Point> state);
    State<Point>* getBelow(State<Point> state);
    State<Point>* getLeft(State<Point> state);
    State<Point>* getRight(State<Point> state);
    bool isValidCellInMatrix(int x, int y);

 public:
    State<Point> getInitialState() override;
    bool isGoalState(State<Point> state) override;
    list<State<Point>> getAllPossibleStates(State<Point> state) override;
    State<Point>* getCell(Point*);
    State<Point>* getCell(int, int) override;

    /*TODO: AddRow and RemoveRow shouldnt be public! BANDAGE!*/
    void addRow(vector<Vertex>*) override;
    void removeRow(int) override;
    void setInitialState(Point* initial_point);
    void setGoalState(Point* goal_point);
};


#endif //ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
