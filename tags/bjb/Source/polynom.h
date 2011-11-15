#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <string>
#include "fast_allocator.h"
#include "monom.h"

class Polynom
{
public:
    Polynom();
    Polynom(const Polynom& anotherPolynom);
    Polynom(const std::string& str);
    ~Polynom();

    void SetOne();
    void SetZero();
    bool IsZero() const;
    bool IsBinomial() const;

    unsigned long Length() const;
    Monom::Integer Degree() const;
    const Monom& Lm() const;
    void RidOfLm();

    void* operator new(std::size_t);
    void operator delete(void *ptr);

    const Polynom& operator=(const Polynom& anotherPolynom);
    const Polynom& operator+=(const Monom& newMonom);
    const Polynom& operator+=(const Polynom& anotherPolynom);

    void Multiply(Monom::Integer var, Monom::Integer degree);
    void Multiply(const Monom& anotherMonom);
    void Multiply(const Polynom& anotherPolynom);

    bool operator==(const Polynom &anotherPolynom) const;
    bool operator!=(const Polynom &anotherPolynom) const;
    bool operator<(const Polynom& anotherPolynom) const;
    bool operator>(const Polynom& anotherPolynom) const;
    static int Compare(const Polynom& polynomA, const Polynom& polynomB);

    void Reduction(const Polynom& anotherPolynom);
    void HeadReduction(const Polynom& anotherPolynom);

    std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom);
    friend std::istream& operator>>(std::istream& in, Polynom& polynom);

private:
    void Additive(std::istream& in);
    void Multiplicative(std::istream& in);
    void Unary(std::istream& in);
    void Power(std::istream& in);
    void Bracket(std::istream& in);

    const Monom * const * Find(const Monom& monom) const;
    void MergeWith(Polynom& anotherPolynom);
    
private:
    Monom* MonomListHead;
    static FastAllocator Allocator;
    static Monom UniteMonom;
};

inline Polynom::Polynom()
    : MonomListHead(0)
{
}

inline Polynom::Polynom(const Polynom& anotherPolynom)
    : MonomListHead(0)
{
    if (!anotherPolynom.MonomListHead)
    {
        return;
    }
    else
    {
        Monom **iterator = &MonomListHead,
               *iteratorAnother = anotherPolynom.MonomListHead;
        while (iteratorAnother)
        {
            *iterator = new Monom(*iteratorAnother);

            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
}

inline Polynom::~Polynom()
{
    SetZero();
}

inline void Polynom::SetOne() 
{
    SetZero();
    MonomListHead = new Monom();
}

inline void Polynom::SetZero() 
{
    if (MonomListHead)
    {
        Monom* tmpMonom = 0;
        while (MonomListHead)
        {
            tmpMonom = MonomListHead;
            MonomListHead = MonomListHead->Next;
            delete tmpMonom;
        }
    }
}

inline bool Polynom::IsZero() const 
{
    return !MonomListHead;
}

inline unsigned long Polynom::Length() const 
{
    unsigned long length = 0;
    Monom* iterator = MonomListHead;
    while (iterator)
    {
        iterator = iterator->Next;
        ++length;
    }
    return length;
}

inline Monom::Integer Polynom::Degree() const 
{
    return MonomListHead ? MonomListHead->Degree() : 0;
}

inline const Monom& Polynom::Lm() const 
{
    return MonomListHead ? *MonomListHead : UniteMonom;
}

inline void Polynom::RidOfLm()
{
    if (MonomListHead)
    {
        Monom* tmpMonom(MonomListHead);
        MonomListHead = MonomListHead->Next;
        delete tmpMonom;
    }
}

inline void* Polynom::operator new(std::size_t) 
{
    return Allocator.Allocate();
}

inline void Polynom::operator delete(void *ptr) 
{
    Allocator.Free(ptr);
}

inline const Polynom& Polynom::operator=(const Polynom& anotherPolynom)
{
    if (!anotherPolynom.MonomListHead)
    {
        SetZero();
    }
    else
    {
        Monom *iteratorAnother = anotherPolynom.MonomListHead,
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
            *iterator = new Monom(*iteratorAnother);
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
    return *this;
}

inline bool Polynom::operator==(const Polynom& anotherPolynom) const
{
    Monom *iterator = MonomListHead,
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

inline bool Polynom::operator!=(const Polynom& anotherPolynom) const
{
    Monom *iterator = MonomListHead,
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

inline bool Polynom::operator<(const Polynom& anotherPolynom) const
{
    Monom *iterator = MonomListHead,
          *anotherIterator = anotherPolynom.MonomListHead;

    while (iterator && anotherIterator)
    {
        switch (Monom::Compare(*iterator, *anotherIterator))
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

inline bool Polynom::operator>(const Polynom& anotherPolynom) const
{
    Monom *iterator = MonomListHead,
          *anotherIterator = anotherPolynom.MonomListHead;

    while (iterator && anotherIterator)
    {
        switch (Monom::Compare(*iterator, *anotherIterator))
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

inline int Polynom::Compare(const Polynom& polynomA, const Polynom& polynomB)
{
    Monom *iteratorA = polynomA.MonomListHead,
          *iteratorB = polynomB.MonomListHead;

    while (iteratorA && iteratorB)
    {
        switch (Monom::Compare(*iteratorA, *iteratorB))
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

inline const Monom * const * Polynom::Find(const Monom& monom) const
{
    if (!MonomListHead || *MonomListHead < monom)
    {
        return 0;
    }

    Monom * const *previousPointer = &MonomListHead,
          * const *currentPointer = 0;
    unsigned long range(Length()), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register unsigned long i = 0; i < middle; ++i)
        {
            currentPointer = &((*currentPointer)->Next);
        }

        switch (Monom::Compare(**currentPointer, monom))
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
