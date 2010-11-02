#include <list>
#include <algorithm>
#include "tset.h"
#include "qset.h"

class GBasis
{
private:
    Monom::Integer Dim;
    std::list<Polynom*> gBasis;
    TSET tSet;
    QSET qSet;
#ifdef COLLECT_STATISTICS
    unsigned long nonMultiProlongations;
    unsigned long nonZeroReductions;
#endif // COLLECT_STATISTICS

public:
    GBasis();
    GBasis(const std::list<Polynom*>& set);
    ~GBasis() {}

    Polynom* operator[](int num);
    unsigned Length();
    Polynom* NormalForm(const Triple* p);

#ifdef COLLECT_STATISTICS
    void PrintStatistics(std::ostream& out) const;
#endif // COLLECT_STATISTICS

    friend std::ostream& operator<<(std::ostream& out, GBasis& gBasis);

private:
    const Polynom* FindR(const Polynom* p, const std::list<Polynom*>& Q);
    Polynom* Reduce(Polynom* p, const std::list<Polynom*>& Q);
    void ReduceSet();
    void InvolutiveBasis();
};
