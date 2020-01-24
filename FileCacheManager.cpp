//
// Created by Dor Refaeli on 15/01/2020.
//

#include <fstream>
#include <iostream>
#include "FileCacheManager.h"

/** Returns true if file matching problem-key already_existed, false o.w.
 *
 * @param problem_key problem_type + problem_hashed (key)
 * @return true/false.
 */
bool FileCacheManager::contains(string problem_key) {
    string file_name = addTxt(problem_key);
    ifstream ifile(file_name);
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
string FileCacheManager::get(string problem_key) {
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
void FileCacheManager::insert(string problem_key, string solution) {
    writeToFile(problem_key, solution); /*TODO DEBUG*/
}

/** Writes data to file (solution).
 * Helper for insert.
 *
 * @param problem_key
 * @param solution
 */
void FileCacheManager::writeToFile(string problem_key, string solution) {
    ofstream outFile(addTxt(problem_key));
    if (!outFile.is_open()) {
        throw "Failed to create a file";
    }

    /*Assuming string is a string here !!!*/
    outFile.clear();
    outFile << solution << endl;
    outFile.close();
}

/** Reads solution from file.
 *
 * @param problem_key
 * @return
 */
string FileCacheManager::readFromFile(string problem_key) {
    ifstream inFile(addTxt(problem_key));

    char buffer[MAX_CHARS];
    string solution;

    if (!inFile.is_open()) {
        throw "Failed to read from an existing file";
    }

    while(!inFile.eof()) {
        inFile.read(buffer, sizeof(solution));
        solution.append(buffer);
    }

    inFile.close();
    return solution;
}

/** Adds ".txt" to string.
 *
 * @param problem_key
 * @return
 */
string FileCacheManager::addTxt(string problem_key) {
    /*Assuming problem is the problem represented as string*/
    return string (problem_key + ".txt");
}

FileCacheManager* FileCacheManager::clone() const {
    return new FileCacheManager();
}
