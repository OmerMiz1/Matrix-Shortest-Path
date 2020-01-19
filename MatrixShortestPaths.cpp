//
// Created by omer on 19/01/2020.
//

#include "MatrixShortestPaths.h"

template<typename P, typename S>
list<Vertex> MatrixShortestPaths<P, S>::solve(Searchable<Point> sMatrix) {
    list<Vertex> shorthest_path;
    auto my_searcher = new BestFirstSearch<Searchable<Point>,list<Vertex>>();
    this->shortest_path = my_searcher.search(sMatrix);
    this->path_cost = calculatePathCost();
    return this->shortest_path;
}

/*TODO: not really in use*/
template<typename P, typename S>
void MatrixShortestPaths<P, S>::calculatePathCost() {
    if(this->shortest_path.empty()) {
        return;
    }

    for(auto state : this->shortest_path) {
        this->path_cost += state.getCost();
    }
}

