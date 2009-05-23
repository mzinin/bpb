#ifndef QSET_H
#define QSET_H

#include "triple.h"
#include <list>
#include <algorithm>

class QSET
{
    list<Triple*> tripleList;

public:
    QSET();
    QSET(list<Polynom*> &basis);
    ~QSET();

    void insert(list<Polynom*> &addList);
    void insert(list<Triple*> &addList);
    void update(Triple* newTriple, list<Triple*> &set);
    Triple* get();

    bool empty();
    std::size_t size();
    void deleteDescendants(Triple* ancestor);
};

inline bool QSET::empty()
{
    return tripleList.empty();
}

inline std::size_t QSET::size()
{
    return tripleList.size();
}

#endif // QSET_H
