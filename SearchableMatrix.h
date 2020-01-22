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
class SearchableMatrix : public Searchable<P>, public Matrix<P> {
 private:
    /*Allows SearchableBuilder::buildMatrix to use setters.*/
    template<typename S>
    friend class SearchableBuilder;

    P *initial_state = nullptr;
    P *goal_state = nullptr;

    void setInitialState(Point initial_point);
    void setGoalState(Point goal_point);

 public:
    P getInitialState() override;
    P getGoalState() const;
    bool isGoalState(P state) override;
    list<P> getAllPossibleStates(P state) override;
};

template class SearchableMatrix<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2_SEARCHABLEMATRIX_H
