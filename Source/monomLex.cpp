#include "monomLex.h"

void MonomLex::AddVariable(const char *var)
{
    if (mIndepend->Add(var))
    {
        ++mDimIndepend;
    }
}

const char* MonomLex::GetVariable(MonomLex::Integer var)
{
    return mIndepend->Variable(var);
}

std::istream& operator>>(std::istream& in, MonomLex& a)
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
                var = -1;
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

std::ostream& operator<<(std::ostream& out, const MonomLex& a)
{
    if (!a.mListHead)
    {
        out << "1";
    }
    else
    {
        MonomLex::VarsListNode* iteratorA(a.mListHead);
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

int MonomLex::Compare(const MonomLex& monomA, const MonomLex& monomB)
{
    VarsListNode *iteratorA(monomA.mListHead),
                 *iteratorB(monomB.mListHead);
    while (iteratorA && iteratorB)
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

    if (iteratorA)
    {
        return 1;
    }
    else if (iteratorB)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

Variables* MonomLex::mIndepend = new Variables();
FastAllocator MonomLex::Allocator(sizeof(MonomLex));
FastAllocator MonomLex::VarsListNode::Allocator(sizeof(MonomLex::VarsListNode));
MonomLex::Integer MonomLex::mDimIndepend = 0;
