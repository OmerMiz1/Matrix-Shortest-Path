//
// Created by omer on 15/01/2020.
//

#define MAX_CHARS 1024
#define END_CONNECTION_REQUEST "end"
#define ERROR_READING nullptr

#include "MyTestClientHandler.h"
#include <error.h>

MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solverObj,
                                         CacheManager<string, string> *cacheObj)
    : solver(solverObj), cache(cacheObj) {}
/**
 *
 * @param client_socketfd
 * @return
 */
int MyTestClientHandler::handleClient(int client_socketfd) {
    int bytes_read = 0, result_count=0;
    string *message, result;
    ssize_t sent_status;

    /*Assuming client send 1 message, read it until the end and then handle*/
    while (1) {
        message = readMessageFromClient(client_socketfd);

        if (message == nullptr) {
            perror("handleClient#1");
            return 1;
        }

        /*Client requested to end connection*/
        else if (!message->compare(END_CONNECTION_REQUEST)) {
            cout<<"Closing connection: \"end\" received..."<< endl;
            break;
        }

        /*Solve problem and send to client*/
        result = this->solver->solve(*message);

        if (send(client_socketfd, result.c_str(), result.size(), 0) == -1) {
            perror("handleClient#2");
            return 1;
        }
    }
    return 0;
}

string* MyTestClientHandler::readMessageFromClient(int client_socketfd) {
    /*Clear to avoid garbage*/
    int bytes_read = 0;

    /*TODO: bug- doesnt stop at the right place.
     * i think im supposed to read 1 time and count on them not to bring longer strings than expected.*/
//    do {
    char buffer[MAX_CHARS] = {'\0'};
    bytes_read = read(client_socketfd, buffer, MAX_CHARS);

    /*Print error, return failure value*/
    if (bytes_read == -1) {
        perror("MyTestClientHandler::readMessageFromClient()#1");
        return nullptr;
    } else if (0 < bytes_read /*&& bytes_read < MAX_CHARS*/) {
        return (new string(buffer));
    }
//    cout<<buffer<<endl; /*TODO: for debugging.*/
//    } while (bytes_read != 0); /*0 if end of message reached*/
    perror("MyTestClientHandler::readMessageFromClient()#2");
    return nullptr; /*Also error, shouldnt get here.*/
}
