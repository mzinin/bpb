#include "triple.h"

FastAllocator Triple::Allocator(sizeof(Triple));

Triple::Triple(Polynom* initialPolynom)
    : Lm(0)
    , Polynomial(initialPolynom)
    , Ancestor(0)
    , WeakAncestor(0)
    , Nmp()
    , Variable(-1)
{
    if (Polynomial)
    {
        Lm = &Polynomial->Lm();
        Ancestor = this;
        Nmp = std::set<Monom::Integer>();
    }
}

Triple::Triple(Polynom* initialPolynom
             , const Triple* initialAncestor
             , const std::set<Monom::Integer>& initialNmp
             , const Triple* weakAncestor
             , Monom::Integer nmVar)
    : Lm(0)
    , Polynomial(0)
    , Ancestor(0)
    , WeakAncestor(0)
    , Nmp()
    , Variable(nmVar)
{
    if (initialPolynom)
    {
        if (Variable == -1)
        {
            Polynomial = initialPolynom;
            if (initialAncestor)
            {
                Ancestor = initialAncestor;
            }
            else
            {
                Ancestor = this;
            }
        }
        else
        {
            Polynomial = new Polynom();
            (*Polynomial) += initialPolynom->Lm();

            Ancestor = initialAncestor;
            WeakAncestor = weakAncestor;
        }

        Lm = &Polynomial->Lm();
        Nmp = initialNmp;
    }
}

bool Triple::Compare(const Triple* tripleA, const Triple* tripleB)
{
    return *tripleA->Lm > *tripleB->Lm;
}
