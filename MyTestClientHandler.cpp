//
// Created by omer on 15/01/2020.
//

#define MAX_CHARS 1024
#define END_CONNECTION_REQUEST "end"
#define ERROR_READING nullptr

#include "MyTestClientHandler.h"

MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solverObj,
                                         CacheManager<string, string> *cacheObj)
    : solver(solverObj), cache(cacheObj) {}
/**
 *
 * @param client_socketfd
 * @return
 */
int MyTestClientHandler::handleClient(int client_socketfd) {
    int bytes_read = 0;
    string message, result;
    ssize_t sent_status;

    /*Assuming client send 1 message, read it until the end and then handle*/
    while (1) {

        message.clear();
        message = readMessageFromClient(client_socketfd);

        /*Client requested to end connection*/
        if (!message.compare(END_CONNECTION_REQUEST)) {
            cout << "Closing connection with client, \"end\" received..."
                 << endl;
            break;
        } else if (!message.compare(ERROR_READING)) {
            clog << "Error at MyTestClientHandler::handleClient..." << endl;
            return 1;
        }

        /*Solve problem and send to client*/
        result = this->solver->solve(message);
        if (send(client_socketfd, result.c_str(), result.size(), 0) == -1) {
            clog << "Error sending result to client..." << endl;
            return 1;
        }

    }
    return 0;
}

string MyTestClientHandler::readMessageFromClient(int client_socketfd) {
    /*Clear to avoid garbage*/
    int bytes_read = 0;
    string buf_str;
    buf_str.clear();

    do {
        char buffer[MAX_CHARS] = {'\0'};
        bytes_read = read(client_socketfd, buffer, MAX_CHARS);
        /*Print error, return failure value*/
        if (bytes_read == -1) {
            clog << "Error reading from client, client_socketfd = ";
            clog << client_socketfd << endl;
            return ERROR_READING;
        } else if (0 < bytes_read && bytes_read < MAX_CHARS) {
            buf_str.append(buffer);
        }
    } while (bytes_read != 0); /*0 if end of message reached*/
    return buf_str;
}
