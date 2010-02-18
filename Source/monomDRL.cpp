#include <string>
#include "monomDRL.h"

void MonomDRL::AddVariable(const char *var)
{
    if (mIndepend->Add(var))
    {
        mDimIndepend++;
    }
}

const char* MonomDRL::GetVariable(MonomDRL::Integer var)
{
    return mIndepend->Variable(var);
}

std::istream& operator>>(std::istream& in, MonomDRL& a)
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
                    IMESSAGE("expected 'degree >= 0'");
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
            in.clear();
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const MonomDRL& a)
{
    if (a.mListHead == NULL)
    {
        out << "1";
    }
    else
    {
        std::string monomString;
        MonomDRL::VarsListNode* iteratorA(a.mListHead);
        monomString.insert(0, a.mIndepend->Variable(iteratorA->value));
        iteratorA = iteratorA->next;
        while (iteratorA != NULL)
        {
            monomString.insert(0, "*");
            monomString.insert(0, a.mIndepend->Variable(iteratorA->value));
            iteratorA = iteratorA->next;
        }
        out << monomString;
    }

    return out;
}

int MonomDRL::Compare(const MonomDRL& monomA, const MonomDRL& monomB)
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
        while (iteratorA != NULL)
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

Variables* MonomDRL::mIndepend = new Variables();
Allocator MonomDRL::mAllocator(sizeof(MonomDRL));
Allocator MonomDRL::VarsListNode::vlnAllocator(sizeof(MonomDRL::VarsListNode));
MonomDRL::Integer MonomDRL::mDimIndepend = 0;
