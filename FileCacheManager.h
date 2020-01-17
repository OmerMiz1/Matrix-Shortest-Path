//
// Created by Dor on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
#define ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_

#include <utility>
#include <string>
#include <list>
#include <bits/unordered_map.h>
#include "CacheManager.h"

template<typename P, typename S>
class FileCacheManager : CacheManager<P,S> {
    int capacity;
    int count = 0;
    //a list that will store all of the cache, sorted so will also be used as recently used indicator
    list<pair<P, S>> cacheList;
    //a map of pointers to the items of the list, so that getting an object will be O(1)
    unordered_map<P,typename list<pair<P, S>>::iterator> cacheMap;

public:
    FileCacheManager(int capacity);
    void insert(P problem, S solution);
    bool contains(P given_problem);
    S get(P problem);

private:
    void writeToFile(P, S);
    void updateFile(P, S);
    bool tryToReadFromFile(P);
    void removeLRU();
};

#endif //ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
