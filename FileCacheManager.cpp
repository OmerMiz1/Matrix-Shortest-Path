//
// Created by Dor Refaeli on 15/01/2020.
//

#include <fstream>
#include <iostream>
#include "FileCacheManager.h"

bool FileCacheManager::contains(string problem) {
    string file_name = addTxt(problem);
    ifstream ifile(file_name);
    bool exists = ifile.good();
    if(ifile.is_open()) {
       ifile.close();
    }
    return exists;
}

string FileCacheManager::get(string problem) {
    //if known problem read it from file and return it
    if (contains(problem)) {
        return readFromFile(problem);
    } else {
        perror("asked for a solution without validating it's existence"); //TODO remove before submitting
        return nullptr;
    }
}

void FileCacheManager::insert(string problem, string solution) {
    writeToFile(problem, solution);
}

void FileCacheManager::writeToFile(string problem, string solution) {
    ofstream outFile(addTxt(problem));
    cout<<addTxt(problem)<<endl; /*TODO debug*/

    if (!outFile.is_open()) {
        throw "Failed to create a file";
    }
    /*Assuming string is a string here !!!*/
    outFile.clear();
    outFile << solution << endl;
    outFile.close();
}

string FileCacheManager::readFromFile(string problem) {
    ifstream inFile(addTxt(problem));
    cout<<addTxt(problem)<<endl; /*TODO debug*/

    char buffer[MAX_CHARS];
    string solution;

    if (!inFile.is_open()) {
        throw "Failed to read from an existing file";
    }

    inFile.read(buffer, sizeof(solution));
    inFile.close();

    solution = buffer;
    return solution;
}

string FileCacheManager::addTxt(string problem_key) {
    /*Assuming problem is the problem represented as string*/
    return string (problem_key + ".txt");
}

FileCacheManager* FileCacheManager::clone() const {
    return new FileCacheManager();
}
