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
        SearchSolver<State<Point>> *solver{};
        FileCacheManager <State<Point>, list<State<Point>>> *cache{};
        MyClientHandler<Searchable<State<Point>>, list<State<Point>>>* handler;;
        MyParallelServer mps;
        try {
            mps.open(port, handler);
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
        auto solver = new StringReverser<string,string>();
        auto cache = new FileCacheManager<string,string>(CACHE_CAPACITY);
        auto handler = new MyTestClientHandler<string,string>(solver, cache);
        server_side::Server *mss = new MySerialServer();
        mss->open(port, handler);
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
        auto solver = new StringReverser<string,string>();
        auto cache = new FileCacheManager<string,string>(CACHE_CAPACITY);
        auto handler = new MyTestClientHandler<string,string>(solver, cache);
        server_side::Server *mps = new MyParallelServer();
        mps->open(port, handler);
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
        SearchSolver<State<Point>> *solver{};
        FileCacheManager <State<Point>, list<State<Point>>> *cache{};
        MyClientHandler<Searchable<State<Point>>, list<State<Point>>>* handler;;
        MySerialServer mss;
        try {
            mss.open(port, handler);
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
        SearchSolver<State<Point>> *solver{};
        FileCacheManager <State<Point>, list<State<Point>>> *cache{};
        MyClientHandler<Searchable<State<Point>>, list<State<Point>>>* handler;;
        MyParallelServer mps;
        try {
            mps.open(port, handler);
        } catch (const char* e) {
            perror(e);
        }
        return 0;
    }
};



#endif //ALGORITHMICPROGRAMMING2__MAIN_H_
