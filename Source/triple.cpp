#include "triple.h"

Triple::Triple(Polynom *initialPolynom)
    : lm(0)
    , poly(0)
    , anc(0)
    , wanc(0)
    , nmp()
    , var(-1)
{
    poly = initialPolynom;
    lm = &poly->Lm();
    anc = this;
    nmp = std::set<Monom::Integer>();
}

Triple::Triple(Polynom *initialPolynom
             , const Triple* initialAncestor
             , const std::set<Monom::Integer>& initialNmp
             , const Triple* weakAncestor
             , Monom::Integer nmVar)
    : lm(0)
    , poly(0)
    , anc(0)
    , wanc(0)
    , nmp()
    , var(nmVar)
{
    if (var == -1)
    {
        poly = initialPolynom;
        if (initialAncestor)
        {
            anc = initialAncestor;
        }
        else
        {
            anc = this;
        }
    }
    else
    {
        poly = new Polynom();
        Monom tmpMonom(initialPolynom->Lm());
        (*poly) += tmpMonom;

        anc = initialAncestor;
        wanc = weakAncestor;
    }

    lm = &poly->Lm();
    nmp = initialNmp;
}

Triple::~Triple()
{
    delete poly;
}

Allocator Triple::tAllocator(sizeof(Triple));
