//
// Created by omer on 19/01/2020.
//

#define MAX_CHARS 1024
#define END_OF_MESSAGE "end"
#define NO_SOLUTION "No path (-1)"
#define NO_MOVES_MADE "No Moves (0)"

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

template<class P>
MyClientHandler<P>::~MyClientHandler() {
    delete my_solver;
    delete my_cache;
}

/** Handler for TCP clients with matrix paths problems.
 *
 * @tparam State<Point>
 * @param client_socketfd to handle.
 */
template <class P>
void MyClientHandler<P>::handleClient(int client_socketfd) {
    SearchableBuilder<P> s_builder;
    Searchable<P> *problem;
    list<string> recieved_data, tmp;
    list<P>* solution;
    string cur_line, result;
    auto problem_key = new string();
    auto solution_str = new string();
    bool sol_in_cache;

    /*Reads all data from client*/
    recvMsgMtx.lock();
    while (!message_end) {
        tmp = readMessageFromClient(client_socketfd);
        if (tmp.empty() && !message_end) {
            perror("handleClient#1");
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
    recvMsgMtx.unlock();

    /*Generate problem*/
    probBuildMtx.lock();
    problem = s_builder.buildMatrix(recieved_data);
    probBuildMtx.unlock();

    /*Error*/
    if(problem == nullptr) {
        perror("handleClient#2");
        return;
    }

    /*Generate problem key for cache*/
    keyGenMtx.lock();
    problem_key->append(typeid(problem).name());
    problem_key->append("_");
    problem_key->append(hashProblem(problem));
    keyGenMtx.unlock();

    getSolMtx.lock();
    sol_in_cache = my_cache->contains(problem_key);
    getSolMtx.unlock();

    if(sol_in_cache) {
        getSolMtx.lock();
        solution_str = my_cache->get(problem_key);
        getSolMtx.unlock();
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

    /*Send each chunk to client*/
    sendMsgMtx.lock();
    tmp.clear();
    tmp = toChunks(solution_str);

    for(auto chunk : tmp) {
        if (send(client_socketfd,chunk.c_str(), chunk.size(), MSG_CONFIRM) == -1) {
            perror("handleClient#3");
            return;
        }
    }
    sendMsgMtx.unlock();
    delete problem;
}

/**
 * Reads the message (problem) from client.
 * @tparam P
 * @param client_socketfd
 * @return
 */
template <class P>
list<string> MyClientHandler<P>::readMessageFromClient(int client_socketfd) {
    list<string> result;
    regex lineRx("(.*)\\n");
    sregex_iterator start, end = sregex_iterator();
    string buf_str;

    /*Clear to avoid garbage*/
    int bytes_read = 0;
    char buffer[MAX_CHARS] = {0};
    bytes_read = read(client_socketfd, buffer, MAX_CHARS-1);

    /*Check if end of message reached*/
    if(strstr(buffer,"end")) {
        message_end = true;
    }

    /*Print error, return empty list*/
    if (bytes_read == -1) {
        perror("readMessageFromClient#1");
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

/** Hash Searchable<P> problem.
 *
 * @tparam P
 * @param problem
 * @return
 */
template<class P>
string MyClientHandler<P>::hashProblem(Searchable<P> *problem) const {
    hash<string> hasher;
    size_t hashed_problem = hasher(problem->str());
    return to_string(hashed_problem);
}

/**
 * Generate string description for solution (directions and cost at each step).
 */
template<class P>
string* MyClientHandler<P>::solutionDescription(list<P> *solution) {
    string *result = new string(), cur_direction, cur_cost;

    /*solution is empty if there is NO SOLUTION*/
    if(solution->empty()) {
        result->append(NO_SOLUTION);
        return result;
    } else if (solution->size() == 1) {
        result->append(NO_MOVES_MADE);
        return result;
    }

    auto cur_element = solution->begin();
    auto next_element = solution->begin();
    ++next_element;

    for(; next_element != solution->end(); ++cur_element, ++next_element) {
        /*Get direction from cur to next.*/
        cur_direction = cur_element->getState().getDirectionToStr(next_element->getState());
        /*Error*/
        if (!cur_direction.compare("Same") || !cur_direction.compare("ERROR")) {
            perror("solutionDescription#1");
        }
        /*Parse next element's cost to string*/
        try {
            cur_cost = to_string(next_element->getCost());
        } catch (const char *e) {
            perror("SolutionDescription#2");
            perror(e);
        }
        /*Add all up to the end of result so far*/
        result->append(cur_direction + " (" + cur_cost + "), ");
    }
    /*Pop last space, ',' delimiter and adds end of line */
    result->pop_back();
    result->pop_back();
    result->append("\n");
    return result;
}

/**
 * Splits content to chunks of 1024 to send to client.
 * @tparam P
 * @param solution as returned from solutionDescriptor or Cache.
 * @return
 */
template<class P>
list<string> MyClientHandler<P>::toChunks(string *solution) {
    list<string> result;
    string cur_chunk;
    int chunk_size = MAX_CHARS-1;

    result.clear();
    for(unsigned i = 0; i<solution->size();i+=chunk_size) {
        cur_chunk = solution->substr(i,chunk_size);
        result.push_back(cur_chunk);
    }
    result.emplace_back("\n");
    return result;
}






