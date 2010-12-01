#ifndef MONOMDRL_H
#define MONOMDRL_H

#include <set>

#include "fast_allocator.h"
#include "monom.h"

class MonomDRL : public Monom
{
private:
    struct VarsListNode
    {
        Monom::Integer Value;
        VarsListNode* Next;
        static FastAllocator Allocator;

        VarsListNode();
        VarsListNode(Monom::Integer newValue, VarsListNode*& newNext);
        ~VarsListNode();

        void* operator new(size_t);
        void operator delete(void* ptr);
    };

    VarsListNode* ListHead;
    static FastAllocator Allocator;

    friend class Monom;

private:
    MonomDRL();
    MonomDRL(const Monom& anotherMonom);
    VarsListNode* Find(const Monom::Integer var) const;
    const MonomDRL* CastToMe(const Monom& monom) const;

public:
    ~MonomDRL();

    Monom::Order GetOrder() const;

    void* operator new(std::size_t);
    void operator delete(void* ptr);

    Monom::Integer operator[](Monom::Integer var) const;

    const Monom& operator=(const Monom& anotherMonom);

    const Monom& operator*=(Monom::Integer var);
    const Monom& operator*=(const Monom& anotherMonom);
    void SetProductOf(const Monom& anotherMonom, Monom::Integer var);
    void SetProductOf(const Monom& monomA, const Monom& monomB);

    const Monom& operator/=(const Monom& anotherMonom);
    void SetQuotientOf(const Monom& monomA, const Monom& monomB);

    void SetOne();

    bool operator==(const Monom& anotherMonom) const;
    bool operator!=(const Monom& anotherMonom) const;
    bool operator<(const Monom& anotherMonom) const;
    bool operator>(const Monom& anotherMonom) const;

    bool IsDivisibleBy(const Monom& anotherMonom) const;
    bool IsTrueDivisibleBy(const Monom& anotherMonom) const;
    bool IsPommaretDivisibleBy(const Monom& anotherMonom) const;

    void SetGcdOf(const Monom& monomA, const Monom& monomB);
    void SetLcmOf(const Monom& monomA, const Monom& monomB);

    Monom::Integer FirstMultiVar() const;
    std::set<Monom::Integer> GetVariablesSet() const;

    int Compare(const Monom& anotherMonom);
    Monom::Integer GcdDegree(const Monom& anotherMonom);
    Monom::Integer LcmDegree(const Monom& anotherMonom);
};


inline MonomDRL::VarsListNode::VarsListNode()
    : Value(0)
    , Next(0)
{
}

inline MonomDRL::VarsListNode::VarsListNode(Monom::Integer newValue, VarsListNode*& newNext)
    : Value(newValue)
    , Next(newNext)
{
}

inline MonomDRL::VarsListNode::~VarsListNode()
{
}

inline void* MonomDRL::VarsListNode::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void MonomDRL::VarsListNode::operator delete(void* ptr)
{
    Allocator.Free(ptr);
}

inline MonomDRL::MonomDRL()
    : Monom()
    , ListHead(0)
{
}

inline MonomDRL::MonomDRL(const Monom& anotherMonom)
    : Monom()
    , ListHead(0)
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (!castedAnotherMonom->ListHead)
    {
        return;
    }
    else
    {
        TotalDegree = castedAnotherMonom->TotalDegree;
        VarsListNode **iterator = &ListHead,
                     *iteratorAnother = castedAnotherMonom->ListHead;
        while (iteratorAnother)
        {
            *iterator = new VarsListNode();
            (*iterator)->Value = iteratorAnother->Value;

            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
}

inline MonomDRL::VarsListNode* MonomDRL::Find(const Monom::Integer var) const
{
    if (!ListHead || ListHead->Value < var)
    {
        return 0;
    }

    VarsListNode *previousPointer(ListHead), *currentPointer;
    Monom::Integer range(TotalDegree), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register Monom::Integer i = 0; i < middle; ++i)
        {
            currentPointer = currentPointer->Next;
        }

        if (currentPointer->Value > var)
        {
            previousPointer = currentPointer;
            range -= middle;
        }
        else if (currentPointer->Value < var)
        {
            range = middle;
        }
        else
        {
            return currentPointer;
        }
    }
    return previousPointer;
}

