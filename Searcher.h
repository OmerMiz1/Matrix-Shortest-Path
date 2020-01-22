//
// Created by omer on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__SEARCHER_H_
#define ALGORITHMICPROGRAMMING2__SEARCHER_H_

#include <list>

#include "State.h"
#include "Searchable.h"
#include "Cloneable.h"

;using namespace std;

/*Interface*/
template<typename P>
class Searcher : public virtual Cloneable<Searcher<P>> {
 public:
    virtual list<P> search(Searchable<P>*)=0;
    virtual Searcher<P> *clone() const =0;
};

template class Searcher<State<Point>>;
#endif //ALGORITHMICPROGRAMMING2__SEARCHER_H_
