#include "monom.h"

void Monom::addVariable(const char *var)
{
    if (mIndepend->add(var))
    {
        mDimIndepend++;
    }
}

std::istream& operator>>(std::istream& in, Monom& a)
{
    std::streampos posbeg = in.tellg();
    int var = a.mIndepend->read(in);
    if (var < 0)
    {
        in.clear();
        in.setstate(std::ios::failbit);
    }
    else
    {
        a.setOne();
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
                var = a.mIndepend->read(in);
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

std::ostream& operator<<(std::ostream& out, const Monom& a)
{
    if (a.degree() == 0)
        out << '1';
    else
    {
        int i = 0;
        Variables::ConstIterator j(a.mIndepend->begin());
        while(a[i] == 0)
        {
            ++i;
            ++j;
        }
        out << *j;
        if (a[i] > 1)
            out << '^' << a[i];
        ++i;
        ++j;
        while(j != a.mIndepend->end())
        {
            if (a[i])
            {
                out << '*' << *j;
                if (a[i] > 1)
                    out << '^' << a[i];
            }
            ++i;
            ++j;
        }
    }
    return out;
}

Variables* Monom::mIndepend = new Variables();
Allocator Monom::sAllocator(sizeof(Monom));
Monom::Integer Monom::mDimIndepend = 0;
