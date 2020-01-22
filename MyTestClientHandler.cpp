//
// Created by omer on 15/01/2020.
//

#define MAX_CHARS 1024
#define END_OF_MESSAGE "end"

#include "MyTestClientHandler.h"


template<class P, class S>
MyTestClientHandler<P, S>::MyTestClientHandler(Solver<P, S> *solver,
                                               CacheManager<string, string> * cache): my_solver(solver),my_cache(cache) {}

/**
 *
 * @param client_socketfd
 * @return
 */
template<class P, class S>
void MyTestClientHandler<P,S>::handleClient(int client_socketfd) {
    string *message, result;
    /*Assuming client send 1 message, read it until the end and then handle*/
    while (1) {
        message = readMessageFromClient(client_socketfd);
        if (message == nullptr) {
            perror("handleClient#1");
            return;
        }
        /*Client requested to end connection*/
        else if (!message->compare(END_OF_MESSAGE)) {
            break;
        }

        /*Solve problem and send to client*/
        result = my_solver->solve(message);
        if (send(client_socketfd, result.c_str(), result.size(), 0) == -1) {
            perror("handleClient#2");
            return;
        }
    }
    close(client_socketfd);
}

template<class P, class S>
string* MyTestClientHandler<P,S>::readMessageFromClient(int client_socketfd) {
    /*Clear to avoid garbage*/
    int bytes_read = 0;

    /*TODO: bug- doesnt stop at the right place.
     * i think im supposed to read 1 time and count on them not to bring longer strings than expected.*/

    char buffer[MAX_CHARS] = {'\0'};
    bytes_read = read(client_socketfd, buffer, MAX_CHARS);

    /*Print error, return failure value*/
    if (bytes_read == -1) {
        perror("readMessageFromClient#1");
        return nullptr;
    } else if (0 < bytes_read /*&& bytes_read < MAX_CHARS*/) {
        return (new string(buffer));
    }
    //cout<<buffer<<endl; /*TODO: for debugging.*/

    /*Also error, shouldnt get here.*/
    perror("readMessageFromClient#2");
    return nullptr;
}

template<class P, class S>
MyTestClientHandler<P,S> *MyTestClientHandler<P, S>::clone() const {
    return new MyTestClientHandler<P,S>(my_solver->clone(),my_cache->clone());
}


