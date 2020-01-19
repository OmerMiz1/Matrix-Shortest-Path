//
// Created by omer on 17/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SERVER_H_
#define ALGORITHMICPROGRAMMING2__SERVER_H_

#include "server_side.h"
#include "ClientHandler.h"

/*Interface*/
class server_side::Server {
 public:
    virtual int open(int port, ClientHandler *handler)=0; /* Job: open a server and wait for clients */
    virtual void stop()=0; /* Close the server */
    /* TODO: Do we need any more functions? */
};

#endif //ALGORITHMICPROGRAMMING2__SERVER_H_
