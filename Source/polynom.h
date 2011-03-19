#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include "fast_allocator.h"

template <typename MonomType>
class Polynom
{
private:
    MonomType* MonomListHead;
    static FastAllocator Allocator;
    static MonomType UniteMonom;

public:
    Polynom();
    Polynom(const Polynom& anotherPolynom);
    ~Polynom();

    void SetOne();
    void SetZero();
    bool IsZero() const;
    unsigned long Length() const;
    typename MonomType::Integer Degree() const;
    const typename MonomType& Lm() const;
    void RidOfLm();

    void* operator new(std::size_t);
    void operator delete(void *ptr);

    const Polynom& operator=(const Polynom& anotherPolynom);
    const Polynom& operator+=(const typename MonomType& newMonom);
    const Polynom& operator+=(const Polynom& anotherPolynom);
    const Polynom& operator*=(typename MonomType::Integer var);
    const Polynom& operator*=(const typename MonomType& anotherMonom);
    const Polynom& operator*=(const Polynom& anotherPolynom);

    bool operator==(const Polynom &anotherPolynom) const;
    bool operator!=(const Polynom &anotherPolynom) const;
    bool operator<(const Polynom& anotherPolynom) const;
    bool operator>(const Polynom& anotherPolynom) const;
    static int Compare(const Polynom& polynomA, const Polynom& polynomB);

    void Reduction(const Polynom& anotherPolynom);
    void HeadReduction(const Polynom& anotherPolynom);
    void MergeWith(Polynom& anotherPolynom);
    std::string ToString() const;

    template <typename MonomType>
    friend std::ostream& operator<<(std::ostream& out, const Polynom<MonomType>& polynom);
    template <typename MonomType>
    friend std::istream& operator>>(std::istream& in, Polynom<MonomType>& polynom);

private:
    void Additive(std::istream& in);
    void Multiplicative(std::istream& in);
    void Unary(std::istream& in);
    void Bracket(std::istream& in);
    const typename MonomType * const * Find(const typename MonomType& monom) const;
};

template <typename MonomType>
FastAllocator Polynom<MonomType>::Allocator(sizeof(Polynom<MonomType>));

template <typename MonomType>
MonomType Polynom<MonomType>::UniteMonom;

template <typename MonomType>
Polynom<MonomType>::Polynom()
    : MonomListHead(0)
{
}

