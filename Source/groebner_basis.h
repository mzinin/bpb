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
    Polynom* NormalForm(const Triple* triple);
    const Polynom* FindR(const Polynom* polynom, const std::list<Polynom*>& set);
    Polynom* Reduce(Polynom* polynom, const std::list<Polynom*>& set);
    void ReduceSet();
    void ConstructInvolutiveBasis();
    void Reset();
};