inline const MonomDRL* MonomDRL::CastToMe(const Monom& monom) const
{
    if (monom.GetOrder() != GetOrder())
    {
        throw 1;
    }
    return static_cast<const MonomDRL*>(&monom);
}

inline MonomDRL::~MonomDRL()
{
    SetOne();
}

inline Monom::Order MonomDRL::GetOrder() const
{
    return Monom::DegRevLex;
}

inline void* MonomDRL::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void MonomDRL::operator delete(void* ptr)
{
    Allocator.Free(ptr);
}

inline Monom::Integer MonomDRL::operator[](Monom::Integer var) const
{
    if (!ListHead || ListHead->Value < var)
    {
        return 0;
    }

    VarsListNode *previousPointer(ListHead), *currentPointer;
    Monom::Integer range(TotalDegree), middle;

    while (range > 0)
    {
        middle = range >> 1;
        currentPointer = previousPointer;
        for (register Monom::Integer i = 0; i < middle; ++i)
        {
            currentPointer = currentPointer->Next;
        }

        if (currentPointer->Value > var)
        {
            previousPointer = currentPointer->Next;
            range -= middle + 1;
        }
        else if (currentPointer->Value < var)
        {
            range = middle;
        }
        else
        {
            return 1;
        }
    }
    return previousPointer && previousPointer->Value == var;
}

inline const Monom& MonomDRL::operator=(const Monom& anotherMonom)
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);
    if (this == castedAnotherMonom)
    {
        return *this;
    }

    if (!castedAnotherMonom->ListHead)
    {
        SetOne();
    }
    else
    {
        TotalDegree = castedAnotherMonom->TotalDegree;

        VarsListNode *iteratorAnother = castedAnotherMonom->ListHead,
                     **iterator = &ListHead;
        while (*iterator && iteratorAnother)
        {
            (*iterator)->Value = iteratorAnother->Value;
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }

        if (*iterator)
        {
            VarsListNode *nodeToDelete = (*iterator)->Next;
            *iterator = 0;
            while (nodeToDelete)
            {
                iteratorAnother = nodeToDelete;
                nodeToDelete = nodeToDelete->Next;
                delete iteratorAnother;
            }
        }

        if (iteratorAnother)
        {
            while (iteratorAnother)
            {
                *iterator = new VarsListNode();
                (*iterator)->Value = iteratorAnother->Value;

                iterator = &((*iterator)->Next);
                iteratorAnother = iteratorAnother->Next;
            }
        }
    }
    return *this;
}

inline const Monom& MonomDRL::operator*=(Monom::Integer var)
{
    //inserted variable is the only one
    if (!ListHead)
    {
        ListHead = new VarsListNode();
        ListHead->Value = var;
        ++TotalDegree;
    }
    else
    {
        VarsListNode* position = Find(var);
        //inserted variable is the eldest one
        if (!position)
        {
            position = new VarsListNode();
            position->Value = var;
            position->Next = ListHead;
            ListHead = position;
            ++TotalDegree;
        }
        //all other cases
        else if(position->Value != var)
        {
            VarsListNode* newNode = new VarsListNode();
            newNode->Value = var;
            newNode->Next = position->Next;
            position->Next = newNode;
            ++TotalDegree;
        }
    }

    return *this;
}

inline const Monom& MonomDRL::operator*=(const Monom& anotherMonom)
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (!ListHead)
    {
        *this = *castedAnotherMonom;
    }
    else if (castedAnotherMonom->ListHead)
    {
        VarsListNode **iterator = &ListHead,
                     *anotherIterator = castedAnotherMonom->ListHead;

        while (*iterator && anotherIterator)
        {
            if ((*iterator)->Value == anotherIterator->Value)
            {
                iterator = &((*iterator)->Next);
                anotherIterator = anotherIterator->Next;
            }
            else if ((*iterator)->Value > anotherIterator->Value)
            {
                iterator = &((*iterator)->Next);
            }
            else
            {
                VarsListNode* newNode = new VarsListNode();
                newNode->Value = anotherIterator->Value;
                newNode->Next = *iterator;
                *iterator = newNode;
                ++TotalDegree;

                iterator = &(newNode->Next);
                anotherIterator = anotherIterator->Next;
            }
        }

        while (anotherIterator)
        {
            *iterator = new VarsListNode();
            (*iterator)->Value = anotherIterator->Value;
            ++TotalDegree;

            iterator = &((*iterator)->Next);
            anotherIterator = anotherIterator->Next;
        }
    }

    return *this;
}

