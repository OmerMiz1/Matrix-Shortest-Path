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
#include <vector>

#include "Server.h"
using namespace std;
using namespace server_side;

class MyParallelServer : public server_side::Server{
 private:
    int sockfd = -1;
    bool done = false;
    sockaddr_in address{};
    vector<ClientHandler*> handlers;
    vector<thread> threads;
    void joinAllThreads();
    void start(ClientHandler* handler);

 public:
    int open(int port, ClientHandler *handler) override;
    void stop() override;
};
#endif //ALGORITHMICPROGRAMMING2__MYPARALLELSERVER_H_
