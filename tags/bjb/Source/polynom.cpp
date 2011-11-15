#include <algorithm>
#include <sstream>
#include <string>
#include "polynom.h"

FastAllocator Polynom::Allocator(sizeof(Polynom));
Monom Polynom::UniteMonom;

Polynom::Polynom(const std::string& str)
    : MonomListHead(0)
{
    std::stringstream tmpStream(str); 
    tmpStream >> *this;
}

bool Polynom::IsBinomial() const 
{
    Monom* iterator1 = MonomListHead;
    if (!iterator1 || iterator1->Degree() != 2)
    {
        return false;
    }
    Monom* iterator2 = iterator1->Next;
    if (!iterator2 || iterator2->Degree() != 1)
    {
        return false;
    }
    return !(iterator2->Next) && iterator1->HasSameOnlyVariable(*iterator2);
}

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
            switch (Monom::Compare(**iterator, *iteratorAnother))
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

void Polynom::Multiply(Monom::Integer var, Monom::Integer degree)
{
    if (MonomListHead)
    {
        Monom* iterator = MonomListHead;
        while (iterator)
        {
            iterator->Prolong(var, degree);
            iterator = iterator->Next;
        }
    }
}

void Polynom::Multiply(const Monom& anotherMonom)
{
    if (MonomListHead)
    {
        Monom* iterator = MonomListHead;
        while (iterator)
        {
            iterator->Multiply(anotherMonom);
            iterator = iterator->Next;
        }
    }
}

void Polynom::Multiply(const Polynom& anotherPolynom)
{
    if (MonomListHead)
    {
        Polynom *tmpPolynom = 0, 
                *tmpResult = new Polynom();
        Monom* iteratorAnother = anotherPolynom.MonomListHead;

        while (iteratorAnother)
        {
            tmpPolynom = new Polynom(*this);
            tmpPolynom->Multiply(*iteratorAnother);
            tmpResult->MergeWith(*tmpPolynom);
            delete tmpPolynom;
            iteratorAnother = iteratorAnother->Next;
        }
        SetZero();
        MonomListHead = tmpResult->MonomListHead;
        tmpResult->MonomListHead = 0;
        delete tmpResult;
    }
}

void Polynom::Reduction(const Polynom& anotherPolynom) 
{
    if (MonomListHead && anotherPolynom.MonomListHead)
    {
        Monom* tmpMonom = new Monom();
        Polynom* tmpPolynom = 0;
        Monom* iterator = MonomListHead;
        const Monom& anotherLm = anotherPolynom.Lm();

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom->SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                tmpPolynom->Multiply(*tmpMonom);
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
                    tmpPolynom->Multiply(*tmpMonom);
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
        delete tmpMonom;
    }
}

void Polynom::HeadReduction(const Polynom& anotherPolynom) 
{
    if (MonomListHead && anotherPolynom.MonomListHead)
    {
        Monom* tmpMonom = new Monom();
        Polynom* tmpPolynom = 0;
        Monom* iterator = MonomListHead;
        const Monom& anotherLm = anotherPolynom.Lm();

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom->SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                tmpPolynom->Multiply(*tmpMonom);
                MergeWith(*tmpPolynom);
                delete tmpPolynom;
                iterator = MonomListHead;
            }
            else
            {
                break;
            }
        }
        delete tmpMonom;
    }
}

void Polynom::MergeWith(Polynom& anotherPolynom)
{
    Monom **iterator = &MonomListHead,
           *iteratorAnother = anotherPolynom.MonomListHead,
           *tmpPointer = 0;

    while (*iterator && iteratorAnother)
    {
        switch (Monom::Compare(**iterator, *iteratorAnother))
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

std::string Polynom::ToString() const
{
    std::stringstream tmpStream; 
    tmpStream << *this;
    return tmpStream.str();
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

std::istream& operator>>(std::istream& in, Polynom& polynom) 
{
    polynom.Additive(in);
    return in;
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
        Multiply(tmpPolynom);
        op = in.peek();
    }
}

void Polynom::Unary(std::istream& in) 
{
    int ch = (in >> std::ws).peek();
    if (ch != '+' && ch != '-') 
    {
        Power(in);
    }
    else 
    {
        do 
        {
            ch = (in >> std::ws).peek();
        } while (ch == '+' || ch == '-');
        Power(in);
    }
}

void Polynom::Power(std::istream& in)
{
    Bracket(in);
    int op = (in >> std::ws).peek();
    if (op == '^')
    {
        in.get();
        int degree = 0;
        in >> std::ws >> degree;
        if (in.fail() || degree <= 0)
        {
            std::cerr << "expected 'degree > 0'" << std::endl;
        }
        for (register int i = 1; i < degree; ++i)
        {
            Multiply(*this);
        }
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
        Monom* tmpMonom = new Monom();
        in >> *tmpMonom;
        if (!in.fail())
        {
            this->Multiply(*tmpMonom);
            delete tmpMonom;
        }
        else 
        {
            delete tmpMonom;
            in.clear();
            op = in.get();
            if (op == '0') 
            {
                SetZero();
            }
            else if (op != '1') 
            {
                std::cerr << "expected 'monomial'" << std::endl;
                exit(EXIT_FAILURE); 
            }
        }
    }
}