template <typename MonomType>
Polynom<MonomType>::Polynom(const Polynom& anotherPolynom)
    : MonomListHead(0)
{
    if (!anotherPolynom.MonomListHead)
    {
        return;
    }
    else
    {
        MonomType **iterator = &MonomListHead,
                  *iteratorAnother = anotherPolynom.MonomListHead;
        while (iteratorAnother)
        {
            *iterator = new MonomType(*iteratorAnother);

            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
}

template <typename MonomType>
Polynom<MonomType>::~Polynom()
{
    SetZero();
}

template <typename MonomType>
void Polynom<MonomType>::SetOne()
{
    SetZero();
    MonomListHead = new MonomType();
}

template <typename MonomType>
void Polynom<MonomType>::SetZero()
{
    if (MonomListHead)
    {
        MonomType* tmpMonom = 0;
        while (MonomListHead)
        {
            tmpMonom = MonomListHead;
            MonomListHead = MonomListHead->Next;
            delete tmpMonom;
        }
    }
}

template <typename MonomType>
bool Polynom<MonomType>::IsZero() const
{
    return !MonomListHead;
}

template <typename MonomType>
unsigned long Polynom<MonomType>::Length() const
{
    unsigned long length = 0;
    MonomType* iterator = MonomListHead;
    while (iterator)
    {
        iterator = iterator->Next;
        ++length;
    }
    return length;
}

template <typename MonomType>
typename MonomType::Integer Polynom<MonomType>::Degree() const
{
    if (!MonomListHead)
    {
        return 0;
    }
    else
    {
        return MonomListHead->Degree();
    }
}

template <typename MonomType>
const typename MonomType& Polynom<MonomType>::Lm() const
{
    if (MonomListHead)
    {
        return *MonomListHead;
    }
    else
    {
        return UniteMonom;
    }
}

template <typename MonomType>
void Polynom<MonomType>::RidOfLm()
{
    if (MonomListHead)
    {
        Monom* tmpMonom(MonomListHead);
        MonomListHead = MonomListHead->Next;
        delete tmpMonom;
    }
}

template <typename MonomType>
void* Polynom<MonomType>::operator new(std::size_t)
{
    return Allocator.Allocate();
}

template <typename MonomType>
void Polynom<MonomType>::operator delete(void *ptr)
{
    Allocator.Free(ptr);
}

template <typename MonomType>
const Polynom<MonomType>& Polynom<MonomType>::operator=(const Polynom<MonomType>& anotherPolynom)
{
    if (!anotherPolynom.MonomListHead)
    {
        SetZero();
    }
    else
    {
        MonomType *iteratorAnother = anotherPolynom.MonomListHead,
                  **iterator = &MonomListHead;
        while (*iterator && iteratorAnother)
        {
            **iterator = *iteratorAnother;
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }

        if (*iterator)
        {
            Monom* monomToDelete = (*iterator)->Next;
            *iterator = 0;
            while (monomToDelete)
            {
                iteratorAnother = monomToDelete;
                monomToDelete = monomToDelete->Next;
                delete iteratorAnother;
            }
        }

        while (iteratorAnother)
        {
            *iterator = new MonomType(*iteratorAnother);
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
    return *this;
}

template <typename MonomType>
const Polynom<MonomType>& Polynom<MonomType>::operator+=(const typename MonomType& newMonom)
{
    MonomType** position = const_cast<MonomType**>(Find(newMonom));
    MonomType* tmpMonom = 0;

    if (!position)
    {
        tmpMonom = new MonomType(newMonom);
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
            tmpMonom = new MonomType(newMonom);
            tmpMonom->Next = (*position)->Next;
            (*position)->Next = tmpMonom;
        }
    }

    return *this;
}

template <typename MonomType>
const Polynom<MonomType>& Polynom<MonomType>::operator+=(const Polynom<MonomType>& anotherPolynom)
{
    if (anotherPolynom.MonomListHead)
    {
        MonomType **iterator = &MonomListHead,
                  *iteratorAnother = anotherPolynom.MonomListHead,
                  *tmpMonom = 0;

        while (*iterator && iteratorAnother)
        {
            switch ((**iterator).Compare(*iteratorAnother))
            {
                case -1:
                    tmpMonom = new MonomType(*iteratorAnother);
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
            *iterator = new MonomType(*iteratorAnother);
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }

    return *this;
}

template <typename MonomType>
const Polynom<MonomType>& Polynom<MonomType>::operator*=(typename MonomType::Integer var)
{
    if (MonomListHead)
    {
        Polynom<MonomType> polynomWithVar;
        MonomType **iterator = &MonomListHead,
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

template <typename MonomType>
const Polynom<MonomType>& Polynom<MonomType>::operator*=(const typename MonomType& anotherMonom)
{
    if (MonomListHead)
    {
        for (register MonomType::Integer i = 0; i < anotherMonom.GetDimIndepend(); ++i)
        {
            if (anotherMonom[i])
            {
                *this *= i;
            }
        }
    }
    return *this;
}

template <typename MonomType>
const Polynom<MonomType>& Polynom<MonomType>::operator*=(const Polynom<MonomType>& anotherPolynom)
{
    if (MonomListHead)
    {
        Polynom<MonomType> *tmpPolynom = 0,
                           *tmpResult = new Polynom<MonomType>();
        MonomType* iteratorAnother = anotherPolynom.MonomListHead;

        while (iteratorAnother)
        {
            tmpPolynom = new Polynom<MonomType>(*this);
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

template <typename MonomType>
bool Polynom<MonomType>::operator==(const Polynom<MonomType>& anotherPolynom) const
{
    MonomType *iterator = MonomListHead,
              *anotherIterator = anotherPolynom.MonomListHead;

    while (iterator && anotherIterator)
    {
        if (*iterator != *anotherIterator)
        {
            break;
        }
        iterator = iterator->Next;
        anotherIterator = anotherIterator->Next;
    }
    return !iterator && !anotherIterator;
}

template <typename MonomType>
bool Polynom<MonomType>::operator!=(const Polynom<MonomType>& anotherPolynom) const
{
    MonomType *iterator = MonomListHead,
              *anotherIterator = anotherPolynom.MonomListHead;

    while (iterator && anotherIterator)
    {
        if (*iterator != *anotherIterator)
        {
            break;
        }
        iterator = iterator->Next;
        anotherIterator = anotherIterator->Next;
    }
    return iterator || anotherIterator;
}

template <typename MonomType>
bool Polynom<MonomType>::operator<(const Polynom<MonomType>& anotherPolynom) const
{
    MonomType *iterator = MonomListHead,
              *anotherIterator = anotherPolynom.MonomListHead;

    while (iterator && anotherIterator)
    {
        switch ((*iterator).Compare(*anotherIterator))
        {
            case -1:
                return true;
                break;
            case 1:
                return false;
                break;
            case 0:
                iterator = iterator->Next;
                anotherIterator = anotherIterator->Next;
                break;
        }
    }
    return !iterator && !anotherIterator;
}

template <typename MonomType>
bool Polynom<MonomType>::operator>(const Polynom<MonomType>& anotherPolynom) const
{
    MonomType *iterator = MonomListHead,
              *anotherIterator = anotherPolynom.MonomListHead;

    while (iterator && anotherIterator)
    {
        switch ((*iterator).Compare(*anotherIterator))
        {
            case -1:
                return false;
                break;
            case 1:
                return true;
                break;
            case 0:
                iterator = iterator->Next;
                anotherIterator = anotherIterator->Next;
                break;
        }
    }
    return iterator && !anotherIterator;
}

template <typename MonomType>
int Polynom<MonomType>::Compare(const Polynom<MonomType>& polynomA, const Polynom<MonomType>& polynomB)
{
    MonomType *iteratorA = polynomA.MonomListHead,
              *iteratorB = polynomB.MonomListHead;

    while (iteratorA && iteratorB)
    {
        switch ((*iteratorA).Compare(*iteratorB))
        {
            case -1:
                return -1;
                break;
            case 1:
                return 1;
                break;
            case 0:
                iteratorA = iteratorA->Next;
                iteratorB = iteratorB->Next;
                break;
        }
    }

    if (iteratorA)
    {
        return 1;
    }
    else if (iteratorB)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

template <typename MonomType>
void Polynom<MonomType>::Reduction(const Polynom<MonomType>& anotherPolynom)
{
    if (MonomListHead && anotherPolynom.MonomListHead)
    {
        MonomType* tmpMonom = new MonomType();
        Polynom<MonomType>* tmpPolynom = 0;
        MonomType* iterator = MonomListHead;
        const MonomType& anotherLm = anotherPolynom.Lm();

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom->SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom<MonomType>(anotherPolynom);
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
            MonomType* iterator2 = iterator;
            iterator = iterator->Next;
            while (iterator)
            {
                if (iterator->IsDivisibleBy(anotherLm))
                {
                    tmpMonom->SetQuotientOf(*iterator, anotherLm);
                    tmpPolynom = new Polynom<MonomType>(anotherPolynom);
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
        delete tmpMonom;
    }
}

template <typename MonomType>
void Polynom<MonomType>::HeadReduction(const Polynom<MonomType>& anotherPolynom)
{
    if (MonomListHead && anotherPolynom.MonomListHead)
    {
        MonomType* tmpMonom = new MonomType();
        Polynom<MonomType>* tmpPolynom = 0;
        MonomType* iterator = MonomListHead;
        const MonomType& anotherLm = anotherPolynom.Lm();

        while (iterator)
        {
            if (iterator->IsDivisibleBy(anotherLm))
            {
                tmpMonom->SetQuotientOf(*iterator, anotherLm);
                tmpPolynom = new Polynom<MonomType>(anotherPolynom);
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
        delete tmpMonom;
    }
}

template <typename MonomType>
void Polynom<MonomType>::MergeWith(Polynom<MonomType>& anotherPolynom)
{
    MonomType **iterator = &MonomListHead,
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

template <typename MonomType>
std::string Polynom<MonomType>::ToString() const
{
    std::stringstream tmpStream;
    tmpStream << *this;
    return tmpStream.str();
}

template <typename MonomType>
std::ostream& operator<<(std::ostream& out, const Polynom<MonomType>& polynom)
{
    if (!polynom.MonomListHead)
    {
        out << "0";
    }
    else
    {
        MonomType* iteratorA(polynom.MonomListHead);
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

template <typename MonomType>
std::istream& operator>>(std::istream& in, Polynom<MonomType>& polynom)
{
    polynom.Additive(in);
    return in;
}

template <typename MonomType>
void Polynom<MonomType>::Additive(std::istream& in)
{
    Multiplicative(in);
    int op = (in >> std::ws).peek();
    Polynom<MonomType> tmpPolynom;
    while(op == '+' || op == '-')
    {
        in.get();
        tmpPolynom.Multiplicative(in);
        *this += tmpPolynom;
        op = in.peek();
    }
}

template <typename MonomType>
void Polynom<MonomType>::Multiplicative(std::istream& in)
{
    Unary(in);
    int op = (in >> std::ws).peek();
    Polynom<MonomType> tmpPolynom;
    while(op == '*')
    {
        in.get();
        tmpPolynom.Unary(in);
        *this *= tmpPolynom;
        op = in.peek();
    }
}

template <typename MonomType>
void Polynom<MonomType>::Unary(std::istream& in)
{
    int ch = (in >> std::ws).peek();
    if (ch != '+' && ch != '-')
    {
        Bracket(in);
    }
    else
    {
        do
        {
            ch = (in >> std::ws).peek();
        } while (ch == '+' || ch == '-');
        Bracket(in);
    }
}

template <typename MonomType>
void Polynom<MonomType>::Bracket(std::istream& in)
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
        MonomType* tmpMonom = new MonomType();
        in >> *tmpMonom;
        if (!in.fail())
        {
            *this *= *tmpMonom;
            delete tmpMonom;
        }
        else
        {
            delete tmpMonom;
            in.clear();
            if (in.get() != '1')
            {
                std::cerr << "expected 'monomial'" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

template <typename MonomType>
const typename MonomType * const * Polynom<MonomType>::Find(const typename MonomType& monom) const
{
    if (!MonomListHead || *MonomListHead < monom)
    {
        return 0;
    }

    MonomType * const *previousPointer = &MonomListHead,
              * const *currentPointer = 0;
    unsigned long range(Length()), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register unsigned long i = 0; i < middle; ++i)
        {
            currentPointer = &((*currentPointer)->Next);
        }

        switch ((**currentPointer).Compare(monom))
        {
        case 1:
            previousPointer = currentPointer;
            range -= middle;
            break;
        case -1:
            range = middle;
            break;
        case 0:
            return currentPointer;
        }
    }

    return previousPointer;
}

#endif // POLYNOM_H
