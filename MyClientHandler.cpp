//
// Created by omer on 19/01/2020.
//

#define MAX_CHARS 1024
#define END_OF_MESSAGE "end"

#include "MyClientHandler.h"

template<class P>
MyClientHandler<P>::MyClientHandler(Solver<Searchable<P>,list<P>> *solver, CacheManager<string, string> *cache) {
    this->my_solver = move(solver);
    this->my_cache = move(cache);
}

template<class P>
MyClientHandler<P>::MyClientHandler(SearchSolver<P> *solver,
                                    CacheManager<string, string> *cache) {
    this->my_solver = move(solver);
    this->my_cache = move(cache);
}

/** Returns a list of strings from first line received from client until line
 * says "end". The list DOESNT INCLUDE "end"!
 *
 * @tparam P
 * @tparam S
 * @param client_socketfd
 */
template <class P>
void MyClientHandler<P>::handleClient(int client_socketfd) {
    list<string> recieved_data;
    list<P> solution;
    string cur_line,result;


    /*Reads all data from client*/
    while (1) {
        cur_line = readMessageFromClient(client_socketfd);
        if (cur_line.empty()) {
            perror("handleClient#1");
            return;
        }

        /*Reached end of message token*/
        else if (!(cur_line.compare(END_OF_MESSAGE))) {
            break;
        }
        recieved_data.push_back(cur_line);
    }

    SearchableBuilder<P> s_builder;
    auto problem = s_builder.buildMatrix(recieved_data);
    hash<string> hasher;
    auto hashed_problem = hasher(problem->toString());
    string problem_key = to_string(hashed_problem);

    if(!(my_cache->contains(problem_key))) {
        solution = my_solver->solve(problem);
        my_cache->insert(problem_key,solution);
    } else {
        solution = my_cache->get(problem_key);
    }

    /*TODO: print solution (S should be printable)*/

    if (send(client_socketfd, result.c_str(), result.size(), 0) == -1) {
        perror("handleClient#2");
        return;
    }
}

template <class P>
string MyClientHandler<P>::readMessageFromClient(int client_socketfd) {
    /*TODO: bug- doesnt stop at the right place. I think im supposed to read 1
     * time and count on them not to bring longer strings than expected.
     * If doesnt work, consider using the same "buffering" method used in EX3
     * at OpenServerCommand::startListening*/

    /*Clear to avoid garbage*/
    int bytes_read = 0;
    char buffer[MAX_CHARS] = {'\0'};
    bytes_read = read(client_socketfd, buffer, MAX_CHARS);

    /*Print error, return empty list*/
    if (bytes_read == -1) {
        perror("readMessageFromClient#1");
        return "";
        /*TODO remove below condition before submitting.*/
    } else if (0 < bytes_read /*&& bytes_read < MAX_CHARS*/) {
        return string(buffer);
    }

    //cout<<buffer<<endl; /*TODO: for debugging.*/

    /*Also error, shouldnt get here.*/
    perror("readMessageFromClient#2");
    return "";
}

template<class P>
MyClientHandler<P>* MyClientHandler<P>::clone() const {
    return new MyClientHandler<P>(my_solver->clone(),my_cache->clone());
}