inline void MonomDRL::SetProductOf(const Monom& monomA, Monom::Integer var)
{
    *this = monomA;
    *this *= var;
}

inline void MonomDRL::SetProductOf(const Monom& monomA, const Monom& monomB)
{
    const MonomDRL* castedMonomA = CastToMe(monomA);
    const MonomDRL* castedMonomB = CastToMe(monomB);

    SetOne();
    VarsListNode **iterator = &ListHead,
                 *iteratorA = castedMonomA->ListHead,
                 *iteratorB = castedMonomB->ListHead;

    while (iteratorA && iteratorB)
    {
        ++TotalDegree;
        *iterator = new VarsListNode();
        if (iteratorA->Value == iteratorB->Value)
        {
            (*iterator)->Value = iteratorA->Value;
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else if (iteratorA->Value > iteratorB->Value)
        {
            (*iterator)->Value = iteratorA->Value;
            iteratorA = iteratorA->Next;
        }
        else
        {
            (*iterator)->Value = iteratorB->Value;
            iteratorB = iteratorB->Next;
        }
        iterator = &((*iterator)->Next);
    }

    while (iteratorA)
    {
        ++TotalDegree;
        *iterator = new VarsListNode();
        (*iterator)->Value = iteratorA->Value;
        iterator = &((*iterator)->Next);
        iteratorA = iteratorA->Next;
    }

    while (iteratorB)
    {
        ++TotalDegree;
        *iterator = new VarsListNode();
        (*iterator)->Value = iteratorB->Value;
        iterator = &((*iterator)->Next);
        iteratorB = iteratorB->Next;
    }
}

inline const Monom& MonomDRL::operator/=(const Monom& anotherMonom)
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    VarsListNode **iterator = &ListHead,
                 *anotherIterator = castedAnotherMonom->ListHead;

    while (*iterator && anotherIterator)
    {
        if ((*iterator)->Value == anotherIterator->Value)
        {
            VarsListNode* nodeToDelete = *iterator;
            *iterator = (*iterator)->Next;
            delete nodeToDelete;
            --TotalDegree;
            anotherIterator = anotherIterator->Next;
        }
        else if ((*iterator)->Value > anotherIterator->Value)
        {
            iterator = &((*iterator)->Next);
        }
    }

    return *this;
}

