//
// Created by Omer Mizrachi on 17/01/2020.
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
    T *my_state; // inner state.
    int cost; // the cost until this state.
    State<T> *prev_state; // where we came from

public:
//    ~State();
    State();
    State(T *myState);
    State(T *myState, int myCost, State<T> *prevState);
    State(int x, int y, int myCost, State<T> *prevState);

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
