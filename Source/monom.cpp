#include "monom.h"
#include "monomLex.h"
#include "monomDL.h"
#include "monomDRL.h"
#include "monomOld.h"
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

Monom* Monom::GetNewMonom()
{
    switch(GetSettingsManager().GetMonomialOrder())
    {
        case Lex:
            return new MonomLex();
        case DegLex:
            return new MonomDL();
        case DegRevLex:
            return new MonomDRL();
        case OldDRL:
            return new MonomOld();
        default:
            return 0;
    };
};

Monom* Monom::GetNewMonom(const Monom& anotherMonom)
{
    switch(GetSettingsManager().GetMonomialOrder())
    {
        case Lex:
            return new MonomLex(anotherMonom);
        case DegLex:
            return new MonomDL(anotherMonom);
        case DegRevLex:
            return new MonomDRL(anotherMonom);
        case OldDRL:
            return new MonomOld(anotherMonom);
        default:
            return 0;
    };
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


Variables* const Monom::IndependVariables = new Variables();
Monom::Integer Monom::DimIndepend = 0;
