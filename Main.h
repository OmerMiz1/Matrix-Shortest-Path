//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MAIN_H_
#define ALGORITHMICPROGRAMMING2__MAIN_H_

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

/**
* Main to boot server from.
*/
class server_side::boot::Main {
public:
    int main(int argc, char *argv[]) {
        if (argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }
        int port;
        try {
             port = stoi(argv[1]);
        } catch(const char* e) {
            perror(e);
            exit(EXIT_FAILURE);
        }

        /*Initialize Searchers and everything...
         *Chose AStar as Roi said in piazza to choose it anyway. */
        Searcher<State<Point>> *searcher = new BestFS<State<Point>>(); /*Searcher Type*/
        SearchSolver<State<Point>> *solver = new SearchSolver<State<Point>>(searcher);/*Solver Type*/
        CacheManager<string, string> *cache = new FileCacheManager();
        auto handler = new MyClientHandler<State<Point>>(solver, cache);
        auto mps = new MyParallelServer();

        /*Open Serer Wth Matrix Solver And AStar Searcher*/
        try {
            mps->open(port, handler);
        } catch (const char *e) {
            perror(e);
        }

        delete searcher;
        delete solver;
        delete cache;
        delete handler;
        delete mps;

        return 0;
    }
};

class server_side::boot::SerialStringTester {
public:
    int main(int argc, char *argv[]) {
        if (argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }

        int port = stoi(argv[1]);
        Solver<string, string> *solver = new StringReverser<string>();
        auto cache = new FileCacheManager();
        auto handler = new MyTestClientHandler<string, string>(solver, cache);
        server_side::Server *mss = new MySerialServer();

        try {
            mss->open(port, handler);
        } catch (const char *e) {
            perror(e);
        }
        return 0;
    }
};

class server_side::boot::ParallelStringTester {
public:
    int main(int argc, char *argv[]) {
        if (argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }

        int port = stoi(argv[1]);
        Solver<string, string> *solver = new StringReverser<string>();
        auto cache = new FileCacheManager();
        auto handler = new MyTestClientHandler<string, string>(solver, cache);
        server_side::Server *mps = new MyParallelServer();

        try {
            mps->open(port, handler);
        } catch (const char *e) {
            perror(e);
        }

        return 0;
    }
};

class server_side::boot::SerialMatrixTester {
public:
    int main(int argc, char *argv[]) {
        if (argc < 2) {
            perror("main");
            exit(EXIT_FAILURE);
        }

        int port = stoi(argv[1]);
        auto *searcher = new AStar<State<Point>>();
        auto *solver =   new SearchSolver<State<Point>>(searcher);
        auto cache =     new FileCacheManager();
        auto handler =   new MyClientHandler<State<Point>>(solver, cache);
        auto mss =       new MySerialServer();

        try {
            mss->open(port, handler);
        } catch (const char *e) {
            perror(e);
        }

        return 0;
    }
};

/**
 * Mainly for easier testing.
 */
class server_side::boot::ParallelMatrixTester {
public:
    int main(int argc, char *argv[]) {
        int port = stoi(argv[1]);
        Searcher<State<Point>>* sDFS = new DFS<State<Point>>();
        Searcher<State<Point>>* sBFS = new BFS<State<Point>>();
        Searcher<State<Point>>* sAStar = new AStar<State<Point>>();
        Searcher<State<Point>>* sBestFS = new BestFS<State<Point>>();
        SearchSolver<State<Point>> *DFS_solver = new SearchSolver<State<Point>>(sDFS);
        SearchSolver<State<Point>> *BFS_solver = new SearchSolver<State<Point>>(sBFS);
        SearchSolver<State<Point>> *AStar_solver = new SearchSolver<State<Point>>(sAStar);
        SearchSolver<State<Point>> *BestFS_solver = new SearchSolver<State<Point>>(sBestFS);
        auto cache = new FileCacheManager();
        auto DFS_handler = new MyClientHandler<State<Point>>(DFS_solver, cache);
        auto BFS_handler = new MyClientHandler<State<Point>>(BFS_solver, cache);
        auto AStar_handler = new MyClientHandler<State<Point>>(AStar_solver, cache);
        auto BestFS_handler = new MyClientHandler<State<Point>>(BestFS_solver, cache);
        auto DFS_server = new MyParallelServer();
        auto BFS_server = new MyParallelServer();
        auto AStar_server = new MyParallelServer();
        auto BestFS_server = new MyParallelServer();

        try {
            thread DFS_th(&MyParallelServer::open, DFS_server, 8080, DFS_handler);
            thread BFS_th(&MyParallelServer::open, BFS_server, 8081, BFS_handler);
            thread AStar_th(&MyParallelServer::open, AStar_server, 8082, AStar_handler);
            thread BestFS_th(&MyParallelServer::open, BestFS_server, 8083, BestFS_handler);

            DFS_th.join();
            BFS_th.join();
            AStar_th.join();
            BestFS_th.join();
        } catch (const char *e) {
            perror(e);
        }
        return 0;
    }
};

#endif //ALGORITHMICPROGRAMMING2__MAIN_H_