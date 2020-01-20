//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__CLIENTHANDLER_H_
#define ALGORITHMICPROGRAMMING2__CLIENTHANDLER_H_

#include "Cloneable.h"

/*Interface*/

class ClientHandler : virtual Cloneable<ClientHandler> {
 public:
    virtual void handleClient(int client_socketfd)=0;
};

#endif //ALGORITHMICPROGRAMMING2__CLIENTHANDLER_H_