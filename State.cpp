//
// Created by Dor on 17/01/2020.
//

#include "State.h"

template<typename T>
State<T> State<T>::getState() {
    return this->myState;
}

template<typename T>
bool State<T>::operator==(State<T> other_state) {
    return this->myState == other_state.myState;
}

template<typename T>
State<T>::State(T myState, double cost, const State<T> &prevState):myState(myState), cost(cost),
                                                                   prev_state(prevState) {}

template<typename T>
State<T>::State(T myState):myState(myState) {
    this->cost = 0;
    this->prev_state = nullptr;
}

template<typename T>
bool State<T>::operator<(State<T> other_state) {
    return this->cost < other_state.cost;
}

template<typename T>
void State<T>::updateRoute(double cost, State<T> prev_state) {
    this->cost = cost;
    this->prev_state = prev_state;
}
