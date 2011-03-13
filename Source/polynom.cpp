#include <algorithm>
#include <sstream>
#include "polynom.h"

const Polynom& Polynom::operator+=(const Monom& newMonom)
{
    Monom** position = const_cast<Monom**>(Find(newMonom));
    Monom* tmpMonom = 0;

    if (!position)
    {
        tmpMonom = new Monom(newMonom);
        tmpMonom->Next = MonomListHead;
        MonomListHead = tmpMonom;
    }
    else
    {
        if (*position && **position == newMonom)
        {
            tmpMonom = *position;
            *position = (*position)->Next;
            delete tmpMonom;
        }
        else
        {
            tmpMonom = new Monom(newMonom);
            tmpMonom->Next = (*position)->Next;
            (*position)->Next = tmpMonom;
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
              *tmpMonom = 0;

        while (*iterator && iteratorAnother)
        {
            switch ((**iterator).Compare(*iteratorAnother))
            {
                case -1:
                    tmpMonom = new Monom(*iteratorAnother);
                    tmpMonom->Next = *iterator;
                    *iterator = tmpMonom;
                    iterator = &(tmpMonom->Next);
                    iteratorAnother = iteratorAnother->Next;
                    break;
                case 0:
                    tmpMonom = *iterator;
                    *iterator = (*iterator)->Next;
                    delete tmpMonom;
                    iteratorAnother = iteratorAnother->Next;
                    break;
                case 1:
                    iterator = &((*iterator)->Next);
                    break;
            }
        }

        while (iteratorAnother)
        {
            *iterator = new Monom(*iteratorAnother);
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
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
                *iterator = (*iterator)->Next;
                (*iteratorWithVar)->Next = 0;
                iteratorWithVar = &((*iteratorWithVar)->Next);
            }
            else
            {
                iterator = &((*iterator)->Next);
            }
        }

        iterator = &MonomListHead;
        while (*iterator)
        {
            **iterator *= var;
            iterator = &((*iterator)->Next);
        }

        MergeWith(polynomWithVar);
    }

    return *this;
}

const Polynom& Polynom::operator*=(const Monom& anotherMonom)
{
    if (MonomListHead)
    {
        for (register Monom::Integer i = 0; i < anotherMonom.GetDimIndepend(); ++i)
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
        Polynom *tmpPolynom = 0,
                *tmpResult = new Polynom();
        Monom* iteratorAnother = anotherPolynom.MonomListHead;

        while (iteratorAnother)
        {
            tmpPolynom = new Polynom(*this);
            *tmpPolynom *= *iteratorAnother;
            tmpResult->MergeWith(*tmpPolynom);
            delete tmpPolynom;
            iteratorAnother = iteratorAnother->Next;
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
        std::auto_ptr<Monom> tmpMonom(new Monom());
        Polynom* tmpPolynom = 0;
        Monom* iterator = MonomListHead;
        const Monom& anotherLm = anotherPolynom.Lm();

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom->SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                *tmpPolynom *= *tmpMonom;
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
            Monom* iterator2 = iterator;
            iterator = iterator->Next;
            while (iterator)
            {
                if (iterator->IsDivisibleBy(anotherLm))
                {
                    tmpMonom->SetQuotientOf(*iterator, anotherLm);
                    tmpPolynom = new Polynom(anotherPolynom);
                    *tmpPolynom *= *tmpMonom;
                    MergeWith(*tmpPolynom);
                    delete tmpPolynom;
                    iterator = iterator2->Next;
                }
                else
                {
                    iterator2 = iterator2->Next;
                    iterator = iterator2->Next;
                }
            }
        }
    }
}

void Polynom::HeadReduction(const Polynom &anotherPolynom)
{
    if (MonomListHead && anotherPolynom.MonomListHead)
    {
        std::auto_ptr<Monom> tmpMonom(new Monom());
        Polynom* tmpPolynom = 0;
        Monom* iterator = MonomListHead;
        const Monom& anotherLm = anotherPolynom.Lm();

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom->SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                *tmpPolynom *= *tmpMonom;
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
          *tmpPointer = 0;

    while (*iterator && iteratorAnother)
    {
        switch ((**iterator).Compare(*iteratorAnother))
        {
        case -1:
            tmpPointer = iteratorAnother;
            iteratorAnother = iteratorAnother->Next;
            tmpPointer->Next = *iterator;
            *iterator = tmpPointer;
            iterator = &(tmpPointer->Next);
            break;
        case 0:
            tmpPointer = *iterator;
            *iterator = (*iterator)->Next;
            delete tmpPointer;
            tmpPointer = iteratorAnother;
            iteratorAnother = iteratorAnother->Next;
            delete tmpPointer;
            break;
        case 1:
            iterator = &((*iterator)->Next);
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
        iteratorA = iteratorA->Next;
        while (iteratorA)
        {
            out << " + " << *iteratorA;
            iteratorA = iteratorA->Next;
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
        std::auto_ptr<Monom> tmpMonom(new Monom());
        in >> *tmpMonom;
        if (!in.fail())
        {
            *this *= *tmpMonom;
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
