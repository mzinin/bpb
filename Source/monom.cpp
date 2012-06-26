#include <sstream>
#include "monom.h"

std::string Monom::ToString() const
{
    std::stringstream tmpStream;
    tmpStream << *this;
    return tmpStream.str();
}

std::string Monom::GetInnerStructure() const
{
    std::stringstream tmpStream;
    tmpStream << TotalDegree << "(";

    VarsListNode* iterator = ListHead;
    while (iterator)
    {
        tmpStream << iterator->Value << "->";
        iterator = iterator->Next;
    }
    tmpStream << ")";

    return tmpStream.str();
}

void Monom::AddVariable(const std::string& var)
{
    if (IndependVariables.Add(var))
    {
        ++DimIndepend;
    }
}

const std::string& Monom::GetVariable(Monom::Integer var)
{
    return IndependVariables.Variable(var);
}

std::istream& operator>>(std::istream& in, Monom& monom)
{
    std::streampos posbeg = in.tellg();
    int var = monom.IndependVariables.Read(in);
    if (var < 0)
    {
        in.clear();
        in.setstate(std::ios::failbit);
    }
    else
    {
        monom.SetOne();
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
            monom.MultiplyBy(var);
            posbeg = in.tellg();
            if (in.peek() != '*')
            {
                var = -1;
            }
            else
            {
                in.get();
                var = monom.IndependVariables.Read(in);
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

std::ostream& operator<<(std::ostream& out, const Monom& monom)
{
    if (!monom.Degree())
    {
        out << '1';
    }
    else
    {
        int i = 0;
        Variables::ConstIterator j(monom.IndependVariables.Begin());
        while(monom[i] == 0)
        {
            ++i;
            ++j;
        }
        out << *j;
        if (monom[i] > 1)
        {
            out << '^' << monom[i];
        }
        ++i;
        ++j;
        while(j != monom.IndependVariables.End())
        {
            if (monom[i])
            {
                out << '*' << *j;
                if (monom[i] > 1)
                {
                    out << '^' << monom[i];
                }
            }
            ++i;
            ++j;
        }
    }
    return out;
}

FastAllocator Monom::VarsListNode::Allocator(sizeof(Monom::VarsListNode));
Variables Monom::IndependVariables;
Monom::Integer Monom::DimIndepend = 0;
