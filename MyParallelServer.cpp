//
// Created by Omer Mizrachi on 18/01/2020.
//

#include "MyParallelServer.h"


MyParallelServer::~MyParallelServer() {
    for(auto handler : *handlers) {
        if(handler != nullptr) {
            delete handler;
        }
    }
    delete handlers;
    delete threads;
}

/** Opened server starts listening until stop() is called or error.

 * @param port to be bind onto.
 * @param handler in-charge of handling the client requests.
 * @return 0 success, negative value o.w (might also terminate the program).
 */
int MyParallelServer::open(int port, ClientHandler *handler) {
    struct timeval tv{};
    fd_set fdset;

    /*OPEN SOCKET*/
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)  {
        perror("parallel_open#1");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);

    /*TODO: for debugging*/
    /*Force attach to given port*/
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    /*SET TIMEOUT*/
    tv.tv_sec = TIME_OUT_SECONDS;
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv) != 0) {
        perror("parallel_open#2");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; /* address is in IPv4*/
    address.sin_addr.s_addr = INADDR_ANY; /* give me any ip alloc'd for machine*/
    address.sin_port = htons(port); /* more info tirgul 6 page 32*/

    /*BIND*/
    if (::bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("parallel_open#3");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    /*LISTEN*/
    if (listen(sockfd, MAX_CLIENTS) == -1) {
        perror("parallel_open#4");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    /*Start infinite loop that handles clients.*/
    start(handler);

    return 0;
}

void MyParallelServer::stop() {
    this->done = true;
}

/** Starts listening to port and accepting clients.
 * Each client will be handled in its own thread.
 *
 * @param port listening port.
 * @param handler injected handler to be used.
 */
void MyParallelServer::start(ClientHandler *handler) {
    socklen_t addr_len;

    /*Accepts clients one-by-one until done*/
    while(!done) {
        /*Reset values every iteration*/
        int client_socket = 0;
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);
        struct timeval tv{};

        /*SET TIMEOUT*/
        tv.tv_sec = TIME_OUT_SECONDS;

        /*SELECT FROM QUEUE*/
        int select_status = select(this->sockfd+1, &fdset, nullptr, nullptr, &tv);
        if (select_status <= 0) {
            cout<<("Server timed-out...")<<endl;
            this->done = true;
            break;
        }

        /*ACCEPT*/
        if(FD_ISSET(sockfd, &fdset)) {
            addr_len = sizeof(address);
            client_socket = accept(sockfd,(struct sockaddr*) &address,&addr_len);
            if (client_socket == -1) {
                this->done = true;
                perror("parallel_start#2");
                return;
            }

            /*Call handler in a new thread*/
            ClientHandler *cloned = handler->clone();
            handlers->push_back(cloned);
            threads->push_back(thread(&ClientHandler::handleClient, &(*cloned), std::ref(client_socket)));

            /*Make this thread sleep so new handler can read and not get blocked by select()*/
            this_thread::sleep_for(200ms);
        }
    } // End of while, server is done listening.

    /*Join threads and close socket*/
    joinAllThreads();
    if(close(sockfd)==-1) {
        perror("parallel_start#3");
        return;
    }
    cout<<"Server closed successfully..."<<endl;
}

/**
 * Joins all threads before closing server.
 */
void MyParallelServer::joinAllThreads() {
    cout<<"Joining all running threads..."<<endl;
    for(auto& t : *this->threads) {
        if( t.joinable()) {
            t.join();
        }
    }
}


