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

#include "CacheManager.h"
#include "FileCacheManager.h"
#include "ClientHandler.h"
#include "Solver.h"
#include "Searchable.h"
#include "SearchableBuilder.h"
#include "SearchSolver.h"

using namespace std;

template<class P>
class MyClientHandler : public ClientHandler {
 private:
    Solver<Searchable<P>,list<P>> *my_solver;
    CacheManager<string,string> *my_cache;
    string readMessageFromClient(int client_socketfd);

 public:
    MyClientHandler(Solver<Searchable<P>,list<P>> *solver,CacheManager<string,string> *cache);
    MyClientHandler(SearchSolver<P> *solver,CacheManager<string,string> *cache);
    void handleClient(int client_socketfd) override;
    MyClientHandler* clone() const override;
};

/*TODO: NO IDEA WHY IT IS SO IMPORTANT DECLARATION IS IN THIS ORDER*/
template class MyClientHandler<State<Point>>;
template class MyClientHandler<SearchSolver<State<Point>>>;
template class MyClientHandler<Searchable<State<Point>>>;
#endif //ALGORITHMICPROGRAMMING2__MYCLIENTHANDLER_H_
