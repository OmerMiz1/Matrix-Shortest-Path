//
// Created by Dor on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
#define ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
//TODO change the class file aren't saved as binery + save only to files, no cache
#include <utility>
#include <string>
#include <list>
#include <unordered_map>

#include "CacheManager.h"

template<typename P, typename S>
class FileCacheManager : public CacheManager<P,S> {

public:
    void insert(P problem, S solution);
    bool contains(P given_problem);
    S get(P problem);

private:
    void writeToFile(P, S);
    S readFromFile(P);
};

template class FileCacheManager<string,string>;
#endif //ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
