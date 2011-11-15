#ifndef GROEBNER_BASIS_H
#define GROEBNER_BASIS_H

#include <list>
#include "qset.h"
#include "tset.h"

class GroebnerBasis
{
public:
    GroebnerBasis();
    ~GroebnerBasis();

    void Construct(const std::list<Polynom*>& set);
    
    const Polynom& operator[](int number) const;
    unsigned Length() const;

    friend std::ostream& operator<<(std::ostream& out, const GroebnerBasis& groebnerBasis);

private:
    bool Criterion1(const Triple* p, const Triple* g) const;
    bool Criterion2(const Triple* p, const Triple* g) const;
    bool Criterion3(const Triple* p, const Triple* g) const;
    bool Criterion4(const Triple* p, const Triple* g) const;
    Polynom* NormalForm(const Triple* triple) const;

    const Polynom* FindDivisor(const Polynom* polynom, const std::list<Polynom*>& set) const;
    Polynom* Reduce(Polynom* polynom, const std::list<Polynom*>& set) const;
    void ReduceSet();
    void ConstructInvolutiveBasis();
    void Reset();
    
private:
    std::list<Polynom*> GBasis;
    TSet IntermediateBasis;
    QSet ProlongationsSet;
};

#endif // GROEBNER_BASIS_H
