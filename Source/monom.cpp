#include "monom.h"
#include "settings_manager.h"

void Monom::AddVariable(const char *var)
{
    if (IndependVariables->Add(var))
    {
        ++DimIndepend;
    }
}

const char* Monom::GetVariable(Monom::Integer var)
{
    return IndependVariables->Variable(var);
}

std::istream& operator>>(std::istream& in, Monom& a)
{
    std::streampos posbeg = in.tellg();
    int var = a.IndependVariables->Read(in);
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
                var = a.IndependVariables->Read(in);
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

std::ostream& operator<<(std::ostream& out, const Monom& a)
{
    if (!a.Degree())
    {
        out << '1';
    }
    else
    {
        int i = 0;
        Variables::ConstIterator j(a.IndependVariables->Begin());
        while(a[i] == 0)
        {
            ++i;
            ++j;
        }
        out << *j;
        if (a[i] > 1)
        {
            out << '^' << a[i];
        }
        ++i;
        ++j;
        while(j != a.IndependVariables->End())
        {
            if (a[i])
            {
                out << '*' << *j;
                if (a[i] > 1)
                {
                    out << '^' << a[i];
                }
            }
            ++i;
            ++j;
        }
    }
    return out;
}

bool Monom::operator<(const Monom& anotherMonom) const
{
    switch(GetSettingsManager().GetMonomialOrder())
    {
        case Lex:
            return operatorLessLex(anotherMonom);
        case DegLex:
            return operatorLessDegLex(anotherMonom);
        case DegRevLex:
            return operatorLessDegRevLex(anotherMonom);
        default:
            return false;
    };
}

bool Monom::operator>(const Monom& anotherMonom) const
{
    switch(GetSettingsManager().GetMonomialOrder())
    {
        case Lex:
            return operatorMoreLex(anotherMonom);
        case DegLex:
            return operatorMoreDegLex(anotherMonom);
        case DegRevLex:
            return operatorMoreDegRevLex(anotherMonom);
        default:
            return false;
    };
}

int Monom::Compare(const Monom& anotherMonom) const
{
    switch(GetSettingsManager().GetMonomialOrder())
    {
        case Lex:
            return CompareLex(anotherMonom);
        case DegLex:
            return CompareDegLex(anotherMonom);
        case DegRevLex:
            return CompareDegRevLex(anotherMonom);
        default:
            return -1;
    };
}

bool Monom::operatorLessLex(const Monom& anotherMonom) const
{
    VarsListNode *iterator = ListTail,
                 *anotherIterator = anotherMonom.ListTail;
    while (anotherIterator && iterator)
    {
        if (iterator->Value < anotherIterator->Value)
        {
            return false;
        }
        if (iterator->Value > anotherIterator->Value)
        {
            return true;
        }
        iterator = iterator->Previous;
        anotherIterator = anotherIterator->Previous;
    }
    return anotherIterator;
}

bool Monom::operatorLessDegLex(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return true;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = ListTail,
                     *anotherIterator = anotherMonom.ListTail;
        while (anotherIterator)
        {
            if (iterator->Value < anotherIterator->Value)
            {
                return false;
            }
            if (iterator->Value > anotherIterator->Value)
            {
                return true;
            }
            iterator = iterator->Previous;
            anotherIterator = anotherIterator->Previous;
        }
        return false;
    }
}

bool Monom::operatorLessDegRevLex(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return true;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = anotherMonom.ListHead;
        while (anotherIterator)
        {
            if (iterator->Value < anotherIterator->Value)
            {
                return false;
            }
            if (iterator->Value > anotherIterator->Value)
            {
                return true;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return false;
    }
}

bool Monom::operatorMoreLex(const Monom& anotherMonom) const
{
    VarsListNode *iterator = ListTail,
                 *anotherIterator = anotherMonom.ListTail;
    while (anotherIterator && iterator)
    {
        if (iterator->Value < anotherIterator->Value)
        {
            return true;
        }
        if (iterator->Value > anotherIterator->Value)
        {
            return false;
        }
        iterator = iterator->Previous;
        anotherIterator = anotherIterator->Previous;
    }
    return iterator;
}

bool Monom::operatorMoreDegLex(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return false;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = ListTail,
                     *anotherIterator = anotherMonom.ListTail;
        while (anotherIterator)
        {
            if (iterator->Value < anotherIterator->Value)
            {
                return true;
            }
            if (iterator->Value > anotherIterator->Value)
            {
                return false;
            }
            iterator = iterator->Previous;
            anotherIterator = anotherIterator->Previous;
        }
        return false;
    }
}

bool Monom::operatorMoreDegRevLex(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return false;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = anotherMonom.ListHead;
        while (anotherIterator)
        {
            if (iterator->Value < anotherIterator->Value)
            {
                return true;
            }
            if (iterator->Value > anotherIterator->Value)
            {
                return false;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return false;
    }
}

int Monom::CompareLex(const Monom& anotherMonom) const
{
    VarsListNode *iterator = ListTail,
                 *iteratorAnother = anotherMonom.ListTail;
    while (iterator && iteratorAnother)
    {
        if (iterator->Value < iteratorAnother->Value)
        {
            return 1;
        }
        if (iterator->Value > iteratorAnother->Value)
        {
            return -1;
        }
        iterator = iterator->Previous;
        iteratorAnother = iteratorAnother->Previous;
    }

    if (iterator)
    {
        return 1;
    }
    else if (iteratorAnother)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int Monom::CompareDegLex(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return -1;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return 1;
    }
    else
    {
        VarsListNode *iterator = ListTail,
                     *iteratorAnother = anotherMonom.ListTail;
        while (iterator)
        {
            if (iterator->Value < iteratorAnother->Value)
            {
                return 1;
            }
            if (iterator->Value > iteratorAnother->Value)
            {
                return -1;
            }
            iterator = iterator->Previous;
            iteratorAnother = iteratorAnother->Previous;
        }
        return 0;
    }
}

int Monom::CompareDegRevLex(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return -1;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return 1;
    }
    else
    {
        VarsListNode *iterator(ListHead),
                     *iteratorAnother(anotherMonom.ListHead);
        while (iterator)
        {
            if (iterator->Value < iteratorAnother->Value)
            {
                return 1;
            }
            if (iterator->Value > iteratorAnother->Value)
            {
                return -1;
            }
            iterator = iterator->Next;
            iteratorAnother = iteratorAnother->Next;
        }
        return 0;
    }
}

Variables* const Monom::IndependVariables = new Variables();
Monom::Integer Monom::DimIndepend = 0;
FastAllocator Monom::Allocator(sizeof(Monom));
FastAllocator Monom::VarsListNode::Allocator(sizeof(Monom::VarsListNode));
