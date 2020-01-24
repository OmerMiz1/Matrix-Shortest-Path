//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYSERIALSERVER_H_
#define ALGORITHMICPROGRAMMING2__MYSERIALSERVER_H_

#define MAX_CLIENTS 10
#define TIME_OUT_SECONDS 120

#include <chrono>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

#include "Server.h"
using namespace std;
using namespace server_side;
 class MySerialServer : public server_side::Server {
 private:
    int sockfd = -1;
    bool done = false;
    sockaddr_in address{};

 public:
    /* NOTE: This class must be generic for all kinds of servers (protocols and such). */
    int open(int, ClientHandler *) override;
    void stop() override;
    void start(ClientHandler *handler);
};

#endif //ALGORITHMICPROGRAMMING2__MYSERIALSERVER_H_
