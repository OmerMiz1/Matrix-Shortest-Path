//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYSERIALSERVER_H_
#define ALGORITHMICPROGRAMMING2__MYSERIALSERVER_H_

#include <chrono>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

#include "Server.h"

class MySerialServer : public Server {
 private:
    int sockfd = -1;
    bool done = false;
    sockaddr_in address{};

 public:
    /* NOTE: This class must be generic for all kinds of servers (protocols and such). */
    int open(int, ClientHandler *) override;
    void stop() override;
    void start(int port, ClientHandler *handler);
};

#endif //ALGORITHMICPROGRAMMING2__MYSERIALSERVER_H_
