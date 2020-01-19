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

using namespace std;

template<class P, class S>
class MyClientHandler : ClientHandler {
 private:
    Solver<P,S> *solver;
    CacheManager<P,S> *cache;
    list<string> readMessageFromClient;

 public:
    void handleClient(int client_socketfd) override;
};

#endif //ALGORITHMICPROGRAMMING2__MYCLIENTHANDLER_H_
