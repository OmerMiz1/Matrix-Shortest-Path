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

 public:
    P getInitialState() override;
    P getGoalState() const;
    bool isGoalState(State<P> state) override;
    list<State<P>> getAllPossibleStates(State<P> state) override;
};
#endif //ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
