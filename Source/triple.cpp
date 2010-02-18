#include "triple.h"

#ifdef USE_CRITERIA
Triple::Triple(Polynom *initialPolynom)
{
    poly = initialPolynom;
    lm = &poly->lm();
    anc = this;
    anc_lm = lm;
    wanc = NULL;
    nmp = set<Monom::Integer>();
    var = -1;
}

Triple::Triple(Polynom *initialPolynom,
               const Triple* initialAncestor,
               const Triple* initialWeakAncestor,
               const set<Monom::Integer>& initialNmp,
               Monom::Integer lastProlongingVar)
{
    poly = initialPolynom;
    lm = &poly->lm();
    if (initialAncestor)
    {
        anc = initialAncestor;
        anc_lm = &anc->getPolyLm();
    }
    else
    {
        anc = this;
        anc_lm = lm;
    }
    wanc = initialWeakAncestor;
    nmp = initialNmp;
    var = lastProlongingVar;
    if (var != -1)
    {
        nmp.insert(var);
    }
}
#else
Triple::Triple(Polynom *initialPolynom)
{
    poly = initialPolynom;
    lm = &poly->lm();
    anc = this;
    nmp = set<Monom::Integer>();
}

Triple::Triple(Polynom *initialPolynom,
               const Triple* initialAncestor,
               const set<Monom::Integer>& initialNmp)
{
    poly = initialPolynom;
    lm = &poly->lm();
    if (initialAncestor)
    {
        anc = initialAncestor;
    }
    else
    {
        anc = this;
    }
    nmp = initialNmp;
}
#endif

Triple::~Triple()
{
    delete poly;
}

Allocator Triple::tAllocator(sizeof(Triple));
