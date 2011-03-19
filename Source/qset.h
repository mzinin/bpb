#ifndef QSET_H
#define QSET_H

#include <list>
#include <algorithm>
#include "triple.h"

template <typename MonomType>
class QSet
{
private:
    std::list<Triple<MonomType>*> TripleList;

public:
    QSet();
    QSet(const std::list<Polynom<MonomType>*>& basis);
    ~QSet();

    void Insert(std::list<Polynom<MonomType>*>& addList);
    void Insert(std::list<Triple<MonomType>*>& addList);

    Triple<MonomType>* Get();

    void Clear();
    bool Empty() const;
    std::size_t Size() const;
    void DeleteDescendants(const Triple<MonomType>* ancestor);
};

template <typename MonomType>
QSet<MonomType>::QSet()
    : TripleList()
{
}

template <typename MonomType>
QSet<MonomType>::QSet(const std::list<Polynom<MonomType>*>& basis)
    : TripleList()
{
    std::list<Polynom<MonomType>*>::const_iterator itBasis(basis.begin());
    while (itBasis != basis.end())
    {
        if (*itBasis)
        {
            TripleList.push_back(new Triple<MonomType>(*itBasis));
        }
        ++itBasis;
    }
    TripleList.sort(Triple<MonomType>::Compare);
}

template <typename MonomType>
QSet<MonomType>::~QSet()
{
    Clear();
}

template <typename MonomType>
void QSet<MonomType>::Insert(std::list<Polynom<MonomType>*>& addList)
{
    std::list<Polynom<MonomType>*>::const_iterator itBasis(addList.begin());
    while ( itBasis != addList.end() )
    {
        if (*itBasis)
        {
            TripleList.push_back(new Triple<MonomType>(*itBasis));
        }
        ++itBasis;
    }
    TripleList.sort(Triple<MonomType>::Compare);
}

template <typename MonomType>
void QSet<MonomType>::Insert(std::list<Triple<MonomType>*>& addList)
{
    addList.sort(Triple<MonomType>::Compare);
    TripleList.merge(addList, Triple<MonomType>::Compare);
}

template <typename MonomType>
Triple<MonomType>* QSet<MonomType>::Get()
{
    Triple<MonomType>* result = TripleList.back();
    TripleList.pop_back();
    return result;
}

template <typename MonomType>
void QSet<MonomType>::Clear()
{
    std::list<Triple<MonomType>*>::iterator it(TripleList.begin());
    while (it != TripleList.end())
    {
        delete *it;
        ++it;
    }
    TripleList.clear();
}

template <typename MonomType>
inline bool QSet<MonomType>::Empty() const
{
    return TripleList.empty();
}

template <typename MonomType>
inline std::size_t QSet<MonomType>::Size() const
{
    return TripleList.size();
}

template <typename MonomType>
void QSet<MonomType>::DeleteDescendants(const Triple<MonomType>* ancestor)
{
    if (!ancestor)
    {
        return;
    }

    std::list<Triple<MonomType>*>::iterator it(TripleList.begin());
    while ( it != TripleList.end() )
    {
        if ((**it).GetAncestor() == ancestor || (**it).GetWeakAncestor() == ancestor)
        {
            delete *it;
            it = TripleList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

#endif // QSET_H
