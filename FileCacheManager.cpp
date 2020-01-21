//
// Created by Dor on 15/01/2020.
//

#include <fstream>
#include <iostream>
#include "FileCacheManager.h"

template<typename P, typename S>
bool FileCacheManager<P, S>::contains(P problem) {
    bool exist;
    string problemClassName = typeid(P).name(); //TODO change to typeid(*P).name() ???
    fstream test(problemClassName + "_" + problem, ios::in | ios::binary); //TODO change from binary to text
    if (test) {
        exist = true;
    } else {
        exist = false;
        test.close();
    }
    return exist;
}

template<typename P, typename S>
S FileCacheManager<P, S>::get(P problem) {
    //if known problem read it from file and return it
    if (contains(problem)) {
        return readFromFile(problem);
    } else {
        perror("asked for a solution without validating it's existence"); //TODO remove before submitting
        return nullptr;
    }
}

template<typename P, typename S>
void FileCacheManager<P, S>::insert(P problem, S solution) {
    if (this->contains(problem)) { //TODO for debugging purposes, remove before submitting
        perror("writing a known solution");
    }
    writeToFile(problem, solution);
}

template<typename P, typename S>
void FileCacheManager<P, S>::writeToFile(P problem, S solution) {
    ofstream outFile;
    string problemClassName = typeid(problem).name(); //TODO change to typeid(*P).name() ???
    /*TODO: debug check prints*/
    cout<<typeid(problem).name()<<endl;
    //out<<typeid(*problem).name()<<endl; //get by reference?
    outFile.open(problemClassName + "_" + problem, ios::binary); //TODO change from binary to text
    if (!outFile.is_open()) {
        throw "Failed to create a file";
    }
    outFile.write((char *)&solution, sizeof(S));
    outFile.close();
}

template<typename P, typename S>
S FileCacheManager<P, S>::readFromFile(P problem) {
    string problemClassName = typeid(P).name(); //TODO change to typeid(*P).name() ???
    fstream inFile(problemClassName + "_" + problem, ios::in | ios::binary); //TODO change from binary to text
    if (!inFile) {
        throw "Failed to read from an existing file";
    }
    S solution;
    inFile.read((char *)&solution, sizeof(solution));
    inFile.close();
    return solution;
}

template<typename P, typename S>
FileCacheManager<P, S>* FileCacheManager<P, S>::clone() const {
    return new FileCacheManager<P, S>();
}
