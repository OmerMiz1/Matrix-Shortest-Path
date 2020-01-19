//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SEARCHEABLEBUILDER_H_
#define ALGORITHMICPROGRAMMING2__SEARCHEABLEBUILDER_H_

#include <string>
#include <bits/stdc++.h> /*Used for tolower(string)*/
#include <regex>

#include "SearchableMatrix.h"

using namespace std;

class SearcheableBuilder {
 public:
    SearchableMatrix* buildMatrix(list<string> data);
    Point* buildMatrixState(string state_str);
    Vertex buildMatrixCell(int x,int y, int cost, Vertex* prev);
};


#endif //ALGORITHMICPROGRAMMING2__SEARCHEABLEBUILDER_H_
