//
// Created by Dor Refaeli on 21/01/2020.
//

#include "HashPriorityQueueAStar.h"

/** Inserts to queue.
 *
 * @tparam P
 * @param element
 */
template <typename P>
void HashPriorityQueueAStar<P>::insert(pair<P,int> element) {
    /*If exists already, must be removed first.
     *NOTE: if gets here, its derived from AStar's logic!*/
    if(my_set.count(element)) {
        my_set.erase(my_set.find(element));
    }
    this->my_set.insert(element);
    this->push(element);
}

/** Remove and return the top of the queue.
 *
 * @tparam P
 * @return
 */
template<typename P>
pair<P,int> HashPriorityQueueAStar<P>::topAndPop() {
    auto element = this->top();
    this->pop();
    this->my_set.erase(element);
    ++evaluated_nodes;
    return element;
}

/** Returns true if element exists.
 *
 * @tparam P
 * @param element
 * @return
 */
template<typename P>
bool HashPriorityQueueAStar<P>::contains(pair<P,int> element) {
    return this->my_set.count(element);
}

/** Returns an element from queue.
 *
 * @tparam P
 * @param element
 * @return
 */
template<typename P>
pair<P,int> HashPriorityQueueAStar<P>::find(pair<P,int> element) {
    return *(this->my_set.find(element));
}

