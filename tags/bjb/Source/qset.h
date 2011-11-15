#ifndef QSET_H
#define QSET_H

#include <list>
#include "triple.h"

class QSet
{
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

private:
    std::list<Triple*> TripleList;
};

inline QSet::QSet()
    : TripleList()
{
}

inline QSet::QSet(const std::list<Polynom*>& basis)
    : TripleList()
{
    std::list<Polynom*>::const_iterator itBasis(basis.begin());
    while (itBasis != basis.end())
    {
        if (*itBasis)
        {
            TripleList.push_back(new Triple(*itBasis));
        }
        ++itBasis;
    }
    TripleList.sort(Triple::Compare);
}

inline QSet::~QSet()
{
    Clear();
}

inline Triple* QSet::Get()
{
    Triple* result = TripleList.back();
    TripleList.pop_back();
    return result;
}

inline bool QSet::Empty() const
{
    return TripleList.empty();
}

inline std::size_t QSet::Size() const
{
    return TripleList.size();
}

#endif // QSET_H
