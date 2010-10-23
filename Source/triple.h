#ifndef TRIPLE_H
#define TRIPLE_H

#include <set>
#include "polynom.h"

class Triple
{
private:
    const Monom* lm;
    Polynom* poly;
    const Triple* anc;
    const Triple* wanc;
    std::set<Monom::Integer> nmp;
    const Monom::Integer var;
    const Monom::Integer hiddenDegree;

    static Allocator tAllocator;

public:
    Triple(Polynom* initialPolynom);

    Triple(Polynom* initialPolynom
          ,const Triple* initialAncestor
          ,const std::set<Monom::Integer>& initialNmp
          ,const Triple* weakAncestor
          ,Monom::Integer nmVar
#ifdef USE_REAL_MINSTRATEGY
          ,Monom::Integer hDegree = 0
#endif
          );

    ~Triple();

    const Polynom* GetPoly() const;
    const Monom& GetPolyLm() const;
    const Triple* GetAnc() const;
    const Triple* GetWAnc() const;
    Monom::Integer GetVar() const;
    const std::set<Monom::Integer>& GetNmp() const;

    void SetNmp(const std::set<Monom::Integer>& newNmp);
    void SetNmp(Monom::Integer var);
    bool TestNmp(Monom::Integer var) const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    static bool Compare(const Triple* a, const Triple* b);
};

inline const Polynom* Triple::GetPoly() const
{
    return poly;
}

inline const Monom& Triple::GetPolyLm() const
{
    return *lm;
}

inline const Triple* Triple::GetAnc() const
{
    return anc;
}

inline const Triple* Triple::GetWAnc() const
{
    return wanc;
}

inline Monom::Integer Triple::GetVar() const
{
    return var;
}

inline const std::set<Monom::Integer>& Triple::GetNmp() const
{
    return nmp;
}

inline void Triple::SetNmp(const std::set<Monom::Integer>& newNmp)
{
    nmp = newNmp;
}

inline void Triple::SetNmp(Monom::Integer var)
{
    nmp.insert(var);
}

inline bool Triple::TestNmp(Monom::Integer var) const
{
    return nmp.count(var);
}

inline void* Triple::operator new(std::size_t)
{
    return tAllocator.allocate();
}

inline void Triple::operator delete(void *ptr)
{
    tAllocator.deallocate(ptr);
}

inline bool Triple::Compare(const Triple* a, const Triple* b)
{
#ifdef USE_REAL_MINSTRATEGY
    static Monom::Integer aDegree;
    static Monom::Integer bDegree;
    aDegree = a->GetPolyLm().Degree() + a->hiddenDegree;
    bDegree = b->GetPolyLm().Degree() + b->hiddenDegree;
    if (aDegree > bDegree)
        return true;
    else if (aDegree < bDegree)
        return false;
    else
#endif
        return *a->lm > *b->lm;
}

#endif // TRIPLE_H
