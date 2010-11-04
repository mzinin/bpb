#ifndef QSET_H
#define QSET_H

#include "triple.h"
#include <list>
#include <algorithm>

class QSet
{
private:
    std::list<Triple*> tripleList;

public:
    QSet();
    QSet(const std::list<Polynom*>& basis);
    ~QSet();

    void Insert(std::list<Polynom*>& addList);
    void Insert(std::list<Triple*>& addList);

    Triple* Get();

    void Clear();
    bool Empty() const;
    std::size_t Size() const;
    void DeleteDescendants(const Triple* ancestor);
};

inline bool QSet::Empty() const
{
    return tripleList.empty();
}

inline std::size_t QSet::Size() const
{
    return tripleList.size();
}

#endif // QSET_H
