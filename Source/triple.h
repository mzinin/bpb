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

    const Polynom* getPoly() const;
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

inline const Monom& Triple::getAncLm() const
{
    return *anc_lm;
}

inline const Triple* Triple::getWanc() const
{
    return wanc;
}

inline Monom::Integer Triple::getVar() const
{
    return var;
}

inline bool Triple::isCriteriaAppliable() const
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

        const Polynom* getPoly() const;
        const Monom& getPolyLm() const;
        const Triple* getAnc() const;
        const set<Monom::Integer>& getNmp() const;

        void setNmp(const set<Monom::Integer>& newNmp);
        void setNmp(Monom::Integer var);
        bool testNmp(Monom::Integer var) const;

        void* operator new(std::size_t);
        void operator delete(void *ptr);
        static bool compare(Triple* a, Triple* b);
};
#endif

inline const Polynom* Triple::getPoly() const
{
    return poly;
}

inline const Monom& Triple::getPolyLm() const
{
    return *lm;
}

inline const Triple* Triple::getAnc() const
{
    return anc;
}

inline const set<Monom::Integer>& Triple::getNmp() const
{
    return nmp;
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

inline bool Triple::compare(Triple* a, Triple* b)
{
    return *a->lm > *b->lm;
}

#endif // TRIPLE_H
