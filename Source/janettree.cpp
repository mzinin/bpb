#include "janettree.h"

JanetTree::~JanetTree()
{
    clear();
    delete jRoot;
}

Triple* JanetTree::find(const Monom& monom) const
{
    Triple* trpl = NULL;

    if (jRoot)
    {
        ConstIterator j(jRoot);
        Monom::Integer d = monom.degree();
        Monom::Integer var = 0;
        do
        {
            if (j.degree() != monom[var] && j.isNextDegree())
            {
                j.step_deg();
            }

            if (j.degree() != monom[var])
            {
                break;
            }
            else if (j.isNextVar())
            {
                d -= monom[var];
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
    Iterator j(jRoot);
    //подсчет ветвлений
    Monom::Integer var = 0, vet = 0;
    if (j.isNextDegree() && j.isNextVar())
    {
        vet++;
    }

    do
    {
        while(j.degree() < trpl->getPolyLm()[var])
        {
            j.step_deg();
            if (j.isNextDegree() && j.isNextVar())
            {
                vet++;
            }
        }

        if (j.nextVar())
        {
            var++;
            j.step_var();
            if (j.isNextDegree() && j.isNextVar())
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
    j = jRoot;
    var = 0;
    bool varDirection = false;

    if (j.isNextDegree() && j.isNextVar())
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
            if (j.isNextDegree() && j.isNextVar())
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
        if (j.isNextDegree() && j.isNextVar())
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
    JanetTree::Iterator j(jRoot);

    if (jRoot == NULL)
    {
        j.build(d, 0, trpl);
    }
    else
    {
        Monom::Integer var = 0;
        do
        {
            while(j.degree() < trpl->getPolyLm()[var] && j.isNextDegree())
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
    if (jRoot)
    {
        JanetTree::Iterator j(jRoot);
        j.clear();
    }
}
