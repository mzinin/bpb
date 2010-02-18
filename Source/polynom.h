#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>

#include "monom.h"
#include "allocator.h"


class Polynom
{
protected:
    static Allocator pAllocator;
    Monom* pListHead;

protected:
    void Additive(std::istream& in);
    void Multiplicative(std::istream& in);
    void Unary(std::istream& in);
    void Bracket(std::istream& in);
    const Monom * const * Find(const Monom& monom) const;

public:
    Polynom();
    Polynom(const Polynom& anotherPolynom);
    ~Polynom();

    void SetOne();
    void SetZero();
    bool IsZero() const;
    unsigned long Length() const;
    Monom::Integer Degree() const;
    const Monom& Lm() const;
    void RidOfLm();

    void Reduction(const Polynom& anotherPolynom);
    void HeadReduction(const Polynom& anotherPolynom);
    void MergeWith(Polynom& anotherPolynom);

    void* operator new(std::size_t);
    void operator delete(void *ptr);

    const Polynom& operator=(const Polynom& anotherPolynom);
    const Polynom& operator+=(const Monom& newMonom);
    const Polynom& operator+=(const Polynom& anotherPolynom);

    const Polynom& operator*=(Monom::Integer var);
    const Polynom& operator*=(const Monom& anotherMonom);
    const Polynom& operator*=(const Polynom& anotherPolynom);

    bool operator==(const Polynom &anotherPolynom) const;
    bool operator!=(const Polynom &anotherPolynom) const;

    friend std::ostream& operator<<(std::ostream& out, const Polynom& a);
    friend std::istream& operator>>(std::istream& in, Polynom& a);

    bool operator<(const Polynom& anotherPolynom) const;
    bool operator>(const Polynom& anotherPolynom) const;
    static int Compare(const Polynom& polynomA, const Polynom& polynomB);

    std::string ToString() const;
};

inline Polynom::Polynom(): pListHead(NULL)
{
}

inline Polynom::Polynom(const Polynom& anotherPolynom):
        pListHead(NULL)
{
    if (anotherPolynom.pListHead == NULL)
    {
        return;
    }
    else
    {
        Monom **iterator = &pListHead,
              *iteratorAnother = anotherPolynom.pListHead;
        while (iteratorAnother != NULL)
        {
            *iterator = new Monom(*iteratorAnother);

            iterator = &((*iterator)->mNext);
            iteratorAnother = iteratorAnother->mNext;
        }
    }
}

inline Polynom::~Polynom()
{
    SetZero();
}

inline const Monom * const * Polynom::Find(const Monom& monom) const
{
    if (pListHead == NULL || *pListHead < monom)
    {
        return NULL;
    }

    Monom * const *previousPointer = &pListHead,
          * const *currentPointer;
    unsigned long range(Length()), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register unsigned long i = 0; i < middle; i++)
        {
            currentPointer = &((*currentPointer)->mNext);
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
    //return &((*previousPointer)->mNext);
    return previousPointer;
}

inline void Polynom::SetOne()
{
    SetZero();
    pListHead = new Monom();
}

inline void Polynom::SetZero()
{
    if (pListHead != NULL)
    {
        Monom* tmpMonom;
        while (pListHead != NULL)
        {
            tmpMonom = pListHead;
            pListHead = pListHead->mNext;
            delete tmpMonom;
        }
    }
}

inline bool Polynom::IsZero() const
{
    return pListHead == NULL;
}

inline unsigned long Polynom::Length() const
{
    unsigned long length = 0;
    Monom* iterator(pListHead);
    while (iterator != NULL)
    {
        iterator = iterator->mNext;
        length++;
    }
    return length;
}

inline Monom::Integer Polynom::Degree() const
{
    if (pListHead == NULL)
    {
        return 0;
    }
    else
    {
        return pListHead->Degree();
    }
}

inline const Monom& Polynom::Lm() const
{
    if (pListHead != NULL)
    {
        return *pListHead;
    }
    else
    {
        static Monom nullMonom = Monom();
        return nullMonom;
    }
}

inline void Polynom::RidOfLm()
{
    if (pListHead != NULL)
    {
        Monom* tmpMonom(pListHead);
        pListHead = pListHead->mNext;
        delete tmpMonom;
    }
}

inline void* Polynom::operator new(std::size_t)
{
    return pAllocator.allocate();
}

inline void Polynom::operator delete(void *ptr)
{
    pAllocator.deallocate(ptr);
}

inline const Polynom& Polynom::operator=(const Polynom& anotherPolynom)
{
    if (anotherPolynom.pListHead == NULL)
    {
        SetZero();
    }
    else
    {
        Monom *iteratorAnother = anotherPolynom.pListHead,
              **iterator = &pListHead;
        while (*iterator != NULL && iteratorAnother != NULL)
        {
            **iterator = *iteratorAnother;
            iterator = &((*iterator)->mNext);
            iteratorAnother = iteratorAnother->mNext;
        }

        if (*iterator != NULL)
        {
            Monom* monomToDelete = (*iterator)->mNext;
            *iterator = NULL;
            while (monomToDelete != NULL)
            {
                iteratorAnother = monomToDelete;
                monomToDelete = monomToDelete->mNext;
                delete iteratorAnother;
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

inline bool Polynom::operator==(const Polynom &anotherPolynom) const
{
    Monom *iterator(pListHead),
          *anotherIterator(anotherPolynom.pListHead);
    while (iterator != NULL && anotherIterator != NULL)
    {
        if (*iterator != *anotherIterator)
        {
            break;
        }
        iterator = iterator->mNext;
        anotherIterator = anotherIterator->mNext;
    }
    return iterator == NULL && anotherIterator == NULL;
}

inline bool Polynom::operator!=(const Polynom &anotherPolynom) const
{
    Monom *iterator(pListHead),
          *anotherIterator(anotherPolynom.pListHead);
    while (iterator != NULL && anotherIterator != NULL)
    {
        if (*iterator != *anotherIterator)
        {
            break;
        }
        iterator = iterator->mNext;
        anotherIterator = anotherIterator->mNext;
    }
    return iterator != NULL || anotherIterator != NULL;
}

inline bool Polynom::operator<(const Polynom& anotherPolynom) const
{
    Monom *iterator(pListHead),
          *anotherIterator(anotherPolynom.pListHead);
    while (iterator != NULL && anotherIterator != NULL)
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
                iterator = iterator->mNext;
                anotherIterator = anotherIterator->mNext;
                break;
        }
    }
    return iterator == NULL && anotherIterator != NULL;
}

inline bool Polynom::operator>(const Polynom& anotherPolynom) const
{
    Monom *iterator(pListHead),
          *anotherIterator(anotherPolynom.pListHead);
    while (iterator != NULL && anotherIterator != NULL)
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
                iterator = iterator->mNext;
                anotherIterator = anotherIterator->mNext;
                break;
        }
    }
    return iterator != NULL && anotherIterator == NULL;
}

inline int Polynom::Compare(const Polynom& polynomA, const Polynom& polynomB)
{
    Monom *iteratorA(polynomA.pListHead),
          *iteratorB(polynomB.pListHead);
    while (iteratorA != NULL && iteratorB != NULL)
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
                iteratorA = iteratorA->mNext;
                iteratorB = iteratorB->mNext;
                break;
        }
    }

    if (iteratorA != NULL)
    {
        return 1;
    }
    else if (iteratorB != NULL)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

#endif // POLYNOM_H
