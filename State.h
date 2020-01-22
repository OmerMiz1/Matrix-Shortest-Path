//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STATE_H_
#define ALGORITHMICPROGRAMMING2__STATE_H_

#include "Point.h"
#include "Stringable.h"
#include <list>
#include <string>

using namespace std;

template <class T>
class State : public Cloneable<State<T>>, public Stringable<T>, public Stringable<State<T>> {
private:
    T *my_state; // the state of this state
    double cost; //the cost that it took us to get to this state, 0 if this is the first state
    State<T> *prev_state; //the state that this state got from, null if this is the first state

public:
    State()=default;
    State(T *myState);
    State(T *myState, double cost, State<T> *prevState);

    T getState() const;
    double getCost() const;

    list<State<T>>* backtrace() const;

    void setPrev(State<T> *prev_state);

    bool is(State<T> other_state) const;
    bool operator==(const State<T> &other_state) const;
    bool operator<(const State<T> &other_state) const;
    bool operator>(const State<T> &other_state) const;
    string str() const override;

    class costComparator {
        bool operator()(const State<T> &first, const State<T> &second) const {
            return first.cost < second.cost;
        }
    }; /*Kinda useless, already overriding operators*/
    class positionComparator {
        bool operator()(const State<T> &first, const State<T> &second) const {
            return first.my_state < second.my_state;
        }
    };
    State<T>* clone() const override;
};

template class State<Point>;
#endif //ALGORITHMICPROGRAMMING2__STATE_H_
