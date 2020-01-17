//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_
#define ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

using namespace std;

/* This class will be used in the future to test the component\fundamental structure
 * TODO: Figure out if this class should be generic with parameter P or P,S */
class MyTestClientHandler : public ClientHandler {
 private:
    /*Data members*/
    Solver<string,string> *solver;
    CacheManager<string,string> *cache;

    /*Helper functions*/
    string readMessageFromClient(int client_socketfd);

 public:
    MyTestClientHandler(Solver<string,string>*, CacheManager<string,string>*);
    int handleClient(int client_socketfd) override;
};

#endif //ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_
