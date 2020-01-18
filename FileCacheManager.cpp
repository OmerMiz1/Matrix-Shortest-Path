//
// Created by Dor on 15/01/2020.
//

#include <fstream>
#include <iostream>
#include "FileCacheManager.h"

template<typename P, typename S>
FileCacheManager<P, S>::FileCacheManager(int capacity):capacity(capacity) {
    this->cacheList = new list<pair<P, S>>;
    this->cacheMap = new unordered_map<P,typename list<pair<P, S>>::iterator>;
}

template<typename P, typename S>
FileCacheManager<P, S>::~FileCacheManager() {
    delete this->cacheList;
    delete this->cacheMap;
}

template<typename P, typename S>
bool FileCacheManager<P, S>::contains(P problem) {
    //if the problem is in the map
    if (cacheMap->find(problem) != cacheMap->end()) {
        return true;
    }
    //if the problem isn't in the map return if it's in a file
    return tryToReadFromFile(problem);
}

template<typename P, typename S>
S FileCacheManager<P, S>::get(P problem) {
    //if the problem is in the map
    if (cacheMap->find(problem) != cacheMap->end()) {
        typename list<pair<P, S>>::iterator pointer = (*cacheMap)[problem];
        S solution = pointer->second;
        cacheList->erase(pointer);
        cacheList->push_front(make_pair(problem, solution));
        (*cacheMap)[problem] = cacheList->begin();
        return (*cacheMap)[problem]->second;
    }
    //if the problem isn't in the map, and in a file
    if (tryToReadFromFile(problem)) {
        return cacheList->begin()->second;
    }
    //if the problem isn't in the map or fhe file
    return nullptr;
}

template<typename P, typename S>
void FileCacheManager<P, S>::insert(P problem, S solution) {
    if (this->contains(problem)) {
        typename list<pair<P, S>>::iterator pointer = (*cacheMap)[problem];
        cacheList->erase(pointer);
        cacheList->push_front(make_pair(problem, solution));
        (*cacheMap)[problem] = cacheList->begin();
        updateFile(problem, solution);
    } else { //new problem
        if (count == capacity) {
            removeLRU();
        }
        cacheList->push_front(make_pair(problem, solution));
        (*cacheMap)[problem] = cacheList->begin();
        count++;
        writeToFile(problem, solution);
    }
}

template<typename P, typename S>
void FileCacheManager<P, S>::writeToFile(P problem, S solution) {
    ofstream outFile;
    string problemClassName = typeid(problem).name(); //TODO change to typeid(*P).name() ???
    /*TODO: debug check prints*/
    cout<<typeid(problem).name()<<endl;
    //out<<typeid(*problem).name()<<endl; //get by reference?
    outFile.open(problemClassName + "_" + problem, ios::binary);
    if (!outFile.is_open()) {
        throw "Failed to create a file";
    }
    outFile.write((char *)&solution, sizeof(S));
    outFile.close();
}

template<typename P, typename S>
void FileCacheManager<P, S>::updateFile(P problem, S solution) {
    try {
        writeToFile(problem, solution);
    } catch (...) {
        throw "Failed to update a file";
    }
}

template<typename P, typename S>
bool FileCacheManager<P, S>::tryToReadFromFile(P problem) {
    string problemClassName = typeid(P).name(); //TODO change to typeid(*P).name() ???
    fstream inFile(problemClassName + "_" + problem, ios::in | ios::binary);
    if (!inFile) {
        return false;
    }
    if (count == capacity) {
        removeLRU();
    }
    S solution;
    inFile.read((char *)&solution, sizeof(solution));
    cacheList->push_front(make_pair(problem, solution));
    (*cacheMap)[problem] = cacheList->begin();
    count++;
    return true;
}

template<typename P, typename S>
void FileCacheManager<P, S>::removeLRU() {
    count--;
    typename list<pair<P, S>>::iterator pointer = cacheList->end();
    pointer--;
    P problem = pointer->first;
    cacheMap->erase(problem);
    cacheList->erase(pointer);
}
