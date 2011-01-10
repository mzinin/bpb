#include "triple.h"

Triple::Triple(Polynom *initialPolynom)
    : Lm(0)
    , Poly(0)
    , Anc(0)
    , Wanc(0)
    , Nmp()
    , Var(-1)
{
    if (!initialPolynom)
    {
        throw 1;
    }

    Poly = initialPolynom;
    Lm = &Poly->Lm();
    Anc = this;
    Nmp = std::set<Monom::Integer>();
}

Triple::Triple(Polynom *initialPolynom
             , const Triple* initialAncestor
             , const std::set<Monom::Integer>& initialNmp
             , const Triple* weakAncestor
             , Monom::Integer nmVar)
    : Lm(0)
    , Poly(0)
    , Anc(0)
    , Wanc(0)
    , Nmp()
    , Var(nmVar)
{
    if (!initialPolynom)
    {
        throw 1;
    }

    if (Var == -1)
    {
        Poly = initialPolynom;
        if (initialAncestor)
        {
            Anc = initialAncestor;
        }
        else
        {
            Anc = this;
        }
    }
    else
    {
        Poly = new Polynom();
        (*Poly) += initialPolynom->Lm();

        Anc = initialAncestor;
        Wanc = weakAncestor;
    }

    Lm = &Poly->Lm();
    Nmp = initialNmp;
}

Triple::~Triple()
{
    delete Poly;
}

FastAllocator Triple::Allocator(sizeof(Triple));
