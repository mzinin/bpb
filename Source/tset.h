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

    const Triple* Find(const Monom& monom) const;

    iterator Begin();
    const_iterator Begin() const;
    iterator End();
    const_iterator End() const;

    void Clear();
    iterator Erase(iterator it);
    void PushBack(Triple* newTriple);
    std::size_t Size() const;

    Triple* const Back() const;
};


inline const Triple* TSET::Find(const Monom& monom) const
{
    return jTree.Find(monom);
}

inline TSET::iterator TSET::Begin()
{
    return tripleList.begin();
}

inline TSET::const_iterator TSET::Begin() const
{
    return tripleList.begin();
}

inline TSET::iterator TSET::End()
{
    return tripleList.end();
}

inline TSET::const_iterator TSET::End() const
{
    return tripleList.end();
}

inline std::size_t TSET::Size() const
{
    return tripleList.size();
}

inline Triple* const TSET::Back() const
{
    return tripleList.back();
}

#endif // TSET_H
