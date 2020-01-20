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

#include "CacheManager.h"
#include "ClientHandler.h"
#include "Solver.h"
#include "Searchable.h"
#include "SearchableBuilder.h"

using namespace std;

template<class P, class S>
class MyClientHandler : ClientHandler {
 private:
    Solver<P,S> *my_solver;
    CacheManager<P,S> *my_cache;
    string readMessageFromClient(int client_socketfd);

 public:
    MyClientHandler(Solver<P,S> solver, CacheManager<P,S> cache);
    void handleClient(int client_socketfd) override;
    ClientHandler clone() const override;
};

#endif //ALGORITHMICPROGRAMMING2__MYCLIENTHANDLER_H_
