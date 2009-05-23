#ifndef TRIPLE_H
#define TRIPLE_H

#include <set>
#include "polynom.h"

class Triple
{
    Monom lm;
    Monom anc_lm;
    set<Monom::Integer> nmp;
    Polynom*  poly;
    const Triple* anc;
    const Triple* wanc;
    Monom::Integer var;
    static Allocator sAllocator;

public:
    Triple(Polynom* initialPolynom);

    Triple(Polynom* initialPolynom,
           const Triple* initialAncestor,
           const Triple* initialWeakAncestor,
           const set<Monom::Integer>& initialNmp,
           Monom::Integer lastProlongingVar);

    ~Triple();

    Polynom* getPoly() const;
    const Monom& getPolyLm() const;
    const Triple* getAnc() const;
    const Monom& getAncLm() const;
    const Triple* getWanc() const;
    const set<Monom::Integer>& getNmp() const;
    Monom::Integer getVar() const;
    bool isCriteriaAppliable() const;

    void setNmp(const set<Monom::Integer>& newNmp);
    void setNmp(Monom::Integer var);
    bool testNmp(Monom::Integer var) const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    static bool compare(Triple* a, Triple* b);
};

inline Polynom* Triple::getPoly() const
{
    return poly;
}

inline const Monom& Triple::getPolyLm() const
{
    return lm;
}

inline const Triple* Triple::getAnc() const
{
    return anc;
}

inline const Monom& Triple::getAncLm() const
{
    return anc_lm;
}

inline const Triple* Triple::getWanc() const
{
    return wanc;
}

inline const set<Monom::Integer>& Triple::getNmp() const
{
    return nmp;
}

inline Monom::Integer Triple::getVar() const
{
    return var;
}

inline bool Triple::isCriteriaAppliable() const
{
    return var != -1;
}

inline void Triple::setNmp(const set<Monom::Integer>& newNmp)
{
    nmp = newNmp;
}

inline void Triple::setNmp(Monom::Integer var)
{
    nmp.insert(var);
}

inline bool Triple::testNmp(Monom::Integer var) const
{
    return nmp.count(var);
}

inline void* Triple::operator new(std::size_t)
{
    return sAllocator.allocate();
}

inline void Triple::operator delete(void *ptr)
{
    sAllocator.deallocate(ptr);
}

inline bool Triple::compare(Triple* a, Triple* b)
{
    return a->lm > b->lm;
}

#endif // TRIPLE_H
