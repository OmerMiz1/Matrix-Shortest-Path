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
class MyClientHandler : public ClientHandler {
 private:
    Solver<P,S> *my_solver;
    CacheManager<string,string> *my_cache;
    string readMessageFromClient(int client_socketfd);

 public:
    MyClientHandler(Solver<P,S>*,CacheManager<string,string>*);
    void handleClient(int client_socketfd) override;
    MyClientHandler* clone() const override;
};

template class MyClientHandler<Searchable<State<Point>>,list<State<Point>>>;
#endif //ALGORITHMICPROGRAMMING2__MYCLIENTHANDLER_H_
