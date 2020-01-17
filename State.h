//
// Created by Dor on 17/01/2020.
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
    /**
     * A constructor to State
     * @param myState the current state
     * @param cost the cost that it took us to get to this state
     * @param prevState the state that this state got from
     */
    State(T myState, double cost, const State<T> &prevState);

    /**
     * An alternative constructor that gets only the state itself, for use when this state is the first one
     * @param myState the current state
     */
    explicit State(T myState);

    /**
     * Returns this states state
     * @return this states state
     */
    State<T> getState();

    /**
     * Checks if this state's state equals to other state's state,
     * to be used mostly when checking if a state's state is the goal state
     * @param other_state the other state we want to check with
     * @return true - if their's states are equals, false - otherwise
     */
    bool operator==(State<T> other_state);
    /**
     * Checks if this state's cost is smaller then an other state's cost
     * @param other_state the other state
     * @return true - if this state's cost is smaller then the other state's cost, false - otherwise
     */
    bool operator<(State<T> other_state);

    /**
     * Update the route to this states //TODO make sure to update priority queue too!
     * @param cost the new cost to get to this state
     * @param prev_state the new prev_state that we got to this state from
     */
    void updateRoute(double cost, State<T>prev_state);
};

#endif //ALGORITHMICPROGRAMMING2__STATE_H_
