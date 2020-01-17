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

    /*OPEN SOCKET*/
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)  {
        clog<<"Could not create a socket."<<endl;
        this->done = true;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; /* address is in IPv4*/
    address.sin_addr.s_addr = INADDR_ANY; /* give me any ip alloc'd for machine*/
    address.sin_port = htons(port); /* more info tirgul 6 page 32*/

    /*BIND*/
    if (::bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        clog<<"Could not bind the socket to an IP"<<endl;
        this->done = true;
        exit(EXIT_FAILURE);
    }

    /*LISTEN*/
    if (listen(sockfd, MAX_CLIENTS) == -1) {
        clog<<"Error listening to to port"<<endl;
        this->done = true;
        exit(EXIT_FAILURE);
    }

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

    /*Accepts clients one-by-one until done*/
    while(!done) {
        /*Reset values every iteration*/
        int exit_status = 0, client_socket = 0;
        struct timeval tv{};
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);

        /*SET TIMEOUT*/
        /*TODO not completely sure about this...
         * if not here, its supposed to be also in open() function*/
        tv.tv_sec = TIME_OUT_SECONDS;
        if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv) != 0) {
            clog<<"Error setting socket timeout..."<<endl;
            this->done = true;
            exit(EXIT_FAILURE);
        }

        /*SELECT FROM QUEUE*/
        int select_status = select(this->sockfd+1, &fdset, nullptr, nullptr, &tv);
        if (select_status <= 0) {
            clog<<"Error selecting client..."<<endl;
            this->done = true;
            return;
        }

        /*ACCEPT*/
        client_socket = accept(sockfd,(struct sockaddr *) &address,(socklen_t *) &address);
        if (client_socket == -1) {
                clog<<"Error accepting simulator"<<endl;
                this->done = true;
                return;
            }

        /*Mainly used for visualizing whats going on*/
        ++accepted_count;
        printf("Server: client #%d accepted\n", accepted_count);

        /*If handler had error, just print to clog and proceed*/
        exit_status = handler->handleClient(client_socket);
        if(exit_status < 0) {
            clog<<"Error: handling client encountered a problem..."<<endl;
            clog<<"Port = ";
            clog<<port<<endl;
        }
    }
}

void MySerialServer::stop() {
    this->done = true;
}

/*TODO: remove before submission
* void MySerialServer::open(int port, ClientHandler *client_handler) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    thread t(start, server_fd, address, client_handler, &to_stop);
    t.join();
}

void MySerialServer::start(int socketfd, sockaddr_in address, ClientHandler *client_handler, bool *to_stop) {
    while (!(*to_stop)) {
        int iResult;
        int client_socket = 0;
        struct timeval tv;
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(socketfd, &rfds);

        tv.tv_sec = 120.0;
        tv.tv_usec = 0;
        int addrlen = sizeof(address);
        iResult = select(socketfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);
        if (iResult > 0) {
            client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
        } else {
            cout << "timeout, server shut down." << endl;
            return;
        }
        if (client_socket == -1) {
            std::cerr << "can't accept client" << std::endl;
            return;
        }
        client_handler->handleClient(client_socket);
    }
}*/
