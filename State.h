//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STATE_H_
#define ALGORITHMICPROGRAMMING2__STATE_H_

#include "Point.h"
#include <list>

using namespace std;

template <class T>
class State : public Cloneable<State<T>> {
private:
    T *myState; // the state of this state
    double cost; //the cost that it took us to get to this state, 0 if this is the first state
    State<T> *prev_state; //the state that this state got from, null if this is the first state

public:
    State()=default;
    State(T *myState);
    State(T *myState, double cost, State<T> *prevState);

    T getState() const;
    double getCost();

    list<State<T>>* backtrace() const;

    void setPrev(State<T> *prev_state);

    bool is(State<T> other_state) const;
    bool operator==(State<T> &other_state);
    bool operator<(State<T> &other_state);
    bool operator>(State<T> &other_state);

    class costComparator {
        bool operator()(const State<T> &first, const State<T> &second) const {
            return first.cost < second.cost;
        }
    }; /*Kinda useless, already overriding operators*/
    class positionComparator {
        bool operator()(const State<T> &first, const State<T> &second) const {
            return first.myState < second.myState;
        }
    };
    State<T>* clone() const override;
};

template class State<Point>;
#endif //ALGORITHMICPROGRAMMING2__STATE_H_
