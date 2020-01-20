//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__CACHEMANAGER_H_
#define ALGORITHMICPROGRAMMING2__CACHEMANAGER_H_

using namespace std;

/*Interface*/
/**
 * 1. lru list: Queue, the front pair contains the least recently used object.
 * 2. cacheMap: contains the data for fast access.
 **/
template<typename P, typename S>
class CacheManager {
 public:
    virtual void insert(P problem, S solution)=0;
    virtual bool contains(P given_problem)=0;
    virtual S get(P problem)=0;
};

/*TODO: if doesnt work without declaration of CacheManager<Searchable<P>, list<State<P>>
 * just add explicit declaration*/


#endif //ALGORITHMICPROGRAMMING2__CACHEMANAGER_H_
