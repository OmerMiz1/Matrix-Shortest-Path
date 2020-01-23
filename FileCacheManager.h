//
// Created by Dor on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
#define ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_

#define MAX_CHARS 1024

#include <utility>
#include <string>
#include <list>
#include <unordered_map>

#include "CacheManager.h"

template<typename P, typename S>
class FileCacheManager : public CacheManager<P,S> {

public:
    void insert(P problem, S solution) override;
    bool contains(P given_problem) override;
    S get(P problem) override;
    FileCacheManager<P,S>* clone() const override;

private:
    void writeToFile(P, S);
    S readFromFile(P);
    string toFileName(P problem);
};

template class FileCacheManager<string,string>;
#endif //ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
