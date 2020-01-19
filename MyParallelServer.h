//
// Created by omer on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__MYPARALLELSERVER_H_
#define ALGORITHMICPROGRAMMING2__MYPARALLELSERVER_H_

#include <chrono>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <list>
#include <mutex>

#include "Server.h"

 class MyParallelServer : public server_side::Server{
 private:
    int sockfd = -1;
    bool done = false;
    sockaddr_in address{};
    list<thread> threads;

 public:
    int open(int port, ClientHandler *handler) override;
    void stop() override;
    void start(int port, ClientHandler* handler);
    void joinAllThreads();
};

#endif //ALGORITHMICPROGRAMMING2__MYPARALLELSERVER_H_
