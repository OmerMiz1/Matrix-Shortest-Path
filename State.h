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

public:
    State() {}; /*TODO: made this because Matrix C'Tor gave error initializing this->matrix[i]*/
    State(T *myState, double cost, State<T> *prevState);

    T getState();
    double getCost();

    list<State<T>> backtrace() const;

    void setPrev(State<T> prev_state);

    bool is(State<T> other_state);
    bool operator==(State<T> other_state);
    bool operator<(State<T> other_state);
    bool operator>(State<T> other_state);

    class costComparator {
        bool operator()(const State<T> first, const State<T> second) {
            return first.cost<second.cost;
        }
    }; /*Kinda useless, already overriding operators*/
    class positionComparator {
        bool operator()(const State<T> first, const State<T> second) {
            return *(first.getState())<*(second.getState());
        }
    };

    State<T> clone() const override;
};

/*Alias to State<Point>*/
typedef State<class T> Vertex;

#endif //ALGORITHMICPROGRAMMING2__STATE_H_
