#include "janettree.h"

JanetTree::JanetTree()
    : Root(0)
{
}

JanetTree::~JanetTree()
{
    Clear();
    delete Root;
}

const Triple* JanetTree::Find(const Monom& monom) const
{
    const Triple* triple = 0;

    if (Root)
    {
        ConstIterator nodeIterator = Root;
        Monom::Integer degree = monom.Degree();
        Monom::Integer var = 0;
        do
        {
            if (nodeIterator.GetDegree() != monom[var] && nodeIterator.HasNextDegree())
            {
                nodeIterator.StepNextDegree();
            }

            if (nodeIterator.GetDegree() != monom[var])
            {
                break;
            }
            else if (nodeIterator.HasNextVariable())
            {
                degree -= monom[var];
                if (!degree)
                {
                    break;
                }
                ++var;
                nodeIterator.StepNextVariable();
            }
            else
            {
                triple = nodeIterator.GetTriple();
                break;
            }
        } while(true);
    }
    return triple;
}

void JanetTree::Delete(const Triple *triple)
{
    if (!triple)
    {
        return;
    }

    Iterator nodeIterator = Root;
    //count bifurcations
    Monom::Integer var = 0;
    unsigned bifurcations = 0;

    if (nodeIterator.HasNextDegree() && nodeIterator.HasNextVariable())
    {
        ++bifurcations;
    }

    do
    {
        while(nodeIterator.GetDegree() < triple->GetPolyLm()[var])
        {
            nodeIterator.StepNextDegree();
            if (nodeIterator.HasNextDegree() && nodeIterator.HasNextVariable())
            {
                ++bifurcations;
            }
        }

        if (nodeIterator.HasNextVariable())
        {
            ++var;
            nodeIterator.StepNextVariable();
            if (nodeIterator.HasNextDegree() && nodeIterator.HasNextVariable())
            {
                ++bifurcations;
            }
        }
        else
        {
            break;
        }
    } while(true);

    //deletion
    nodeIterator = Root;
    var = 0;
    bool varDirection = false;

    if (nodeIterator.HasNextDegree() && nodeIterator.HasNextVariable())
    {
        --bifurcations;
    }
    if (!bifurcations)
    {
        if (nodeIterator.GetDegree() < triple->GetPolyLm()[var])
        {
            nodeIterator.StepNextDegree();
        }
        else
        {
            varDirection = true;
        }
    }

    while (bifurcations > 0)
    {
        while(nodeIterator.GetDegree() < triple->GetPolyLm()[var] && bifurcations > 0)
        {
            nodeIterator.StepNextDegree();
            if (nodeIterator.HasNextDegree() && nodeIterator.HasNextVariable())
            {
                --bifurcations;
            }
        }

        if (!bifurcations)
        {
            if (nodeIterator.GetDegree() < triple->GetPolyLm()[var])
            {
                nodeIterator.StepNextDegree();
                break;
            }
            else
            {
                varDirection = true;
                break;
            }
        }

        ++var;
        nodeIterator.StepNextVariable();
        if (nodeIterator.HasNextDegree() && nodeIterator.HasNextVariable())
        {
            --bifurcations;
        }
        if (!bifurcations)
        {
            if (nodeIterator.GetDegree() < triple->GetPolyLm()[var])
            {
                nodeIterator.StepNextDegree();
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
        Iterator tmpIterator = nodeIterator;
        tmpIterator.StepNextVariable();
        tmpIterator.Clear();
        nodeIterator.Delete();
    }
    else
    {
        nodeIterator.Clear();
    }
}

void JanetTree::Insert(Triple* triple)
{
    if (!triple)
    {
        return;
    }

    Monom::Integer degree = triple->GetPolyLm().Degree();
    JanetTree::Iterator nodeIterator(Root);

    if (!Root)
    {
        nodeIterator.Build(degree, 0, triple);
    }
    else
    {
        Monom::Integer var = 0;
        do
        {
            while(nodeIterator.GetDegree() < triple->GetPolyLm()[var] && nodeIterator.HasNextDegree())
            {
                nodeIterator.StepNextDegree();
            }

            if (nodeIterator.GetDegree() > triple->GetPolyLm()[var])
            {
                nodeIterator.Build(degree, var, triple);
                break;
            }
            else if (nodeIterator.GetDegree() == triple->GetPolyLm()[var])
            {
                degree -= triple->GetPolyLm()[var];
                ++var;
                nodeIterator.StepNextVariable();
            }
            else
            {
                nodeIterator.StepNextDegree();
                nodeIterator.Build(degree, var, triple);
                break;
            }
        } while(true);
    }
}

void JanetTree::Clear()
{
    if (Root)
    {
        JanetTree::Iterator nodeIterator(Root);
        nodeIterator.Clear();
    }
}

std::set<Monom::Integer> JanetTree::NonMulti(const Triple* triple) const
{
    std::set<Monom::Integer> result;

    if (triple && Root)
    {
        ConstIterator nodeIterator(Root);
        Monom::Integer var = 0;
        do
        {
            while (nodeIterator.GetDegree() < triple->GetPolyLm()[var])
            {
                nodeIterator.StepNextDegree();
            }
            if (nodeIterator.HasNextDegree())
            {
                result.insert(var);
            }

            ++var;
            if (nodeIterator.HasNextVariable())
            {
                nodeIterator.StepNextVariable();
            }
            else
            {
                break;
            }
        } while(true);
    }

    return result;
}
