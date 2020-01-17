//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MAIN_H_
#define ALGORITHMICPROGRAMMING2__MAIN_H_

#define CACHE_CAPACITY 10

#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"

class Main {
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            clog<<"Error: not enough arguments..."<<endl;
            exit(EXIT_FAILURE);
        }
        int port = stoi(argv[0]);
        Solver<string,string> *solver = new StringReverser();
        CacheManager<string,string> *cache = new FileCacheManager<string,string>(CACHE_CAPACITY);
        ClientHandler *handler = new MyTestClientHandler(solver, cache);
        Server *mss = new MySerialServer();
    }
};

#endif //ALGORITHMICPROGRAMMING2__MAIN_H_
