#ifndef TRIPLE_H
#define TRIPLE_H

#include <set>
#include "fast_allocator.h"
#include "polynom.h"

class Triple 
{
public:
    Triple(Polynom* initialPolynom);

    Triple(Polynom* initialPolynom
         , const Triple* initialAncestor
         , const std::set<Monom::Integer>& initialNmp
         , const Triple* weakAncestor
         , Monom::Integer nmVar);

    ~Triple();

    void* operator new(std::size_t);
    void operator delete(void *ptr);

    const Polynom* GetPolynom() const;
    const Monom& GetPolynomLm() const;
    const Triple* GetAncestor() const;
    const Triple* GetWeakAncestor() const;
    Monom::Integer GetVariable() const;
    const std::set<Monom::Integer>& GetNmp() const;

    void SetNmp(const std::set<Monom::Integer>& newNmp);
    void SetNmp(Monom::Integer variable);
    bool TestNmp(Monom::Integer variable) const;

    static bool Compare(const Triple* tripleA, const Triple* tripleB);
    
private:
    static FastAllocator Allocator;

    const Monom* Lm;
    Polynom* Polynomial;
    const Triple* Ancestor;
    const Triple* WeakAncestor;
    std::set<Monom::Integer> Nmp;
    const Monom::Integer Variable;
};


inline Triple::~Triple() 
{
    delete Polynomial;
}

inline void* Triple::operator new(std::size_t) 
{ 
    return Allocator.Allocate(); 
}

inline void Triple::operator delete(void *ptr) 
{ 
    Allocator.Free(ptr); 
}

inline const Polynom* Triple::GetPolynom() const
{
    return Polynomial;
}

inline const Monom& Triple::GetPolynomLm() const 
{ 
    return *Lm;
}

inline const Triple* Triple::GetAncestor() const 
{ 
    return Ancestor;
}

inline const Triple* Triple::GetWeakAncestor() const 
{ 
    return WeakAncestor;
}

inline Monom::Integer Triple::GetVariable() const 
{ 
    return Variable;
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

#endif // TRIPLE_H
