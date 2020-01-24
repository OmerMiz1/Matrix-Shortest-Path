//
// Created by omer on 15/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2__CACHEMANAGER_H_
#define ALGORITHMICPROGRAMMING2__CACHEMANAGER_H_

#include "Cloneable.h"
using namespace std;

/*Interface*/
/** Template CacheManager
 *
 * @tparam P problem - string.
 * @tparam S solution - string.
 */
template<typename P, typename S>
class CacheManager : Cloneable<CacheManager<P,S>> {
 public:
    virtual void insert(P* problem, S* solution)=0;
    virtual bool contains(P* given_problem)=0;
    virtual S *get(P* problem)=0;
    virtual CacheManager<P, S>* clone() const=0;
};
#endif //ALGORITHMICPROGRAMMING2__CACHEMANAGER_H_
