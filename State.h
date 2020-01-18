//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STATE_H_
#define ALGORITHMICPROGRAMMING2__STATE_H_

template<typename T>
class State {
private:
    T myState; //the state of this state
    double cost; //the cost that it took us to get to this state, 0 if this is the first state
    State<T> prev_state; //the state that this state got from, null if this is the first state
public:
    State(T myState, double cost, const State<T> &prevState);

    explicit State(T myState);

    State<T> getState();

    bool operator==(State<T> other_state);

    bool operator<(State<T> other_state);

    void updateRoute(double cost, State<T> prev_state);
};

#endif //ALGORITHMICPROGRAMMING2__STATE_H_
