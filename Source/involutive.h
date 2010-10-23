#include <list>
#include <algorithm>
#include "tset.h"
#include "qset.h"

class GBasis
{
public:
    GBasis();
    GBasis(const std::list<Polynom*>& set);
    ~GBasis() {}

    Polynom* operator[](int num);
    unsigned Length();
    Polynom* NormalForm(const Triple* p);

    friend std::ostream& operator<<(std::ostream& out, GBasis& gBasis);

protected:
    const Polynom* FindR(const Polynom* p, const std::list<Polynom*>& Q);
    Polynom* Reduce(Polynom* p, const std::list<Polynom*>& Q);
    void ReduceSet();
    void InvolutiveBasis();

protected:
    Monom::Integer Dim;
    std::list<Polynom*> gBasis;
    TSET tSet;
    QSET qSet;
};
