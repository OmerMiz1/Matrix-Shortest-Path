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
#include "SearchSolver.h"

using namespace std;

class server_side::boot::Main {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }

        int port = stoi(argv[1]);
        auto solver = new SearchSolver<State<Point>>();
        auto cache = new FileCacheManager<string,string>();
        auto handler = new MyClientHandler<State<Point>, list<State<Point>>>(solver,cache);
        auto mps = new MyParallelServer();
        try {
            mps->open(port, handler);
        } catch (const char* e) {
            perror(e);
        }
        return 0;
    }
};

class server_side::boot::SerialStringTester {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }

        int port = stoi(argv[1]);
        auto solver = new StringReverser<string>();
        auto cache = new FileCacheManager<string,string>();
        auto handler = new MyTestClientHandler<string,string>(solver,cache);
        server_side::Server *mss = new MySerialServer();

        try {
            mss->open(port, handler);
        } catch(const char* e) {
            perror(e);
        }
        return 0;
    }
};

class server_side::boot::ParallelStringTester {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }

        int port = stoi(argv[1]);
        auto solver = new StringReverser<string>();
        auto cache = new FileCacheManager<string,string>();
        auto handler = new MyTestClientHandler<string,string>(solver,cache);
        server_side::Server *mps = new MyParallelServer();

        try {
            mps->open(port, handler);
        } catch (const char* e) {
            perror(e);
        }

        return 0;
    }
};
class server_side::boot::SerialMatrixTester {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }

        int port = stoi(argv[1]);
        auto solver = new SearchSolver<State<Point>>();
        auto cache = new FileCacheManager<string,string>();
        auto handler = new MyClientHandler<Searchable<State<Point>>, list<State<Point>>>(solver,cache);
        auto mss = new MySerialServer();
        try {
            mss->open(port, handler);
        } catch (const char* e) {
            perror(e);
        }

        return 0;
    }
};

class server_side::boot::ParallelMatrixTester {
 public:
    int main(int argc, char *argv[]) {
        if(argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }
        int port = stoi(argv[1]);
        auto solver = new SearchSolver<State<Point>>();
        auto cache = new FileCacheManager<string,string>();
        auto handler = new MyClientHandler<Searchable<State<Point>>, list<State<Point>>>(solver,cache);
        auto mps = new MyParallelServer();

        try {
            mps->open(port, handler);
        } catch (const char* e) {
            perror(e);
        }
        return 0;
    }
};
#endif //ALGORITHMICPROGRAMMING2__MAIN_H_