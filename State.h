//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__STATE_H_
#define ALGORITHMICPROGRAMMING2__STATE_H_

template <typename T>
class State {
 private:
    T myState;
    double cost;
    State<T> prev_state;
 public:
    State<T> getState();
    void setState(State<T> new_state);
    bool operator==(State<T> other_state);
    bool operator<(State<T> other_state); /*TODO: Optional*/
    bool operator>(State<T> other_state); /*TODO: Optional*/
};

#endif //ALGORITHMICPROGRAMMING2__STATE_H_
