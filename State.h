//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STATE_H_
#define ALGORITHMICPROGRAMMING2__STATE_H_

#include "Point.h"
#include <list>

using namespace std;
template <class T>
class State : Cloneable<State<T>> {
private:
    T *myState; // the state of this state
    double cost; //the cost that it took us to get to this state, 0 if this is the first state
    State<T> *prev_state; //the state that this state got from, null if this is the first state
    bool last_in_path(State<T>);

public:
    State() {}; /*TODO: made this because Matrix C'Tor gave error initializing this->matrix[i]*/
    State(T *myState, double cost, State<T> *prevState);
    explicit State(T *myState);
    T getState();
    double getCost();

    list<State<T>> backtrace() const;

    void setPrev(State<T> prev_state);

    bool is(State<T> other_state);
    bool operator==(State<T> other_state);
    bool operator<(State<T> other_state);
    bool operator>(State<T> other_state);
    State<T> clone() const override;
};

/*Alias to State<Point>*/
typedef State<Point> Vertex;

#endif //ALGORITHMICPROGRAMMING2__STATE_H_