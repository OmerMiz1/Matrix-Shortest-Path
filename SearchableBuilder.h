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
    State<P> buildMatrixCell(int x,int y, double cost, Vertex* prev);
 public:
    Searchable<P>* buildMatrix(list<string> data);
};

typedef State<P> Vertex;
#endif //ALGORITHMICPROGRAMMING2__SEARCHABLEBUILDER_H_
