//
// Created by Omer Mizrachi on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SERVER_H_
#define ALGORITHMICPROGRAMMING2__SERVER_H_

#include "server_side.h"
#include "ClientHandler.h"

/*Interface*/
class server_side::Server {
 public:
    virtual int open(int port, ClientHandler *handler)=0;
    virtual void stop()=0;

    virtual ~Server() = default;
};

#endif //ALGORITHMICPROGRAMMING2__SERVER_H_
