#include "janettree.h"

JanetTree::~JanetTree()
{
    clear();
    delete mRoot;
}

Triple* JanetTree::find(const Monom& m) const
{
    Triple* trpl = NULL;

    if (mRoot)
    {
        ConstIterator j(mRoot);
        Monom::Integer d = m.degree();
        Monom::Integer var = 0;
        do
        {
            //while(j.degree() != m[var] && j.isNextDeg())
            if (j.degree() != m[var] && j.isNextDeg())
            {
                j.step_deg();
            }

            if (j.degree() != m[var])
            {
                break;
            }
            else if (j.isNextVar())
            {
                d -= m[var];
                if (d == 0)
                {
                    break;
                }
                var++;
                j.step_var();
            }
            else
            {
                trpl = j.trpl();
                break;
            }
        } while(true);
    }
    return trpl;
}

void JanetTree::del(Triple *trpl)
{
    Iterator j(mRoot);
    //подсчет ветвлений
    Monom::Integer var = 0, vet = 0;
    if (j.isNextDeg() && j.isNextVar())
    {
        vet++;
    }

    do
    {
        while(j.degree() < trpl->getPolyLm()[var])
        {
            j.step_deg();
            if (j.isNextDeg() && j.isNextVar())
            {
                vet++;
            }
        }

        if (j.nextVar())
        {
            var++;
            j.step_var();
            if (j.isNextDeg() && j.isNextVar())
            {
                vet++;
            }
        }
        else
        {
            break;
        }
    } while(true);

    //собственно удаление
    j = mRoot;
    var = 0;
    bool varDirection = false;

    if (j.isNextDeg() && j.isNextVar())
    {
        vet--;
    }
    if (vet == 0)
    {
        if (j.degree() < trpl->getPolyLm()[var])
        {
            j.step_deg();
        }
        else
        {
            varDirection = true;
        }
    }

    while (vet > 0)
    {
        while(j.degree() < trpl->getPolyLm()[var] && vet > 0)
        {
            j.step_deg();
            if (j.isNextDeg() && j.isNextVar())
            {
                vet--;
            }
        }

        if (vet==0)
        {
            if (j.degree() < trpl->getPolyLm()[var])
            {
                j.step_deg();
                break;
            }
            else
            {
                varDirection = true;
                break;
            }
        }

        var++;
        j.step_var();
        if (j.isNextDeg() && j.isNextVar())
        {
            vet--;
        }
        if (vet==0)
        {
            if (j.degree() < trpl->getPolyLm()[var])
            {
                j.step_deg();
                break;
            }
            else
            {
                varDirection = true;
                break;
            }
        }
    }

    if (varDirection)
    {
        Iterator j1 = j;
        j1.step_var();
        j1.clear();
        j.del();
    }
    else
    {
        j.clear();
    }
}

void JanetTree::insert(Triple* trpl)
{
    Monom::Integer d = trpl->getPolyLm().degree();
    JanetTree::Iterator j(mRoot);

    if (mRoot == NULL)
    {
        j.build(d, 0, trpl);
    }
    else
    {
        Monom::Integer var = 0;
        do
        {
            while(j.degree() < trpl->getPolyLm()[var] && j.isNextDeg())
            {
                j.step_deg();
            }

            if (j.degree() > trpl->getPolyLm()[var])
            {
                j.build(d, var, trpl);
                break;
            }
            else if (j.degree() == trpl->getPolyLm()[var])
            {
                d -= trpl->getPolyLm()[var];
                var++;
                j.step_var();
            }
            else
            {
                j.step_deg();
                j.build(d, var, trpl);
                break;
            }
        } while(true);
    }
}

void JanetTree::clear()
{
    if (mRoot)
    {
        JanetTree::Iterator j(mRoot);
        j.clear();
    }
}

set<Monom::Integer> JanetTree::nmulti(Triple *trpl)
{
    IASSERT(trpl->getPoly() != NULL);
    IASSERT(find(trpl->getPolyLm()) == trpl);

    JanetTree::ConstIterator j(mRoot);
    set<Monom::Integer> result;
    Monom::Integer var = 0;
    do
    {
        while(j.degree() < trpl->getPolyLm()[var])
        {
            j.step_deg();
        }

        if (j.isNextDeg())
        {
            result.insert(var);
        }

        var++;
        if (j.isNextVar())
        {
            j.step_var();
        }
        else
        {
            break;
        }
    } while(true);

    return result;
}
