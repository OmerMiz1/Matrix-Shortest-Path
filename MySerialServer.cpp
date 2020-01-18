//
// Created by omer on 15/01/2020.
//
#define MAX_CLIENTS 20
#define TIME_OUT_SECONDS 120


#include "MySerialServer.h"


/** Opened server starts listening until stop() is called or error.
 *
 * ----------------------Instructions-------------------------------
 * 1. create a new thread with the proper arguments.
 * 2. call join()
 * -----------------------------------------------------------------
 * @param port to be bind onto.
 * @param handler in-charge of handling the client requests.
 * @return 0 success, negative value o.w (might also terminate the program).
 */
int MySerialServer::open(int port, ClientHandler *handler) {
    struct timeval tv{};
    fd_set fdset;

    /*OPEN SOCKET*/
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)  {
        perror("open#1");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);

    /*// Forcefully attaching socket to the port 8080
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }*/

    /*SET TIMEOUT*/
    tv.tv_sec = TIME_OUT_SECONDS;
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv) != 0) {
        perror("open#2");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; /* address is in IPv4*/
    address.sin_addr.s_addr = INADDR_ANY; /* give me any ip alloc'd for machine*/
    address.sin_port = htons(port); /* more info tirgul 6 page 32*/

    /*BIND*/
    if (::bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("open#3");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    /*LISTEN*/
    if (listen(sockfd, MAX_CLIENTS) == -1) {
        perror("open#4");
        this->done = true;
        exit(EXIT_FAILURE);
    }

    /*Start infinite loop that handles clients.*/
    start(port, handler);

    /*Clean exit, open ran successfully*/
    close(sockfd);
    return 0;
}

/** Starts handling clients one-by-one until stop() is called or error reached.
 *
 * @param port server is assigned to
 * @param handler ClientHandler object
 * @param tv time value struct used for managing timeouts.
 */
void MySerialServer::start(int port, ClientHandler *handler) {
    int accepted_count = 0;
    socklen_t addr_len;

    /*Accepts clients one-by-one until done*/
    while(!done) {
        /*Reset values every iteration*/
        int exit_status = 0, client_socket = 0;
        struct timeval tv{};
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);

        /*SET TIMEOUT*/
        tv.tv_sec = TIME_OUT_SECONDS;

        /*SELECT FROM QUEUE*/
        int select_status = select(this->sockfd+1, &fdset, nullptr, nullptr, &tv);
        if (select_status <= 0) {
            perror("server_start#1");
            this->done = true;
            return;
        }

        /*ACCEPT*/
        if(FD_ISSET(sockfd, &fdset)) {
            addr_len = sizeof(address);
            client_socket = accept(sockfd,(struct sockaddr*) &address,&addr_len);
            if (client_socket == -1) {
                this->done = true;
                perror("server_start#2");
                return;
            }
        }

        /*Mainly used for visualizing whats going on*/
        ++accepted_count; /*TODO: debug*/
        cout<<"Server: client #" <<accepted_count<<" accepted..."<<endl;

        /*If handler had error, just print error. mainly for debug.*/
        exit_status = handler->handleClient(client_socket);
        if(exit_status < 0) {
            perror("server_start#3");
        }
    }
}

void MySerialServer::stop() {
    this->done = true;
}

/*TODO: debug*/