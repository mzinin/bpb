#include <algorithm>
#include <sstream>
#include "polynom.h"

const Polynom& Polynom::operator+=(const Monom& newMonom)
{
    Monom** position = const_cast<Monom**>(Find(newMonom));
    Monom* tmpMonom;

    if (!position)
    {
        tmpMonom = new Monom(newMonom);
        tmpMonom->mNext = MonomListHead;
        MonomListHead = tmpMonom;
    }
    else
    {
        if (*position && **position == newMonom)
        {
            tmpMonom = *position;
            *position = (*position)->mNext;
            delete tmpMonom;
        }
        else
        {
            tmpMonom = new Monom(newMonom);
            tmpMonom->mNext = (*position)->mNext;
            (*position)->mNext = tmpMonom;
        }
    }

    return *this;
}

const Polynom& Polynom::operator+=(const Polynom& anotherPolynom)
{
    if (anotherPolynom.MonomListHead)
    {
        Monom **iterator = &MonomListHead,
              *iteratorAnother = anotherPolynom.MonomListHead,
              *tmpMonom;

        while (*iterator && iteratorAnother)
        {
            switch (Monom::Compare(**iterator, *iteratorAnother))
            {
                case -1:
                    tmpMonom = new Monom(*iteratorAnother);
                    tmpMonom->mNext = *iterator;
                    *iterator = tmpMonom;
                    iterator = &(tmpMonom->mNext);
                    iteratorAnother = iteratorAnother->mNext;
                    break;
                case 0:
                    tmpMonom = *iterator;
                    *iterator = (*iterator)->mNext;
                    delete tmpMonom;
                    iteratorAnother = iteratorAnother->mNext;
                    break;
                case 1:
                    iterator = &((*iterator)->mNext);
                    break;
            }
        }

        while (iteratorAnother)
        {
            *iterator = new Monom(*iteratorAnother);
            iterator = &((*iterator)->mNext);
            iteratorAnother = iteratorAnother->mNext;
        }
    }

    return *this;
}

const Polynom& Polynom::operator*=(Monom::Integer var)
{
    if (MonomListHead)
    {
        Polynom polynomWithVar;
        Monom **iterator = &MonomListHead,
              **iteratorWithVar = &polynomWithVar.MonomListHead;

        while (*iterator)
        {
            if ((**iterator)[var])
            {
                *iteratorWithVar = *iterator;
                *iterator = (*iterator)->mNext;
                (*iteratorWithVar)->mNext = 0;
                iteratorWithVar = &((*iteratorWithVar)->mNext);
            }
            else
            {
                iterator = &((*iterator)->mNext);
            }
        }

        iterator = &MonomListHead;
        while (*iterator)
        {
            **iterator *= var;
            iterator = &((*iterator)->mNext);
        }

        MergeWith(polynomWithVar);
    }

    return *this;
}

const Polynom& Polynom::operator*=(const Monom& anotherMonom)
{
    if (MonomListHead)
    {
        for (register Monom::Integer i = 0; i < anotherMonom.DimIndepend(); ++i)
        {
            if (anotherMonom[i])
            {
                *this *= i;
            }
        }
    }
    return *this;
}

const Polynom& Polynom::operator*=(const Polynom& anotherPolynom)
{
    if (MonomListHead)
    {
        Polynom *tmpPolynom, *tmpResult = new Polynom();
        Monom* iteratorAnother(anotherPolynom.MonomListHead);
        while (iteratorAnother)
        {
            tmpPolynom = new Polynom(*this);
            *tmpPolynom *= *iteratorAnother;
            tmpResult->MergeWith(*tmpPolynom);
            delete tmpPolynom;
            iteratorAnother = iteratorAnother->mNext;
        }
        SetZero();
        MonomListHead = tmpResult->MonomListHead;
        tmpResult->MonomListHead = 0;
        delete tmpResult;
    }
    return *this;
}

