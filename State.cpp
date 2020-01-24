//
// Created by omer on 17/01/2020.
//

#include "State.h"

/**
 * A constructor to State
 * @param myState the current state
 * @param cost the cost that it took us to get to this state
 * @param prevState the state that this state got from
 */
template<typename T>
State<T>::State(T *myState, int cost, State<T> *prevState):my_state(myState), cost(cost),
                                                              prev_state(prevState) {}

/** Calls above C'TOR
 * An alternative constructor that gets only the state itself, for use when this state is the first one
 * @param myState the current state
 */
template<typename T>
State<T>::State(T *myState): State<T>(myState, -1, nullptr) {}

/** Explicit for State<Point>?
 *
 * @tparam T
 * @param x
 * @param y
 * @param cost
 * @param prevState
 */
template<class T>
State<T>::State(int x, int y, int cost, State<T> *prevState):State<T>(new T(x,y), cost, prevState)  {}

/**
 * Returns this states state
 * @return this states state
 */
template<typename T>
T State<T>::getState() const {
    return *(my_state->clone());
}

/** Returns state cost.
 *
 * @tparam T
 * @return
 */
template <typename T>
int State<T>::getCost() const{
    return this->cost;
}

/** Returns the cost of prev state.
 * Mainly for calculating the difference while searching.
 *
 * @tparam T
 * @return
 */
template<class T>
int State<T>::getPrevCost() const {
    if(prev_state == nullptr) {
        return 0;
    }
    return prev_state->getCost();
}

/** Returns true if state and cost are same (prev_states are not taken into an
 * account).
 *
 * @tparam T
 * @param other_state
 * @return
 */
template <typename T>
bool State<T>::is(State<T> other_state) const {
    return (this->cost == other_state.getCost()
    && this->my_state == other_state.getState().clone());
}

/**
 * Checks if this state's state equals to other state's state,
 * to be used mostly when checking if a state's state is the goal state
 * @param other_state the other state we want to check with
 * @return true - if their's states are equals, false - otherwise
 */
template<typename T>
bool State<T>::operator==(const State<T> &other_state) const{
    return (this->cost == other_state.getCost());
}

/**
 * Checks if this state's cost is smaller then an other state's cost
 * @param other_state the other state
 * @return true - if this state's cost is smaller then the other state's cost, false - otherwise
 */
template<typename T>
bool State<T>::operator<(const State<T> &other_state) const{
    return (this->cost < other_state.cost);
}

template<typename T>
bool State<T>::operator>(const State<T> &other_state) const{
    return (this->cost > other_state.cost);
}

/**
 * Only made it for SearchableBuilder to use.
 * @tparam T
 * @param prev
 */
template<typename T>
void State<T>::setPrev(State<T> *prev) {
    this->prev_state = prev;
    this->cost += prev->getCost();
}

template<class T>
State<T>* State<T>::clone() const {
    /*Case prev-state is nullptr*/
    if(prev_state == nullptr) {
        return new State<T>(my_state->clone(), this->cost, nullptr);
    }

    /*O.W*/
    return new State<T>(my_state->clone(), this->cost, this->prev_state->clone());
}

/** Method used when searcher reaches goal state.
 *
 * @tparam T
 * @return
 */
template<class T>
list<State<T>>* State<T>::backtrace() const {
    auto cloned = this->clone();

    /*First node in path*/
    if(prev_state == nullptr) {
        auto backtrace_path = new list<State<T>>;
        backtrace_path->push_back(*cloned);
        return backtrace_path;
    }

    /*O.W call recursively and add self*/
    auto backtrace_path = prev_state->backtrace();
    backtrace_path->push_back(*cloned);
    return backtrace_path;
}

/** Returns a string representation of the inner state (Point).
 *
 * @tparam T
 * @return
 */
template<class T>
string State<T>::str() const {
    return my_state->str();
}

