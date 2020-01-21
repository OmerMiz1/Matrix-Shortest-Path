//
// Created by omer on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SEARCHER_H_
#define ALGORITHMICPROGRAMMING2__SEARCHER_H_

#include <list>

#include "State.h"
#include "Searchable.h"

;using namespace std;

/*Interface*/
template<typename P>
class Searcher {
 public:
    virtual list<P> search(Searchable<P>*)=0;
};

#endif //ALGORITHMICPROGRAMMING2__SEARCHER_H_
