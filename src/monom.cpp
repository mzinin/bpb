#include "monom.h"

#include <sstream>


FastAllocator Monom::VarsListNode::allocator(sizeof(Monom::VarsListNode));
Variables Monom::independVariables_;
Monom::Integer Monom::dimIndepend_ = 0;


std::string Monom::toString() const
{
    std::stringstream tmpStream;
    tmpStream << *this;
    return tmpStream.str();
}

std::string Monom::innerStructure() const
{
    std::stringstream tmpStream;
    tmpStream << totalDegree_ << "(";

    VarsListNode* iterator = listHead_;
    while (iterator)
    {
        tmpStream << iterator->value << "->";
        iterator = iterator->next;
    }
    tmpStream << ")";

    return tmpStream.str();
}

void Monom::addVariable(const std::string& var)
{
    if (independVariables_.add(var))
    {
        ++dimIndepend_;
    }
}

const std::string& Monom::variable(Integer var)
{
    return independVariables_.variable(var);
}

std::istream& operator>>(std::istream& in, Monom& monom)
{
    std::streampos posbeg = in.tellg();
    int var = monom.independVariables_.read(in);
    if (var < 0)
    {
        in.clear();
        in.setstate(std::ios::failbit);
    }
    else
    {
        monom.setOne();
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
            monom.multiplyBy(var);
            posbeg = in.tellg();
            if (in.peek() != '*')
            {
                var = -1;
            }
            else
            {
                in.get();
                var = monom.independVariables_.read(in);
                if (var < 0)
                {
                    in.clear();
                    in.seekg(posbeg);
                }
            }
        } while (var >= 0);
        if (in.eof() && deg >= 0)
        {
            in.clear();
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Monom& monom)
{
    if (!monom.degree())
    {
        out << '1';
    }
    else
    {
        int i = 0;
        Variables::ConstIterator j(monom.independVariables_.begin());
        while (monom[i] == 0)
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
        while (j != monom.independVariables_.end())
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
