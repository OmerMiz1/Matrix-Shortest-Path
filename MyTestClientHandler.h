//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_
#define ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_

#include "ClientHandler.h"
#include "Solver.h"

using namespace std;

/* This class will be used in the future to test the component\fundamental structure
 * TODO: Figute out if this class sould be genereic with parameter P or P,S */
class MyTestClientHandler : ClientHandler {
 private:
    Solver *solver;

 public:
    MyTestClientHandler(Solver *solver);
};

#endif //ALGORITHMICPROGRAMMING2__MYTESTCLIENTHANDLER_H_
