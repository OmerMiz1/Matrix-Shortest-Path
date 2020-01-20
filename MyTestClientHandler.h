//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_
#define ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "SearchableBuilder.h"

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

using namespace std;

/* This class will be used in the future to test the component\fundamental structure
 * TODO: Figure out if this class should be generic with parameter P or P,S */
template<class P, class S>
class MyTestClientHandler : public ClientHandler<P,S> {
 private:
    Solver<P,S> *solver;
    CacheManager<P,S> *cache;
    string* readMessageFromClient(int client_socketfd);

 public:
    MyTestClientHandler(Solver<P,S>*, CacheManager<P,S>*);
    void handleClient(int client_socketfd) override;
    ClientHandler<P,S> clone() const override;
};

#endif //ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_
