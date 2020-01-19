//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STATE_H_
#define ALGORITHMICPROGRAMMING2__STATE_H_

#include "Point.h"



template<typename T>
class State {
private:
    T *myState; // the state of this state
    double cost; //the cost that it took us to get to this state, 0 if this is the first state
    State<T> *prev_state; //the state that this state got from, null if this is the first state

    /*State<T> getPrev();*/

public:
    State() {}; /*TODO: made this because Matrix C'Tor gave error initializing this->matrix[i]*/
    State(T *myState, double cost, State<T> *prevState);
    explicit State(T *myState);
    T* getState();
    int getCost();

    bool is(State<T> other_state);
    bool operator==(State<T> other_state);
    bool operator<(State<T> other_state);
    bool operator>(State<T> other_state);
};

/*Alias to State<Point>*/
typedef State<Point> Vertex;

/*Templates supported*/
template class State<Point>;

#endif //ALGORITHMICPROGRAMMING2__STATE_H_
