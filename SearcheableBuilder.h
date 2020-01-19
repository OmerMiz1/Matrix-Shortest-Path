//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SEARCHEABLEBUILDER_H_
#define ALGORITHMICPROGRAMMING2__SEARCHEABLEBUILDER_H_

#include <string>
#include <bits/stdc++.h> /*Used for tolower(string)*/
#include <regex>

#include "SearchableMatrix.h"
#include "MyClientHandler.h"

using namespace std;

template <class P, class S>
class SearcheableBuilder {
 private:
    friend class MyClientHandler<P,S>;
    Searchable<P>* buildMatrix(list<string> data);
    P* buildMatrixState(string state_str);
    State<P> buildMatrixCell(int x,int y, int cost, Vertex* prev);
};


#endif //ALGORITHMICPROGRAMMING2__SEARCHEABLEBUILDER_H_
