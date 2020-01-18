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

class SearchableMatrix : public Searchable<Point>, protected Matrix<State<Point>> {
private:
    State<Point> initial_state;
    State<Point> goal_state;
    State<Point> current_state;
public:
    //SearchableMatrix(char * buf) :Matrix<State<Point>>(30, 30) {} //TODO implement

    State<Point> getInitialState() override;

    bool isGoalState(State<Point> state) override;

    list<State<Point>> getAllPossibleStates(State<Point> state) override;

private:
    State<Point>* getAbove(State<Point> state);
    State<Point>* getBelow(State<Point> state);
    State<Point>* getLeft(State<Point> state);
    State<Point>* getRight(State<Point> state);
    bool isValidCellInMatrix(int x, int y);
};


#endif //ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