void Polynom::Reduction(const Polynom &anotherPolynom)
{
    if (MonomListHead && anotherPolynom.MonomListHead)
    {
        Monom tmpMonom;
        Polynom* tmpPolynom;
        Monom* iterator(MonomListHead);
        const Monom& anotherLm(anotherPolynom.Lm());

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom.SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                *tmpPolynom *= tmpMonom;
                MergeWith(*tmpPolynom);
                delete tmpPolynom;
                iterator = MonomListHead;
            }
            else
            {
                break;
            }
        }

        if (MonomListHead)
        {
            Monom* iterator2(iterator);
            iterator = iterator->mNext;
            while (iterator)
            {
                if (iterator->IsDivisibleBy(anotherLm))
                {
                    tmpMonom.SetQuotientOf(*iterator, anotherLm);
                    tmpPolynom = new Polynom(anotherPolynom);
                    *tmpPolynom *= tmpMonom;
                    MergeWith(*tmpPolynom);
                    delete tmpPolynom;
                    iterator = iterator2->mNext;
                }
                else
                {
                    iterator2 = iterator2->mNext;
                    iterator = iterator2->mNext;
                }
            }
        }
    }
}

void Polynom::HeadReduction(const Polynom &anotherPolynom)
{
    if (MonomListHead && anotherPolynom.MonomListHead)
    {
        Monom tmpMonom;
        Polynom* tmpPolynom;
        Monom* iterator(MonomListHead);
        const Monom& anotherLm(anotherPolynom.Lm());

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom.SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                *tmpPolynom *= tmpMonom;
                MergeWith(*tmpPolynom);
                delete tmpPolynom;
                iterator = MonomListHead;
            }
            else
            {
                break;
            }
        }
    }
}

void Polynom::MergeWith(Polynom& anotherPolynom)
{
    Monom **iterator = &MonomListHead,
          *iteratorAnother = anotherPolynom.MonomListHead,
          *tmpPointer;

    while (*iterator && iteratorAnother)
    {
        switch (Monom::Compare(**iterator, *iteratorAnother))
        {
        case -1:
            tmpPointer = iteratorAnother;
            iteratorAnother = iteratorAnother->mNext;
            tmpPointer->mNext = *iterator;
            *iterator = tmpPointer;
            iterator = &(tmpPointer->mNext);
            break;
        case 0:
            tmpPointer = *iterator;
            *iterator = (*iterator)->mNext;
            delete tmpPointer;
            tmpPointer = iteratorAnother;
            iteratorAnother = iteratorAnother->mNext;
            delete tmpPointer;
            break;
        case 1:
            iterator = &((*iterator)->mNext);
            break;
        }
    }

    if (iteratorAnother)
    {
        *iterator = iteratorAnother;
    }

    anotherPolynom.MonomListHead = 0;
}

std::ostream& operator<<(std::ostream& out, const Polynom& polynom)
{
    if (!polynom.MonomListHead)
    {
        out << "0";
    }
    else
    {
        Monom* iteratorA(polynom.MonomListHead);
        out << *iteratorA;
        iteratorA = iteratorA->mNext;
        while (iteratorA)
        {
            out << " + " << *iteratorA;
            iteratorA = iteratorA->mNext;
        }
    }

    return out;
}

void Polynom::Additive(std::istream& in)
{
    Multiplicative(in);
    int op = (in >> std::ws).peek();
    Polynom tmpPolynom;
    while(op == '+' || op == '-')
    {
        in.get();
        tmpPolynom.Multiplicative(in);
        *this += tmpPolynom;
        op = in.peek();
    }
}

void Polynom::Multiplicative(std::istream& in)
{
    Unary(in);
    int op = (in >> std::ws).peek();
    Polynom tmpPolynom;
    while(op == '*')
    {
        in.get();
        tmpPolynom.Unary(in);
        *this *= tmpPolynom;
        op = in.peek();
    }
}

void Polynom::Unary(std::istream& in)
{
    int ch = (in >> std::ws).peek();
    if (ch != '+' && ch != '-')
    {
        Bracket(in);
    }
    else
    {
        do {
            //ch = in.get();
            ch = (in >> std::ws).peek();
        } while (ch == '+' || ch == '-');
        Bracket(in);
    }
}

void Polynom::Bracket(std::istream& in)
{
    int op = (in >> std::ws).peek();
    if (op == '(')
    {
        in.get();
        Additive(in);
        if (in.get() != ')')
        {
            std::cerr << "expected ')'" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        SetOne();
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
                std::cerr << "expected 'monomial'" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

std::istream& operator>>(std::istream& in, Polynom& polynom)
{
    polynom.Additive(in);
    return in;
}

std::string Polynom::ToString() const
{
    std::stringstream tmpStream;
    tmpStream << *this;
    return tmpStream.str();
}

FastAllocator Polynom::Allocator(sizeof(Polynom));
