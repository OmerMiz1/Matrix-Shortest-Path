//
// Created by omer on 19/01/2020.
//

#define MAX_CHARS 1024
#define END_CONNECTION_REQUEST "end"
#define ERROR_READING nullptr

#include "MyClientHandler.h"
#include "SearcheableBuilder.h"

template <class P, class S>
void MyClientHandler<P,S>::handleClient(int client_socketfd) {
    int bytes_read = 0, result_count=0;
    string *message, result;
    ssize_t sent_status;

    while (1) {
        message = readMessageFromClient(client_socketfd);
        if (message == nullptr) {
            perror("handleClient#1");
            return;
        }
        /*Client requested to end connection*/
        else if (!message->compare(END_CONNECTION_REQUEST)) {
            break;
        }
        if (send(client_socketfd, result.c_str(), result.size(), 0) == -1) {
            perror("handleClient#2");
            return;
        }
    }

    auto s_builder = new SearcheableBuilder<P,S>();
    Searchable<P> problem = s_builder->buildMatrix();
    list<Searchable<P>> solution = this->solver.solve(problem);

}

template <class P, class S>
list<string> MyClientHandler<P,S>::readMessageFromClient(int client_socketfd) {
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
