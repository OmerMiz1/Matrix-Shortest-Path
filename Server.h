//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SERVER_H_
#define ALGORITHMICPROGRAMMING2__SERVER_H_
#include "ClientHandler.h"

namespace server_side {
    class Server {
        virtual int open(int port, ClientHandler handler)=0; /* Job: open a server and wait for clients */
        virtual int stop()=0; /* Close the server */
        /*TODO: Do we need any more functions? */
    };
};

#endif //ALGORITHMICPROGRAMMING2__SERVER_H_
