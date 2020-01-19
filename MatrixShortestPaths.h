//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MATRIXSHORTESTPATHS_H_
#define ALGORITHMICPROGRAMMING2__MATRIXSHORTESTPATHS_H_

#include "Solver.h"
#include "State.h"
#include "Searchable.h"
#include "Point.h"

#include <list>
#include <climits>

/*Object Adapter*/
template <typename P, typename S>
class MatrixShortestPaths : public Solver<P, S> {
 private:
    list<Vertex> shortest_path;
    long path_cost = INT_MAX;

    /*TODO: not really in use*/
    void calculatePathCost();

 public:
    list<Vertex> solve(Searchable<Point> sMatrix) override;

};

#endif //ALGORITHMICPROGRAMMING2__MATRIXSHORTESTPATHS_H_
