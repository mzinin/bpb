#include <algorithm>
#include "polynom.h"

const Polynom& Polynom::operator+=(const Monom& newMonom)
{
    Monom** position = const_cast<Monom**>(find(newMonom));
    Monom* tmpMonom;

    if (position == NULL)
    {
        tmpMonom = new Monom(newMonom);
        tmpMonom->mNext = pListHead;
        pListHead = tmpMonom;
    }
    else
    {
        if (*position != NULL && **position == newMonom)
        {
            tmpMonom = *position;
            *position = (*position)->mNext;
            delete tmpMonom;
        }
        else
        {
            //tmpMonom = new Monom(newMonom);
            //tmpMonom->mNext = *position;
            //*position = tmpMonom;
            tmpMonom = new Monom(newMonom);
            tmpMonom->mNext = (*position)->mNext;
            (*position)->mNext = tmpMonom;
        }
    }

    return *this;
}

const Polynom& Polynom::operator+=(const Polynom& anotherPolynom)
{
    if (anotherPolynom.pListHead != NULL)
    {
        Monom **iterator = &pListHead,
              *iteratorAnother = anotherPolynom.pListHead,
              *tmpMonom;

        while (*iterator != NULL && iteratorAnother != NULL)
        {
            switch (Monom::compare(**iterator, *iteratorAnother))
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

        while (iteratorAnother != NULL)
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
    if (pListHead != NULL)
    {
        Polynom polynomWithVar;
        Monom **iterator = &pListHead,
              **iteratorWithVar = &polynomWithVar.pListHead;

        while (*iterator != NULL)
        {
            if ((**iterator)[var])
            {
                *iteratorWithVar = *iterator;
                *iterator = (*iterator)->mNext;
                (*iteratorWithVar)->mNext = NULL;
                iteratorWithVar = &((*iteratorWithVar)->mNext);
            }
            else
            {
                iterator = &((*iterator)->mNext);
            }
        }

        iterator = &pListHead;
        while (*iterator != NULL)
        {
            **iterator *= var;
            iterator = &((*iterator)->mNext);
        }

        mergeWith(polynomWithVar);
    }

    return *this;
}

const Polynom& Polynom::operator*=(const Monom& anotherMonom)
{
    if (pListHead != NULL)
    {
        for (register Monom::Integer i = 0; i < anotherMonom.dimIndepend(); ++i)
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
    if (pListHead != NULL)
    {
        Polynom *tmpPolynom, *tmpResult = new Polynom();
        Monom* iteratorAnother(anotherPolynom.pListHead);
        while (iteratorAnother != NULL)
        {
            tmpPolynom = new Polynom(*this);
            *tmpPolynom *= *iteratorAnother;
            tmpResult->mergeWith(*tmpPolynom);
            delete tmpPolynom;
            iteratorAnother = iteratorAnother->mNext;
        }
        setZero();
        pListHead = tmpResult->pListHead;
        tmpResult->pListHead = 0;
        delete tmpResult;
    }
    return *this;
}

void Polynom::reduction(const Polynom &anotherPolynom)
{
    if (pListHead != NULL && anotherPolynom.pListHead != NULL)
    {
        Monom tmpMonom;
        Polynom* tmpPolynom;
        Monom* iterator(pListHead);
        const Monom& anotherLm(anotherPolynom.lm());

        while (iterator != NULL)
        {
            if (iterator->isDivisibleBy(anotherLm))
            {
                tmpMonom.setQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                *tmpPolynom *= tmpMonom;
                mergeWith(*tmpPolynom);
                delete tmpPolynom;
                iterator = pListHead;
            }
            else
            {
                break;
            }
        }

        if (pListHead != NULL)
        {
            Monom* iterator2(iterator);
            iterator = iterator->mNext;
            while (iterator != NULL)
            {
                if (iterator->isDivisibleBy(anotherLm))
                {
                    tmpMonom.setQuotientOf(*iterator, anotherLm);
                    tmpPolynom = new Polynom(anotherPolynom);
                    *tmpPolynom *= tmpMonom;
                    mergeWith(*tmpPolynom);
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

void Polynom::headReduction(const Polynom &anotherPolynom)
{
    if (pListHead != NULL && anotherPolynom.pListHead != NULL)
    {
        Monom tmpMonom;
        Polynom* tmpPolynom;
        Monom* iterator(pListHead);
        const Monom& anotherLm(anotherPolynom.lm());

        while (iterator != NULL)
        {
            if (iterator->isDivisibleBy(anotherLm))
            {
                tmpMonom.setQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom(anotherPolynom);
                *tmpPolynom *= tmpMonom;
                mergeWith(*tmpPolynom);
                delete tmpPolynom;
                iterator = pListHead;
            }
            else
            {
                break;
            }
        }
    }
}

void Polynom::mergeWith(Polynom& anotherPolynom)
{
    Monom **iterator = &pListHead,
          *iteratorAnother = anotherPolynom.pListHead,
          *tmpPointer;

    while (*iterator != NULL && iteratorAnother != NULL)
    {
        switch (Monom::compare(**iterator, *iteratorAnother))
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

    if (iteratorAnother != NULL)
    {
        *iterator = iteratorAnother;
    }

    anotherPolynom.pListHead = NULL;
}

std::ostream& operator<<(std::ostream& out, const Polynom& a)
{
    if (a.pListHead == NULL)
    {
        out << "0";
    }
    else
    {
        Monom* iteratorA(a.pListHead);
        out << *iteratorA;
        iteratorA = iteratorA->mNext;
        while (iteratorA != NULL)
        {
            out << " + " << *iteratorA;
            iteratorA = iteratorA->mNext;
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
    else if (op == '0')
    {
        return;
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

Allocator Polynom::pAllocator(sizeof(Polynom));
