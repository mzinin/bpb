#ifndef TSET_H
#define TSET_H

#include "janettree.h"
#include <list>
#include <algorithm>

class TSET
{
    list<Triple*> tripleList;
    JanetTree jTree;

public:
    typedef list<Triple*>::iterator iterator;
    typedef list<Triple*>::const_iterator const_iterator;

    TSET();
    ~TSET();

    Triple* find(const Monom& monom) const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    void clear();
    iterator erase(iterator it);
    void push_back(Triple* newTriple);
    std::size_t size() const;

    Triple* const back() const;
};


inline Triple* TSET::find(const Monom& monom) const
{
    return jTree.find(monom);
}

inline TSET::iterator TSET::begin()
{
    return tripleList.begin();
}

inline TSET::const_iterator TSET::begin() const
{
    return tripleList.begin();
}

inline TSET::iterator TSET::end()
{
    return tripleList.end();
}

inline TSET::const_iterator TSET::end() const
{
    return tripleList.end();
}

inline std::size_t TSET::size() const
{
    return tripleList.size();
}

inline Triple* const TSET::back() const
{
    return tripleList.back();
}

#endif // TSET_H
