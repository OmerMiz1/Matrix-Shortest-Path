//
// Created by omer on 19/01/2020.
//

#define MAX_CHARS 1024
#define END_OF_MESSAGE "end"
#define NO_SOLUTION "No path (-1)"

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

    /*Reads all data from client*/
    while (!reached_end) {
        tmp = readMessageFromClient(client_socketfd);
        if (tmp.empty() && !reached_end) {
            perror("handleClient#1");
            return;
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
        exit(EXIT_FAILURE); /*TODO debug*/
    }
    problem_key = hashProblem(problem);

    /*Case solution NOT IN cache*/
    if(!(my_cache->contains(problem_key))) {
        solution = my_solver->solve(problem);
        solution_str = solutionDescription(solution);
        my_cache->insert(problem_key, solution_str);
    } else { /*Solution IS IN cache*/
        solution_str = my_cache->get(problem_key);
    }

    if (send(client_socketfd, solution_str.c_str(), result.size(), 0) == -1) {
        perror("handleClient#3");
        return;
    }
    cout<<"client done"<<endl;/*TODO debug*/
}

template <class P>
list<string> MyClientHandler<P>::readMessageFromClient(int client_socketfd) {
    /*TODO: bug- doesnt stop at the right place. I think im supposed to read 1
     * time and count on them not to bring longer strings than expected.
     * If doesnt work, consider using the same "buffering" method used in EX3
     * at OpenServerCommand::startListening*/
    list<string> result;
    regex lineRx("(.*)\\n");
    sregex_iterator start, end = sregex_iterator();
    string buf_str;

    /*Clear to avoid garbage*/
    int bytes_read = 0;
    char buffer[MAX_CHARS] = {'\0'};
    bytes_read = read(client_socketfd, buffer, MAX_CHARS);

    if(strstr(buffer,"end")) {
        reached_end = true;
    }

    /*Print error, return empty list*/
    if (bytes_read == -1) {
        perror("readMessageFromClient#1");
        return list<string>();
        /*TODO remove below condition before submitting.*/
    } else if (0 < bytes_read /*&& bytes_read < MAX_CHARS*/) {
        buf_str.append(buffer);
        /*Insert each line (seperated by \n) to messages list*/
        for(start = sregex_iterator(buf_str.begin(),buf_str.end(),lineRx); start != end; ++start ) {
            result.push_back(start->str());
        }
        return result;
    }

    /*Also error, shouldnt get here.*/
    perror("readMessageFromClient#2");
    return list<string>();
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
            exit(EXIT_FAILURE); /*TODO debug*/
        }
        /*Add all up to the end of result so far*/
        result.append(cur_direction + " (" + cur_cost +"), " );
    }
    return result;
}





