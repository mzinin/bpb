#include <algorithm>
#include "polynom.h"

const Polynom& Polynom::operator+=(const Monom& newMonom)
{
    MonomInnerSet::iterator it = lower_bound(monomSet.begin(), monomSet.end(),
                                             &newMonom, monomPointerComparator());
    if (it == monomSet.end() || **it != newMonom)
    {
        monomSet.insert(it, new Monom(newMonom));
    }
    else
    {
        monomSet.erase(it);
    }
    return *this;
}

const Polynom& Polynom::operator+=(const Polynom& anotherPolynom)
{
    MonomInnerSet tmpMonomSet;
    set_symmetric_difference(monomSet.begin(), monomSet.end(),
                             anotherPolynom.monomSet.begin(), anotherPolynom.monomSet.end(),
                             inserter(tmpMonomSet, tmpMonomSet.begin()));
    monomSet = tmpMonomSet;
    return *this;
}

Polynom Polynom::operator+(const Monom& newMonom) const
{
    Polynom tmpPolynom(*this);
    tmpPolynom += newMonom;
    return tmpPolynom;
}

Polynom Polynom::operator+(const Polynom& anotherPolynom) const
{
    Polynom tmpPolynom;
    set_symmetric_difference(monomSet.begin(), monomSet.end(),
                             anotherPolynom.monomSet.begin(), anotherPolynom.monomSet.end(),
                             inserter(tmpPolynom.monomSet, tmpPolynom.monomSet.begin()));
    return tmpPolynom;
}

const Polynom& Polynom::operator*=(Monom::Integer var)
{
    Polynom tmpPolynom;
    Monom tmpMonom;
    MonomInnerSet::const_iterator it;
    for (it = monomSet.begin(); it != monomSet.end(); ++it)
    {
        tmpMonom = **it;
        tmpMonom *= var;
        tmpPolynom += tmpMonom;
    }
    monomSet = tmpPolynom.monomSet;
    tmpPolynom.monomSet.clear();
    return *this;
}

const Polynom& Polynom::operator*=(const Monom& anotherMonom)
{
    Polynom tmpPolynom;
    Monom tmpMonom;
    MonomInnerSet::const_iterator it;
    for (it = monomSet.begin(); it != monomSet.end(); ++it)
    {
        tmpMonom = **it;
        tmpMonom *= anotherMonom;
        tmpPolynom += tmpMonom;
    }
    monomSet = tmpPolynom.monomSet;
    tmpPolynom.monomSet.clear();
    return *this;
}

const Polynom& Polynom::operator*=(const Polynom& anotherPolynom)
{
    Polynom tmpPolynom1, tmpPolynom2;
    MonomInnerSet::const_iterator it;
    for (it = anotherPolynom.monomSet.begin(); it != anotherPolynom.monomSet.end(); ++it)
    {
        tmpPolynom2 = *this;
        tmpPolynom2 *= **it;
        tmpPolynom1 += tmpPolynom2;
    }
    monomSet = tmpPolynom1.monomSet;
    tmpPolynom1.monomSet.clear();
    return *this;
}

Polynom Polynom::operator*(Monom::Integer var) const
{
    Polynom tmpPolynom;
    Monom tmpMonom;
    MonomInnerSet::const_iterator it;
    for (it = monomSet.begin(); it != monomSet.end(); ++it)
    {
        tmpMonom = **it;
        tmpMonom *= var;
        tmpPolynom += tmpMonom;
    }
    return tmpPolynom;
}

Polynom Polynom::operator*(const Monom& anotherMonom) const
{
    Polynom tmpPolynom;
    Monom tmpMonom;
    MonomInnerSet::const_iterator it;
    for (it = monomSet.begin(); it != monomSet.end(); ++it)
    {
        tmpMonom = **it;
        tmpMonom *= anotherMonom;
        tmpPolynom += tmpMonom;
    }
    return tmpPolynom;
}

Polynom Polynom::operator*(const Polynom& anotherPolynom) const
{
    Polynom tmpPolynom1, tmpPolynom2;
    MonomInnerSet::const_iterator it;
    for (it = anotherPolynom.monomSet.begin(); it != anotherPolynom.monomSet.end(); ++it)
    {
        tmpPolynom2 = *this;
        tmpPolynom2 *= **it;
        tmpPolynom1 += tmpPolynom1;
    }
    return tmpPolynom1;
}

