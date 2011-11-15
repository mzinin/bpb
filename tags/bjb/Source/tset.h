#ifndef TSET_H
#define TSET_H

#include <list>
#include "janettree.h"

class TSet
{
public:
    typedef std::list<Triple*>::iterator Iterator;
    typedef std::list<Triple*>::const_iterator ConstIterator;

    TSet();
    ~TSet();

    Iterator Begin();
    ConstIterator Begin() const;
    Iterator End();
    ConstIterator End() const;

    void Clear();
    Iterator Erase(Iterator it);
    void PushBack(Triple* newTriple);
    std::size_t Size() const;

    const Triple* FindDivisor(const Monom& monom) const;
    std::set<Monom::Integer> NonMulti(const Triple* triple) const;
    Triple* const Back() const;
    
    void CollectNonMultiProlongations(Iterator& iterator, std::list<Triple*>& set);

private:
    std::list<Triple*> TripleList;
    JanetTree JTree;
};

inline TSet::TSet()
    : TripleList()
    , JTree()
{
}

inline TSet::~TSet()
{
    Clear();
}

inline TSet::Iterator TSet::Begin()
{ 
    return TripleList.begin();
}

inline TSet::ConstIterator TSet::Begin() const
{ 
    return TripleList.begin();
}

inline TSet::Iterator TSet::End()
{ 
    return TripleList.end();
}

inline TSet::ConstIterator TSet::End() const 
{ 
    return TripleList.end(); 
}

inline TSet::Iterator TSet::Erase(TSet::Iterator it)
{
    JTree.Delete(*it);
    return TripleList.erase(it);
}

inline void TSet::PushBack(Triple* newTriple)
{
    TripleList.push_back(newTriple);
    JTree.Insert(newTriple);
}

inline std::size_t TSet::Size() const 
{ 
    return TripleList.size();
}

inline const Triple* TSet::FindDivisor(const Monom& monom) const 
{ 
    return JTree.Find(monom);
}

inline std::set<Monom::Integer> TSet::NonMulti(const Triple* triple) const
{
    return JTree.NonMulti(triple);
}

inline Triple* const TSet::Back() const 
{ 
    return TripleList.back();
}

#endif // TSET_H
