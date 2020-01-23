//
// Created by omer on 19/01/2020.
//

#define MAX_CHARS 1024
#define END_OF_MESSAGE "end"
#define NO_SOLUTION "No path (-1)"

#include <netinet/in.h>
#include "MyClientHandler.h"

template<class P>
MyClientHandler<P>::MyClientHandler(Solver<Searchable<P>,list<P>*> *solver, CacheManager<string, string> *cache) {
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
    /*TODO dont forget to delete the backtrace*/

    SearchableBuilder<P> s_builder;
    Searchable<P> *problem;
    list<string> recieved_data, tmp;
    list<P>* solution;
    string cur_line, result, solution_str, problem_key;
    bool sol_in_cache;

    /*Reads all data from client*/
    while (!message_end) {
        tmp = readMessageFromClient(client_socketfd);
        if (tmp.empty() && !message_end) {
            perror("handleClient#1");
            running = false;
            exit(EXIT_FAILURE);
        }

        for(auto msg : tmp) {
            if(!(msg.compare(END_OF_MESSAGE))) {
                break;
            }
            recieved_data.push_back(msg);
        }
        tmp.clear();
    }

    /*Generate problem object and hash it for cache*/
    problem = s_builder.buildMatrix(recieved_data);
    if(problem == nullptr) {
        perror("handleClient#2");
        running = false;
        exit(EXIT_FAILURE); /*TODO debug*/
    }
    problem_key = typeid(problem).name();
    problem_key.append("_");
    problem_key.append(hashProblem(problem));

    getSolMtx.lock();
    sol_in_cache = my_cache->contains(problem_key);
    getSolMtx.unlock();


    if(sol_in_cache) {
        solution_str = my_cache->get(problem_key);
    } else {
        /*Solution NOT IN cache, solve problem and store in cache*/
        solution = my_solver->solve(problem);
        solDescMtx.lock();
        solution_str = solutionDescription(solution);
        solDescMtx.unlock();

        /*Insert to cache*/
        setSolMtx.lock();
        my_cache->insert(problem_key, solution_str);
        setSolMtx.unlock();
    }

    /*Double check its clear, and split solution to chunks*/
    toChunksMtx.lock();
    tmp.clear();
    tmp = toChunks(solution_str);
    toChunksMtx.unlock();

    /*Send each chunk to client*/
    sendMsgMtx.lock();
    for(auto chunk : tmp) {
        if (send(client_socketfd,chunk.c_str(), chunk.size(),MSG_CONFIRM) == -1) {
            perror("handleClient#3");
            return;
        }
    }
    sendMsgMtx.unlock();
    running = false;
    cout<<"client done"<<endl;/*TODO debug*/
}

template <class P>
list<string> MyClientHandler<P>::readMessageFromClient(int client_socketfd) {
    list<string> result;
    regex lineRx("(.*)\\n");
    sregex_iterator start, end = sregex_iterator();
    string buf_str;

    /*Clear to avoid garbage*/
    int bytes_read = 0;
    char buffer[MAX_CHARS] = {'\0'};
    bytes_read = read(client_socketfd, buffer, MAX_CHARS);

    if(strstr(buffer,"end")) {
        message_end = true;
    }

    /*Print error, return empty list*/
    if (bytes_read == -1) {
        perror("readMessageFromClient#1");
        running = false;
        return list<string>();
    } else if (0 < bytes_read) {
        buf_str.append(buffer);
        /*Insert each line (seperated by \n) to messages list*/
        for(start = sregex_iterator(buf_str.begin(),buf_str.end(),lineRx); start != end; ++start ) {
            result.push_back(start->str());
        }
        return result;
    } else {
        return list<string>();
    }
}

template<class P>
MyClientHandler<P>* MyClientHandler<P>::clone() const {
    return new MyClientHandler<P>(my_solver->clone(),my_cache->clone());
}

template<class P>
string MyClientHandler<P>::hashProblem(Searchable<P> *problem) const {
    hash<string> hasher;
    size_t hashed_problem = hasher(problem->str());
    return to_string(hashed_problem);
}

template<class P>
string MyClientHandler<P>::solutionDescription(list<P> *solution) {
    string result, cur_direction, cur_cost;

    if(solution->empty()) {
        return NO_SOLUTION;
    }

    auto cur_element = solution->begin();
    auto next_element = solution->begin();
    ++next_element;

    for(; next_element != solution->end(); ++cur_element, ++next_element) {
        /*Get direction from cur to next.*/
        cur_direction = cur_element->getState().getDirectionToStr(next_element->getState());

        /*Error*/
        if(!cur_direction.compare("Same") || !cur_direction.compare("ERROR")) {
            perror("solutionDescription#1");
            exit(EXIT_FAILURE); /*TODO debug*/
        }
        /*Parse next element's cost to string*/
        try {
            cur_cost = to_string(next_element->getCost());
        } catch (const char* e) {
            perror("SolutionDescription#2");
            perror(e);
            running = false;
            exit(EXIT_FAILURE); /*TODO debug*/
        }
        /*Add all up to the end of result so far*/
        result.append(cur_direction + " (" + cur_cost +"), " );
    }
    return result;
}

template<class P>
list<string> MyClientHandler<P>::toChunks(string solution) {
    int chunk_size = MAX_CHARS;
    list<string> result;
    for(unsigned i = 0; i<solution.size();i+=chunk_size) {
        result.push_back(solution.substr(i, chunk_size));
    }
    return result;
}





