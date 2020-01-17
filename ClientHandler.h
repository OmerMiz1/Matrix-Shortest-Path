//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__CLIENTHANDLER_H_
#define ALGORITHMICPROGRAMMING2__CLIENTHANDLER_H_

using namespace std;

class ClientHandler {
 public:
    virtual int handleClient(int client_socketfd)=0; /* Not sure about the return value */
};

#endif //ALGORITHMICPROGRAMMING2__CLIENTHANDLER_H_
