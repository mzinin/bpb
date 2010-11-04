#include <list>
#include <algorithm>
#include "tset.h"
#include "qset.h"

class GroebnerBasis
{
private:
    std::list<Polynom*> GBasis;
    TSet IntermediateBasis;
    QSet ProlongationsSet;
    unsigned long NonMultiProlongations;
    unsigned long NonZeroReductions;

public:
    GroebnerBasis();
    ~GroebnerBasis();

    void Construct(const std::list<Polynom*>& set);
    void PrintStatistics(std::ostream& out) const;

    const Polynom& operator[](int number) const;
    unsigned Length() const;

    friend std::ostream& operator<<(std::ostream& out, GroebnerBasis& groebnerBasis);

private:
    Polynom* NormalForm(const Triple* triple);
    const Polynom* FindR(const Polynom* polynom, const std::list<Polynom*>& set);
    Polynom* Reduce(Polynom* polynom, const std::list<Polynom*>& set);
    void ReduceSet();
    void ConstructInvolutiveBasis();
    void Reset();
};
