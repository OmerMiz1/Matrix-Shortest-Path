//
// Created by Dor Refaeli on 15/01/2020.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include "FileCacheManager.h"

/** Returns true if file matching problem-key already_existed, false o.w.
 *
 * @param problem_key problem_type + problem_hashed (key)
 * @return true/false.
 */
bool FileCacheManager::contains(string *problem_key) {
    string* file_name;
    if(!strstr(problem_key->c_str(), ".txt")) {
        file_name = addTxt(problem_key);
    } else {
        file_name = problem_key;
    }

    ifstream ifile(*file_name);
    bool exists = ifile.good();

    /*If file do exists, close it and return result*/
    if(ifile.is_open()) {
       ifile.close();
    }
    return exists;
}

/** Gets solution to given problem_key-key.
 *
 * @param problem_key
 * @return The solution if exists, o.w. nullptr.
 */
string* FileCacheManager::get(string *problem_key) {
    //if known problem_key read it from file and return it
    if (contains(problem_key)) {
        return readFromFile(problem_key);
    } else {
        return nullptr;
    }
}

/** Insert problem_key to cache
 *
 * @param problem_key
 * @param solution
 */
void FileCacheManager::insert(string *problem_key, string *solution) {
    writeToFile(problem_key, solution); /*TODO DEBUG*/
}

/** Writes data to file (solution).
 * Helper for insert.
 *
 * @param problem_key
 * @param solution
 */
void FileCacheManager::writeToFile(string *problem_key, string *solution) {
    ofstream outFile;
    if(!strstr(problem_key->c_str(), ".txt")) {
        outFile.open(*addTxt(problem_key));
    } else {
        outFile.open(*problem_key);
    }

    if (!outFile.is_open()) {
        throw "Failed to create a file";
    }

    /*Assuming string is a string here !!!*/
    outFile.clear();
    outFile << *solution << endl;
    outFile.close();
}

/** Reads solution from file.
 *
 * @param problem_key
 * @return
 */
string* FileCacheManager::readFromFile(string *problem_key) {
    ifstream inFile;
    if(!strstr(problem_key->c_str(), ".txt")) {
        inFile.open(*addTxt(problem_key));
    } else {
        inFile.open(*problem_key);
    }
    auto solution = new string();
    if (!inFile.is_open()) {
        throw "Failed to read from an existing file";
    }

    while(!inFile.eof()) {
        char *buffer = (char*)malloc(MAX_CHARS);
        inFile.read(buffer, MAX_CHARS-1);
        solution->append(buffer);
    }

    inFile.close();
    return solution;
}

/** Adds ".txt" to string.
 *
 * @param problem_key
 * @return
 */
string* FileCacheManager::addTxt(string *problem_key) {
    /*Assuming problem is the problem represented as string*/
    problem_key->append(".txt");
    return problem_key;
}

FileCacheManager* FileCacheManager::clone() const {
    return new FileCacheManager();
}
