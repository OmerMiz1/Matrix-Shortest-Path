//
// Created by Dor on 15/01/2020.
//

#include <fstream>
#include <iostream>
#include "FileCacheManager.h"

template<typename P, typename S>
bool FileCacheManager<P, S>::contains(P problem) {
    string file_name = toFileName(problem);
    ifstream ifile(file_name);
    bool exists = ifile.good();
    if(ifile.is_open()) {
       ifile.close();
    }
    return exists;
}

template<typename P, typename S>
S FileCacheManager<P, S>::get(P problem) {
    //if known problem read it from file and return it
    if (contains(problem)) {
        return readFromFile(toFileName(problem));
    } else {
        perror("asked for a solution without validating it's existence"); //TODO remove before submitting
        return nullptr;
    }
}

template<typename P, typename S>
void FileCacheManager<P, S>::insert(P problem, S solution) {
    if (contains(problem)) {
        perror("writing a known solution"); /*TODO*/
    }
    writeToFile(problem, solution);
}

template<typename P, typename S>
void FileCacheManager<P, S>::writeToFile(P problem, S solution) {
    ofstream outFile;

    cout<<toFileName(problem)<<endl; /*TODO debug*/
    outFile.open(toFileName(problem) + "_" + problem + ".txt");
    if (!outFile.is_open()) {
        throw "Failed to create a file";
    }

    /*Assuming S is a string here !!!*/
    outFile.write(solution.c_str(), sizeof(S));
    outFile.close();
}

template<typename P, typename S>
S FileCacheManager<P, S>::readFromFile(P problem) {
    char buffer[MAX_CHARS];
    fstream inFile(toFileName(problem));
    S solution;
    if (!inFile.is_open()) {
        throw "Failed to read from an existing file";
    }
    inFile.read(buffer, sizeof(solution));
    inFile.close();
    solution = buffer;
    return solution;
}

template<typename P, typename S>
string FileCacheManager<P,S>::toFileName(P problem) {
    /*Assuming problem is the problem represented as string*/
    return string (problem + ".txt");
}

template<typename P, typename S>
FileCacheManager<P, S>* FileCacheManager<P, S>::clone() const {
    return new FileCacheManager<P, S>();
}
