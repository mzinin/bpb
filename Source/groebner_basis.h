#include <list>
#include <algorithm>

#include "qset.h"
#include "tset.h"

class GroebnerBasis
{
private:
    std::list<Polynom*> GBasis;
    TSet IntermediateBasis;
    QSet ProlongationsSet;

public:
    GroebnerBasis();
    ~GroebnerBasis();

    void Construct(const std::list<Polynom*>& set);

    const Polynom& operator[](int number) const;
    unsigned Length() const;

    friend std::ostream& operator<<(std::ostream& out, const GroebnerBasis& groebnerBasis);

private:
    Polynom* NormalForm(const Triple* triple) const;
    const Polynom* FindDivisor(const Polynom* polynom, const std::list<Polynom*>& set, bool toGroebner) const;
    Polynom* Reduce(Polynom* polynom, const std::list<Polynom*>& set, bool toGroebner) const;
    void ReduceSet(bool toGroebner = true);
    void ConstructInvolutiveBasis();
    void Reset();
};