inline void MonomDRL::SetQuotientOf(const Monom& monomA, const Monom& monomB)
{
    const MonomDRL* castedMonomA = CastToMe(monomA);
    const MonomDRL* castedMonomB = CastToMe(monomB);

    SetOne();
    VarsListNode **iterator = &ListHead,
                 *iteratorA = castedMonomA->ListHead,
                 *iteratorB = castedMonomB->ListHead;

    while (iteratorA && iteratorB)
    {
        if (iteratorA->Value == iteratorB->Value)
        {
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else
        {
            ++TotalDegree;
            *iterator = new VarsListNode();
            (*iterator)->Value = iteratorA->Value;
            iterator = &((*iterator)->Next);
            if (iteratorA->Value > iteratorB->Value)
            {
                iteratorA = iteratorA->Next;
            }
        }
    }

    while (iteratorA)
    {
        ++TotalDegree;
        *iterator = new VarsListNode();
        (*iterator)->Value = iteratorA->Value;
        iterator = &((*iterator)->Next);
        iteratorA = iteratorA->Next;
    }
}

inline void MonomDRL::SetOne()
{
    TotalDegree = 0;
    if (ListHead)
    {
        VarsListNode* tmpNode;
        while (ListHead)
        {
            tmpNode = ListHead;
            ListHead = ListHead->Next;
            delete tmpNode;
        }
    }
}

inline bool MonomDRL::operator==(const Monom& anotherMonom) const
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree != castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = castedAnotherMonom->ListHead;
        while (anotherIterator)
        {
            if (iterator->Value != anotherIterator->Value)
            {
                break;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return !anotherIterator;
    }
}

inline bool MonomDRL::operator!=(const Monom& anotherMonom) const
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree != castedAnotherMonom->TotalDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = castedAnotherMonom->ListHead;
        while (anotherIterator)
        {
            if (iterator->Value != anotherIterator->Value)
            {
                break;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return anotherIterator;
    }
}

inline bool MonomDRL::operator<(const Monom& anotherMonom) const
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree < castedAnotherMonom->TotalDegree)
    {
        return true;
    }
    else if (TotalDegree > castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = castedAnotherMonom->ListHead;
        while (anotherIterator)
        {
            if (iterator->Value < anotherIterator->Value)
            {
                return false;
            }
            if (iterator->Value > anotherIterator->Value)
            {
                return true;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return false;
    }
}

inline bool MonomDRL::operator>(const Monom& anotherMonom) const
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree < castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    else if (TotalDegree > castedAnotherMonom->TotalDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = castedAnotherMonom->ListHead;
        while (anotherIterator)
        {
            if (iterator->Value < anotherIterator->Value)
            {
                return true;
            }
            if (iterator->Value > anotherIterator->Value)
            {
                return false;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return false;
    }
}

inline bool MonomDRL::IsDivisibleBy(const Monom& anotherMonom) const
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    VarsListNode *iterator = ListHead,
                 *anotherIterator = castedAnotherMonom->ListHead;
    while (iterator && anotherIterator)
    {
        if (iterator->Value == anotherIterator->Value)
        {
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        else if (iterator->Value > anotherIterator->Value)
        {
            iterator = iterator->Next;
        }
        else
        {
            break;
        }
    }

    return !anotherIterator;
}

inline bool MonomDRL::IsTrueDivisibleBy(const Monom& anotherMonom) const
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree <= castedAnotherMonom->TotalDegree)
    {
        return false;
    }

    VarsListNode *iterator = ListHead,
                 *anotherIterator = castedAnotherMonom->ListHead;
    while (iterator && anotherIterator)
    {
        if (iterator->Value == anotherIterator->Value)
        {
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        else if (iterator->Value > anotherIterator->Value)
        {
            iterator = iterator->Next;
        }
        else
        {
            break;
        }
    }

    return !anotherIterator;
}

inline bool MonomDRL::IsPommaretDivisibleBy(const Monom& anotherMonom) const
{
    const MonomDRL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree < castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    if (!castedAnotherMonom->TotalDegree)
    {
        return true;
    }

    VarsListNode *iterator = ListHead,
                 *anotherIterator = castedAnotherMonom->ListHead;
    while (iterator->Value != anotherIterator->Value)
    {
        iterator = iterator->Next;
    }
    while (iterator && anotherIterator)
    {
        if (iterator->Value != anotherIterator->Value)
        {
            break;
        }
        iterator = iterator->Next;
        anotherIterator = anotherIterator->Next;
    }

    return !iterator && !anotherIterator;
}

inline void MonomDRL::SetGcdOf(const Monom& monomA, const Monom& monomB)
{
    const MonomDRL* castedMonomA = CastToMe(monomA);
    const MonomDRL* castedMonomB = CastToMe(monomB);

    SetOne();
    VarsListNode **iterator = &ListHead,
                 *iteratorA = castedMonomA->ListHead,
                 *iteratorB = castedMonomB->ListHead;

    while (iteratorA && iteratorB)
    {
        if (iteratorA->Value == iteratorB->Value)
        {
            ++TotalDegree;
            *iterator = new VarsListNode();
            (*iterator)->Value = iteratorA->Value;
            iterator = &((*iterator)->Next);

            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else if (iteratorA->Value > iteratorB->Value)
        {
            iteratorA = iteratorA->Next;
        }
        else
        {
            iteratorB = iteratorB->Next;
        }
    }
}

inline void MonomDRL::SetLcmOf(const Monom& monomA, const Monom& monomB)
{
    SetProductOf(monomA, monomB);
}

inline Monom::Integer MonomDRL::FirstMultiVar() const
{
    if (!ListHead)
    {
        return 0;
    }
    else
    {
        return ListHead->Value;
    }
}

inline std::set<Monom::Integer> MonomDRL::GetVariablesSet() const
{
    std::set<Monom::Integer> result;
    VarsListNode *iterator = ListHead;
    while (iterator)
    {
        result.insert(iterator->Value);
        iterator = iterator->Next;
    }
    return result;
}

#endif // MONOMDRL_H
