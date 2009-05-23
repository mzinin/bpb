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
    typedef list<Triple*>::iterator tsIterator;
    typedef list<Triple*>::const_iterator tsConstIterator;

    TSET();
    ~TSET();

    Triple* find(const Monom& m) const;

    tsIterator begin();
    tsConstIterator begin() const;
    tsIterator end();
    tsConstIterator end() const;

    void clear();
    tsIterator erase(tsIterator it);
    void push_back(Triple* newTriple);
    std::size_t size() const;

    Triple* const back() const;
};


inline Triple* TSET::find(const Monom& m) const
{
    return jTree.find(m);
}

inline TSET::tsIterator TSET::begin()
{
    return tripleList.begin();
}

inline TSET::tsConstIterator TSET::begin() const
{
    return tripleList.begin();
}

inline TSET::tsIterator TSET::end()
{
    return tripleList.end();
}

inline TSET::tsConstIterator TSET::end() const
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
