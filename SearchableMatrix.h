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
class SearchableMatrix : public Searchable<P>, public Matrix<Vertex> {
 private:
    /*Allows SearchableBuilder::buildMatrix to use setters.*/
    template<P>
    friend class SearchableBuilder;

    Vertex *initial_state = nullptr;
    Vertex *goal_state = nullptr;

    State<P>* getAbove(State<P> state);
    State<P>* getBelow(State<P> state);
    State<P>* getLeft(State<P> state);
    State<P>* getRight(State<P> state);

    void addRow(vector<Vertex>*) override;
    void removeRow(int) override;
    void setInitialState(P* initial_point);
    void setGoalState(P* goal_point);

    /*TODO: Maybe using vector's regular at() is faster?*/
    bool isValidCellInMatrix(int x, int y);

 public:
    Vertex getInitialState() override;
    bool isGoalState(Vertex state) override;
    list<Vertex> getAllPossibleStates(Vertex state) override;
    State<P>* getCell(P*);
    State<P>* getCell(int, int) override;
};

#endif //ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