void Polynom::reduction(const Polynom &anotherPolynom)
{
    Monom tmpMonom;
    Polynom tmpPolynom;

    MonomInnerSet::const_iterator jIt(monomSet.begin());
    while (jIt != monomSet.end())
    {
        if ((**jIt).isDivisibleBy(anotherPolynom.lm()))
        {
            tmpMonom = **jIt / anotherPolynom.lm();
            tmpPolynom = anotherPolynom;
            tmpPolynom *= tmpMonom;
            *this += tmpPolynom;
            jIt = monomSet.begin();
        }
        else
        {
            break;
        }
    }

    if (isZero())
    {
        return;
    }

    MonomInnerSet::const_iterator iIt(jIt);
    iIt++;

    while (iIt != monomSet.end())
    {
        if ((**iIt).isDivisibleBy(anotherPolynom.lm()))
        {
            tmpMonom = **iIt / anotherPolynom.lm();
            tmpPolynom = anotherPolynom;
            tmpPolynom *= tmpMonom;
            *this += tmpPolynom;
            //iIt = jIt;
            //iIt++;
            iIt = monomSet.begin();
        }
        else
        {
            iIt++;
            //jIt++;
        }
    }
}

void Polynom::headReduction(const Polynom &anotherPolynom)
{
    Monom tmpMonom;
    Polynom tmpPolynom;

    MonomInnerSet::const_iterator jIt(monomSet.begin());
    while (jIt != monomSet.end())
    {
        if ((**jIt).isDivisibleBy(anotherPolynom.lm()))
        {
            tmpMonom = **jIt / anotherPolynom.lm();
            tmpPolynom = anotherPolynom;
            tmpPolynom *= tmpMonom;
            *this += tmpPolynom;
            jIt = monomSet.begin();
        }
        else
        {
            break;
        }
    }
}


std::ostream& operator<<(std::ostream& out, const Polynom& a)
{
    if (a.isZero())
    {
        out << '0';
    }
    else
    {
        Polynom::MonomInnerSet::const_iterator it(a.monomSet.begin());
        if ((**it).degree())
        {
            out << **it;
        }
        else
        {
            out << '1';
        }
        it++;
        while(it != a.monomSet.end())
        {
            out << " + ";
            if ((**it).degree())
            {
                out << **it;
            }
            else
            {
                out << '1';
            }
            it++;
        }
    }
    return out;
}

void Polynom::additive(std::istream& in)
{
    multiplicative(in);
    int op = (in >> std::ws).peek();
    Polynom tmpPolynom;
    while(op == '+' || op == '-')
    {
        in.get();
        tmpPolynom.multiplicative(in);
        *this += tmpPolynom;
        op = in.peek();
    }
}

void Polynom::multiplicative(std::istream& in)
{
    unary(in);
    int op = (in >> std::ws).peek();
    Polynom tmpPolynom;
    while(op == '*')
    {
        in.get();
        tmpPolynom.unary(in);
        *this *= tmpPolynom;
        op = in.peek();
    }
}

void Polynom::unary(std::istream& in)
{
    int ch = (in >> std::ws).peek();
    if (ch != '+' && ch != '-')
    {
        bracket(in);
    }
    else
    {
        do {
            //ch = in.get();
            ch = (in >> std::ws).peek();
        } while (ch == '+' || ch == '-');
        bracket(in);
    }
}

void Polynom::bracket(std::istream& in)
{
    int op = (in >> std::ws).peek();
    if (op == '(')
    {
        in.get();
        additive(in);
        if (in.get() != ')')
        {
            cerr << "expected ')'" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        setOne();
        Monom tmpMonom;
        in >> tmpMonom;
        if (!in.fail())
        {
            *this *= tmpMonom;
        }
        else
        {
            in.clear();
            if (in.get() != '1')
            {
                cerr << "expected 'monomial'" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

std::istream& operator>>(std::istream& in, Polynom& a)
{
    a.additive(in);
    return in;
}
