//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_
#define ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_

#define MAX_CHARS 1024
#define END_OF_MESSAGE "end"

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "SearchableBuilder.h"

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

using namespace std;

template<class P, class S>
class MyTestClientHandler : public ClientHandler {
 private:
    Solver<P,S> *my_solver;
    CacheManager<string,string> *my_cache;
    string* readMessageFromClient(int client_socketfd);

 public:
    MyTestClientHandler(Solver<P,S>*,CacheManager<string,string>*);
    void handleClient(int client_socketfd) override;
    MyTestClientHandler* clone() const override;
};

template class MyTestClientHandler<string,string>;
#endif //ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_