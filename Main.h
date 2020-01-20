//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MAIN_H_
#define ALGORITHMICPROGRAMMING2__MAIN_H_

#define CACHE_CAPACITY 10

#include <thread>
#include <list>

#include "server_side.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "FileCacheManager.h"
#include "StringReverser.h"
#include "MatrixShortestPaths.h"

using namespace std;

class server_side::boot::Main {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }
        int port = stoi(argv[1]);
        auto solver = new MatrixShortestPaths<State<Point>, list<State<Point>>>;
        auto cache = new FileCacheManager    <State<Point>, list<State<Point>>>(CACHE_CAPACITY);
        auto handler = new MyClientHandler   <State<Point>, list<State<Point>>>(solver, cache);
        server_side::Server *mss = new MyParallelServer();
        mss->open(port, handler);
        return 0;
    }
};

class server_side::boot::SerialTester {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }
        int port = stoi(argv[1]);
        auto solver = new StringReverser<string,string>();
        auto cache = new FileCacheManager<string,string>(CACHE_CAPACITY);
        auto handler = new MyTestClientHandler<string,string>(solver, cache);
        server_side::Server *mss = new MySerialServer();
        mss->open(port, handler);
        return 0;
    }
};

class server_side::boot::ParallelTester {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }
        int port = stoi(argv[1]);
        auto solver = new StringReverser<string,string>();
        auto cache = new FileCacheManager<string,string>(CACHE_CAPACITY);
        auto handler = new MyTestClientHandler<string,string>(solver, cache);
        server_side::Server *mss = new MyParallelServer();
        mss->open(port, handler);
        return 0;
    }
};



#endif //ALGORITHMICPROGRAMMING2__MAIN_H_
