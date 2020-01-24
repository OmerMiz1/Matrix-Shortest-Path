//
// Created by omer on 19/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYCLIENTHANDLER_H_
#define ALGORITHMICPROGRAMMING2__MYCLIENTHANDLER_H_

#include <list>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <utility>
#include <mutex>

#include "CacheManager.h"
#include "FileCacheManager.h"
#include "ClientHandler.h"
#include "Point.h"
#include "Solver.h"
#include "Searchable.h"
#include "SearchableBuilder.h"
#include "SearchSolver.h"

using namespace std;

template<class P>
class MyClientHandler : public ClientHandler {
 private:
    mutex getSolMtx, setSolMtx, toChunksMtx, sendMsgMtx, solDescMtx, probBuildMtx, keyGenMtx;
    Solver<Searchable<P>,list<P>*> *my_solver;
    CacheManager<string,string> *my_cache;
    list<string> readMessageFromClient(int client_socketfd);
    string hashProblem(Searchable<P> *problem) const;
    string solutionDescription(list<P> *solution);
    bool message_end = false;

 public:
    MyClientHandler(Solver<Searchable<P>,list<P>*> *solver,CacheManager<string,string> *cache);
    MyClientHandler(SearchSolver<P> *solver,CacheManager<string,string> *cache);
    void handleClient(int client_socketfd) override;

    MyClientHandler* clone() const override;
    list<string> toChunks(string basic_string);
};

template class MyClientHandler<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2__MYCLIENTHANDLER_H_
