//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SEARCHABLEBUILDER_H_
#define ALGORITHMICPROGRAMMING2__SEARCHABLEBUILDER_H_

#include <string>
#include <bits/stdc++.h> /*Used for tolower(string)*/
#include <regex>

#include "SearchableMatrix.h"
#include "ClientHandler.h"

using namespace std;

template <class P>
class SearchableBuilder {
 private:
    P* buildMatrixState(string state_str);
    State<P> buildMatrixCell(int x,int y, double cost, State<P>* prev);

 public:
    SearchableMatrix<P>* buildMatrix(list<string> data);
};
template class SearchableBuilder<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2__SEARCHABLEBUILDER_H_
