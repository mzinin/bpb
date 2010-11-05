#ifndef TRIPLE_H
#define TRIPLE_H

#include <set>

#include "fast_allocator.h"
#include "polynom.h"

class Triple
{
private:
    const Monom* Lm;
    Polynom* Poly;
    const Triple* Anc;
    const Triple* Wanc;
    std::set<Monom::Integer> Nmp;
    const Monom::Integer Var;

    static FastAllocator Allocator;

public:
    Triple(Polynom* initialPolynom);

    Triple(Polynom* initialPolynom
         , const Triple* initialAncestor
         , const std::set<Monom::Integer>& initialNmp
         , const Triple* weakAncestor
         , Monom::Integer nmVar);

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
    return Poly;
}

inline const Monom& Triple::GetPolyLm() const
{
    return *Lm;
}

inline const Triple* Triple::GetAnc() const
{
    return Anc;
}

inline const Triple* Triple::GetWAnc() const
{
    return Wanc;
}

inline Monom::Integer Triple::GetVar() const
{
    return Var;
}

inline const std::set<Monom::Integer>& Triple::GetNmp() const
{
    return Nmp;
}

inline void Triple::SetNmp(const std::set<Monom::Integer>& newNmp)
{
    Nmp = newNmp;
}

inline void Triple::SetNmp(Monom::Integer var)
{
    Nmp.insert(var);
}

inline bool Triple::TestNmp(Monom::Integer var) const
{
    return Nmp.count(var);
}

inline void* Triple::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void Triple::operator delete(void *ptr)
{
    Allocator.Free(ptr);
}

inline bool Triple::Compare(const Triple* a, const Triple* b)
{
    return *a->Lm > *b->Lm;
}

#endif // TRIPLE_H
