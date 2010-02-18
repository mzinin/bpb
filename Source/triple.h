#ifndef TRIPLE_H
#define TRIPLE_H

#include <set>
#include "polynom.h"


#ifdef USE_CRITERIA

class Triple
{
    const Monom* lm;
    const Monom* anc_lm;
    set<Monom::Integer> nmp;
    Polynom* poly;
    const Triple* anc;
    const Triple* wanc;
    Monom::Integer var;
    static Allocator tAllocator;

public:
    Triple(Polynom* initialPolynom);

    Triple(Polynom* initialPolynom,
           const Triple* initialAncestor,
           const Triple* initialWeakAncestor,
           const set<Monom::Integer>& initialNmp,
           Monom::Integer lastProlongingVar);

    ~Triple();

    const Polynom* GetPoly() const;
    const Monom& GetPolyLm() const;
    const Triple* GetAnc() const;
    const Monom& GetAncLm() const;
    const Triple* GetWanc() const;
    const set<Monom::Integer>& GetNmp() const;
    Monom::Integer GetVar() const;
    bool IsCriteriaAppliable() const;

    void SetNmp(const set<Monom::Integer>& newNmp);
    void SetNmp(Monom::Integer var);
    bool TestNmp(Monom::Integer var) const;

    void* operator new(std::size_t);
    void operator delete(void *ptr);
    static bool Compare(const Triple* a, const Triple* b);
};

inline const Monom& Triple::GetAncLm() const
{
    return *anc_lm;
}

inline const Triple* Triple::GetWanc() const
{
    return wanc;
}

inline Monom::Integer Triple::GetVar() const
{
    return var;
}

inline bool Triple::IsCriteriaAppliable() const
{
    return var != -1;
}

#else

class Triple
{
    const Monom* lm;
    set<Monom::Integer> nmp;
    Polynom* poly;
    const Triple* anc;
    static Allocator tAllocator;

    public:
        Triple(Polynom* initialPolynom);

        Triple(Polynom* initialPolynom,
               const Triple* initialAncestor,
               const set<Monom::Integer>& initialNmp);

        ~Triple();

        const Polynom* GetPoly() const;
        const Monom& GetPolyLm() const;
        const Triple* GetAnc() const;
        const set<Monom::Integer>& GetNmp() const;

        void SetNmp(const set<Monom::Integer>& newNmp);
        void SetNmp(Monom::Integer var);
        bool TestNmp(Monom::Integer var) const;

        void* operator new(std::size_t);
        void operator delete(void *ptr);
        static bool Compare(const Triple* a, const Triple* b);
};
#endif

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

inline const set<Monom::Integer>& Triple::GetNmp() const
{
    return nmp;
}

inline void Triple::SetNmp(const set<Monom::Integer>& newNmp)
{
    nmp = newNmp;
}

inline void Triple::SetNmp(Monom::Integer var)
{
    nmp.insert(var);
}

inline bool Triple::TestNmp(Monom::Integer var) const
{
    //short res = nmp.count(var);
    //return res;
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
    return *a->lm > *b->lm;
}

#endif // TRIPLE_H
