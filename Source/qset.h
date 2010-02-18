#ifndef QSET_H
#define QSET_H

#include "triple.h"
#include <list>
#include <algorithm>

class QSET
{
//public:
    list<Triple*> tripleList;

public:
    QSET();
    QSET(const list<Polynom*>& basis);
    ~QSET();

    void Insert(list<Polynom*>& addList);
    void Insert(list<Triple*>& addList);
    void Update(Triple* newTriple, list<Triple*>& set);
    Triple* Get();

    bool Empty() const;
    std::size_t Size() const;
    void DeleteDescendants(const Triple* ancestor);
};

inline bool QSET::Empty() const
{
    return tripleList.empty();
}

inline std::size_t QSET::Size() const
{
    return tripleList.size();
}

#endif // QSET_H
