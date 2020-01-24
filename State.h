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

/*TODO future assignments: make a namespace for our comparators and stick them
all in there.*/
/**
 * Comparator for costs of states.
 * @tparam T
 */
template <class T>
class costComparator {
public:
    bool operator()(const T &first, const T &second) const {
        return first.getCost() > second.getCost();
    }
};

/** Comparator for positions of states.
 *
 * @tparam T
 * @return true if points of states are same.
 */
template <class T>
class positionComparator {
public:
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs.getState().uniq() < rhs.getState().uniq();
    }
};

/** A point with value, mainly for graphs (node).
 *
 * @tparam State<T>
 */
template <class T>
class State : public Cloneable<State<T>>, public Stringable<T>, public Stringable<State<T>> {
private:
    T *my_state; // the state of this state
    int cost; //the cost that it took us to get to this state, 0 if this is the first state
    State<T> *prev_state; //the state that this state got from, null if this is the first state

public:
    State()=default;
    State(T *myState);
    State(T *myState, int cost, State<T> *prevState);
    State(int x, int y, int cost, State<T> *prevState);

    T getState() const;
    int getCost() const;
    int getPrevCost() const;
    void setPrev(State<T> *prev_state);

    list<State<T>>* backtrace() const;
    State<T>* clone() const override;
    bool is(State<T> other_state) const;
    string str() const override;

    bool operator==(const State<T> &other_state) const;
    bool operator<(const State<T> &other_state) const;
    bool operator>(const State<T> &other_state) const;
};

template class costComparator<State<Point>>;
template class positionComparator<State<Point>>;
template class State<Point>;
#endif //ALGORITHMICPROGRAMMING2__STATE_H_
