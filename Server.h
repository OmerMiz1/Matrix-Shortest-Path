//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SERVER_H_
#define ALGORITHMICPROGRAMMING2__SERVER_H_
#include "ClientHandler.h"

/*TODO: splits into 2 files atleast, first name space and the one within?*/
namespace server_side {
    class Server {
     public:
        virtual int open(int port, ClientHandler *handler)=0; /* Job: open a server and wait for clients */
        virtual void stop()=0; /* Close the server */
        /* TODO: Do we need any more functions? */
    };

    namespace boot {
        class Main {
            int main(int argc, char *argv[]) {
                if(argc < 2) {
                    clog<<"Error: not enough arguments..."<<endl;
                    exit(EXIT_FAILURE);
                }
                int port = stoi(argv[0]);
                auto handler = new MyTestClientHandler(new StringReverser());
                auto serialServer = new MySerialServer()
            }
        };
    }
}

#endif //ALGORITHMICPROGRAMMING2__SERVER_H_
