#include "triple.h"

Triple::Triple(Polynom *initialPolynom):
        var(-1)
#ifdef USE_REAL_MINSTRATEGY
        ,hiddenDegree(0)
#endif
{
    poly = initialPolynom;
    lm = &poly->Lm();
    anc = this;
    nmp = std::set<Monom::Integer>();
}

Triple::Triple(Polynom *initialPolynom
              ,const Triple* initialAncestor
              ,const std::set<Monom::Integer>& initialNmp
              ,const Triple* weakAncestor
              ,Monom::Integer nmVar
#ifdef USE_REAL_MINSTRATEGY
              ,Monom::Integer hDegree
#endif
              ):
        var(nmVar)
#ifdef USE_REAL_MINSTRATEGY
       ,hiddenDegree(hDegree)
#endif
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
        //Monom tmpMonom(weakAncestor->GetPolyLm());
        //tmpMonom *= var;
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
