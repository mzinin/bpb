#include "janettree.h"

JanetTree::~JanetTree()
{
    Clear();
    delete jRoot;
}

const Triple* JanetTree::Find(const Monom& monom) const
{
    const Triple* trpl(0);

    if (jRoot)
    {
        ConstIterator j(jRoot);
        Monom::Integer d = monom.Degree();
        Monom::Integer var = 0;
        do
        {
            if (j.Degree() != monom[var] && j.IsNextDegree())
            {
                j.StepDegree();
            }

            if (j.Degree() != monom[var])
            {
                break;
            }
            else if (j.IsNextVariable())
            {
                d -= monom[var];
                if (d == 0)
                {
                    break;
                }
                ++var;
                j.StepVariable();
            }
            else
            {
                trpl = j.GetTriple();
                break;
            }
        } while(true);
    }
    return trpl;
}

void JanetTree::Delete(const Triple *trpl)
{
    Iterator j(jRoot);
    //подсчет ветвлений
    Monom::Integer var = 0, vet = 0;
    if (j.IsNextDegree() && j.IsNextVariable())
    {
        ++vet;
    }

    do
    {
        while(j.Degree() < trpl->GetPolyLm()[var])
        {
            j.StepDegree();
            if (j.IsNextDegree() && j.IsNextVariable())
            {
                ++vet;
            }
        }

        if (j.NextVariable())
        {
            ++var;
            j.StepVariable();
            if (j.IsNextDegree() && j.IsNextVariable())
            {
                ++vet;
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

    if (j.IsNextDegree() && j.IsNextVariable())
    {
        vet--;
    }
    if (vet == 0)
    {
        if (j.Degree() < trpl->GetPolyLm()[var])
        {
            j.StepDegree();
        }
        else
        {
            varDirection = true;
        }
    }

    while (vet > 0)
    {
        while(j.Degree() < trpl->GetPolyLm()[var] && vet > 0)
        {
            j.StepDegree();
            if (j.IsNextDegree() && j.IsNextVariable())
            {
                vet--;
            }
        }

        if (vet==0)
        {
            if (j.Degree() < trpl->GetPolyLm()[var])
            {
                j.StepDegree();
                break;
            }
            else
            {
                varDirection = true;
                break;
            }
        }

        ++var;
        j.StepVariable();
        if (j.IsNextDegree() && j.IsNextVariable())
        {
            vet--;
        }
        if (vet==0)
        {
            if (j.Degree() < trpl->GetPolyLm()[var])
            {
                j.StepDegree();
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
        j1.StepVariable();
        j1.Clear();
        j.Delete();
    }
    else
    {
        j.Clear();
    }
}

void JanetTree::Insert(Triple* trpl)
{
    Monom::Integer d = trpl->GetPolyLm().Degree();
    JanetTree::Iterator j(jRoot);

    if (!jRoot)
    {
        j.Build(d, 0, trpl);
    }
    else
    {
        Monom::Integer var = 0;
        do
        {
            while(j.Degree() < trpl->GetPolyLm()[var] && j.IsNextDegree())
            {
                j.StepDegree();
            }

            if (j.Degree() > trpl->GetPolyLm()[var])
            {
                j.Build(d, var, trpl);
                break;
            }
            else if (j.Degree() == trpl->GetPolyLm()[var])
            {
                d -= trpl->GetPolyLm()[var];
                ++var;
                j.StepVariable();
            }
            else
            {
                j.StepDegree();
                j.Build(d, var, trpl);
                break;
            }
        } while(true);
    }
}

void JanetTree::Clear()
{
    if (jRoot)
    {
        JanetTree::Iterator j(jRoot);
        j.Clear();
    }
}

std::set<Monom::Integer> JanetTree::NonMulti(const Triple* triple) const
{
    std::set<Monom::Integer> result;

    if (jRoot)
    {
        ConstIterator j(jRoot);
        Monom::Integer var = 0;
        do
        {
            while (j.Degree() < triple->GetPolyLm()[var])
            {
                j.StepDegree();
            }
            if (j.IsNextDegree())
            {
                result.insert(var);
            }

            ++var;
            if (j.IsNextVariable())
            {
                j.StepVariable();
            }
            else
            {
                break;
            }
        } while(true);
    }

    return result;
}
