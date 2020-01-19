//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MAIN_H_
#define ALGORITHMICPROGRAMMING2__MAIN_H_

#define CACHE_CAPACITY 10

#include <thread>

#include "server_side.h"
#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "MyParallelServer.h"

using namespace std;

class server_side::boot::Main {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }
        int port = stoi(argv[1]);
        Solver<string,string> *solver = new StringReverser();
        CacheManager<string,string> *cache = new FileCacheManager<string,string>(CACHE_CAPACITY);
        ClientHandler *handler = new MyTestClientHandler(solver, cache);
        server_side::Server *mss = new MyParallelServer();
        mss->open(port, handler);
        return 0;
    }
};

#endif //ALGORITHMICPROGRAMMING2__MAIN_H_
