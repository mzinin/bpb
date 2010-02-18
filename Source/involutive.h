#include <list>
#include <algorithm>
#include "tset.h"
#include "qset.h"

class GBasis
{
protected:
    Monom::Integer Dim;
    list<Polynom*> gBasis;
    TSET tSet;
    QSET qSet;

#ifdef USE_CRITERIA
    bool Criteria1(Triple* p, Triple* g);
    bool Criteria2(Triple* p, Triple* g);
    bool Criteria3(Triple* p, Triple* g);
    bool Criteria4(Triple* p, Triple* g);
#endif

    Polynom* findR(Polynom* p, list<Polynom*> &Q);
    Polynom* Reduce(Polynom* p, list<Polynom*> &Q);
    void ReduceSet();
    void InvolutiveBasis();

public:
    GBasis();
    GBasis(list<Polynom*> set);
    ~GBasis() {}

    Polynom* operator[](int num);
    unsigned length();
    Polynom* NormalForm(Triple* p);

    friend std::ostream& operator<<(std::ostream& out, GBasis& gBasis);
};
