#include <list>
#include <algorithm>
#include "tset.h"
#include "qset.h"

class GBasis
{
private:
    std::list<Polynom*> gBasis;
    TSET tSet;
    QSET qSet;
#ifdef COLLECT_STATISTICS
    unsigned long nonMultiProlongations;
    unsigned long nonZeroReductions;
#endif // COLLECT_STATISTICS

public:
    GBasis();
    ~GBasis();
    void Construct(const std::list<Polynom*>& set);

    const Polynom& operator[](int num) const;
    unsigned Length() const;

#ifdef COLLECT_STATISTICS
    void PrintStatistics(std::ostream& out) const;
#endif // COLLECT_STATISTICS

    friend std::ostream& operator<<(std::ostream& out, GBasis& gBasis);

private:
    Polynom* NormalForm(const Triple* p);
    const Polynom* FindR(const Polynom* p, const std::list<Polynom*>& Q);
    Polynom* Reduce(Polynom* p, const std::list<Polynom*>& Q);
    void ReduceSet();
    void ConstructInvolutiveBasis();
    void Reset();
};
