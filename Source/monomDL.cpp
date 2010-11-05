#include "monomDL.h"

void MonomDL::AddVariable(const char *var)
{
    if (mIndepend->Add(var))
    {
        ++mDimIndepend;
    }
}

const char* MonomDL::GetVariable(MonomDL::Integer var)
{
    return mIndepend->Variable(var);
}

std::istream& operator>>(std::istream& in, MonomDL& a)
{
    std::streampos posbeg = in.tellg();
    int var = a.mIndepend->Read(in);
    if (var < 0)
    {
        in.clear();
        in.setstate(std::ios::failbit);
    }
    else
    {
        a.SetOne();
        int deg;
        do
        {
            deg = 1;
            std::streampos posbeg = in.tellg();
            if ((in >> std::ws).peek() == '^')
            {
                in.get();
                in >> std::ws >> deg;
                if (in.fail() || deg < 0)
                {
                    in.setstate(std::ios::failbit);
                }
            }
            a *= var;
            posbeg = in.tellg();
            if (in.peek() != '*')
            {
                var = -1;
            }
            else
            {
                in.get();
                var = a.mIndepend->Read(in);
                if (var < 0)
                {
                    in.clear();
                    in.seekg(posbeg);
                }
            }
        } while(var >= 0);

        if (in.eof() && deg >= 0)
        {
            in.clear();
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const MonomDL& a)
{
    if (!a.mListHead)
    {
        out << "1";
    }
    else
    {
        MonomDL::VarsListNode* iteratorA(a.mListHead);
        out << a.mIndepend->Variable(iteratorA->value);
        iteratorA = iteratorA->next;
        while (iteratorA)
        {
            out << "*" << a.mIndepend->Variable(iteratorA->value);
            iteratorA = iteratorA->next;
        }
    }

    return out;
}

int MonomDL::Compare(const MonomDL& monomA, const MonomDL& monomB)
{
    if (monomA.mDegree < monomB.mDegree)
    {
        return -1;
    }
    else if (monomA.mDegree > monomB.mDegree)
    {
        return 1;
    }
    else
    {
        VarsListNode *iteratorA(monomA.mListHead),
                     *iteratorB(monomB.mListHead);
        while (iteratorA)
        {
            if (iteratorA->value < iteratorB->value)
            {
                return 1;
            }
            if (iteratorA->value > iteratorB->value)
            {
                return -1;
            }
            iteratorA = iteratorA->next;
            iteratorB = iteratorB->next;
        }
        return 0;
    }
}

Variables* MonomDL::mIndepend = new Variables();
FastAllocator MonomDL::Allocator(sizeof(MonomDL));
FastAllocator MonomDL::VarsListNode::Allocator(sizeof(MonomDL::VarsListNode));
MonomDL::Integer MonomDL::mDimIndepend = 0;
