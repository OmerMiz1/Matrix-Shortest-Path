//
// Created by Dor Refaeli on 19/01/2020.
//

#include "HashPriorityQueueBestFirstSearch.h"

/** Inserts element to queue.
 *
 * @tparam E
 * @param element
 */
template <typename E>
void HashPriorityQueueBestFirstSearch<E>::insert(E element) {
    if(this->mySet.count(element) > 0) {
        this->missed_inserts++;
    }
    this->mySet.insert(element);
    this->push(element);
}

/** Removes element from top and returns it.
 *
 * @tparam E
 * @return
 */
template<typename E>
E HashPriorityQueueBestFirstSearch<E>::topAndPop() {
    E element = this->top();
    this->pop();
    this->mySet.erase(element);
    return element;
}

/** Check if element is in queue.
 *
 * @tparam E
 * @param element
 * @return
 */
template<typename E>
bool HashPriorityQueueBestFirstSearch<E>::contains(E element) {
    return this->mySet.count(element);
}

/** Returns the element as it is in the set currently.
 * Points might be the same, but the costs are different sometimes.
 *
 * @tparam E
 * @param element
 * @return
 */
template<typename E>
E HashPriorityQueueBestFirstSearch<E>::find(E element) {
    //if doesn't exist
    if (!mySet.count(element)) {
        return nullptr;
    }
    return *(this->mySet.find(element));
}

/** Removes an element from queue.
 *
 * @tparam E
 * @param element
 */
template<typename E>
void HashPriorityQueueBestFirstSearch<E>::remove(E element) {
    auto it = std::find(this->c.begin(), this->c.end(), element);
    if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        this->mySet.erase(this->mySet.find(element));
    } else {
        perror("Tried to delete an non-existing element from the HashPriorityQueueBestFirstSearch");
        exit(1);
    }
}

