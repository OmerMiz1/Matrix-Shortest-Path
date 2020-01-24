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

/** FileCacheManager uses files to cache evaluted data.
 * File must be hashed properly.
 */
class FileCacheManager : public CacheManager<string,string> {
public:
    void insert(string *problem_key, string* content) override;
    bool contains(string* problem_key) override;
    string* get(string* problem_key) override;
    FileCacheManager* clone() const override;

private:
    void writeToFile(string *problem_key, string *content);
    string* readFromFile(string *problem_key);
    string* addTxt(string *problem);
};

#endif //ALGORITHMICPROGRAMMING2__FILECACHEMANAGER_H_
