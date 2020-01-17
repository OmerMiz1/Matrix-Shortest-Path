//
// Created by omer on 15/01/2020.
//

#include <fstream>
#include "FileCacheManager.h"

template<typename P, typename S>
bool FileCacheManager<P, S>::contains(P problem) {
    return this->get(problem) != nullptr;
}

template<typename P, typename S>
S FileCacheManager<P, S>::get(P problem) {
    //if the problem is in the map
    if (cacheMap.find(problem) != cacheMap.end()) {
        typename list<pair<string, S>>::iterator pointer = cacheMap[problem];
        S solution = pointer->second;
        cacheList.erase(pointer);
        cacheList.push_front(make_pair(problem, solution));
        cacheMap[problem] = cacheList.begin();
        return cacheMap[problem]->second;
    }
    //if the problem isn't in the map, and in a file
    if (tryToReadFromFile(problem)) {
        return cacheList.begin()->second;
    }
    //if the problem isn't in the map or fhe file
    return nullptr;
}

template<typename P, typename S>
void FileCacheManager<P, S>::insert(P problem, S solution) { //TODO adjust
    bool inList = false;
    //if the problem is in the map
    if (cacheMap.find(problem) != cacheMap.end()) {
        inList = true;
    }
    //if the problem isn't in the map but in a file
    else if (tryToReadFromFile(problem)) {
        inList = true;
    }
    if (inList) {
        typename list<pair<string, S>>::iterator pointer = cacheMap[problem];
        cacheList.erase(pointer);
        cacheList.push_front(make_pair(problem, solution));
        cacheMap[problem] = cacheList.begin();
        updateFile(problem, solution);
    } else {
        if (count == capacity) {
            removeLRU();
        }
        cacheList.push_front(make_pair(problem, solution));
        cacheMap[problem] = cacheList.begin();
        count++;
        writeSoFile(problem, solution);
    }
}

template<typename P, typename S>
FileCacheManager<P, S>::FileCacheManager(int capacity):capacity(capacity) {}

template<typename P, typename S>
void FileCacheManager<P, S>::writeToFile(P problem, S solution) { //TODO adjust
    ofstream outFile;
    outFile.open(solution.class_name + "_" + problem, ios::binary);
    if (!outFile.is_open()) {
        throw "Failed to create a file";
    }
    outFile.write((char *)&solution, sizeof(S));
    outFile.close();
}

template<typename P, typename S>
void FileCacheManager<P, S>::updateFile(P problem, S solution) { //TODO adjust
    try {
        writeToFile(problem, solution);
    } catch (...) {
        throw "Failed to update a file";
    }
}

template<typename P, typename S>
bool FileCacheManager<P, S>::tryToReadFromFile(P problem) { //TODO adjust
    fstream inFile(S::class_name + "_" + problem, ios::in | ios::binary);
    if (!inFile) {
        return false;
    }
    if (count == capacity) {
        removeLRU();
    }
    S solution;
    inFile.read((char *)&solution, sizeof(solution));
    cacheList.push_front(make_pair(problem, solution));
    cacheMap[problem] = cacheList.begin();
    count++;
    return true;
}

template<typename P, typename S>
void FileCacheManager<P, S>::removeLRU() { //TODO adjust
    count--;
    typename list<pair<string, S>>::iterator pointer = cacheList.end();
    pointer--;
    string problem = pointer->first;
    cacheMap.erase(problem);
    cacheList.erase(pointer);
}
