#ifndef MONOMDL_H
#define MONOMDL_H

#include <set>

#include "fast_allocator.h"
#include "monom.h"


class MonomDL : public Monom
{
private:
    struct VarsListNode
    {
        Integer Value;
        VarsListNode* Next;
        static FastAllocator Allocator;

        VarsListNode();
        VarsListNode(Integer newValue, VarsListNode*& newNext);
        ~VarsListNode();

        void* operator new(size_t);
        void operator delete(void* ptr);
    };

    VarsListNode* ListHead;
    static FastAllocator Allocator;

    friend class Monom;

private:
    MonomDL();
    MonomDL(const Monom& anotherMonom);
    VarsListNode* Find(const Integer var) const;
    const MonomDL* CastToMe(const Monom& monom) const;

public:
    ~MonomDL();

    Monom::Order GetOrder() const;

    void* operator new(std::size_t);
    void operator delete(void* ptr);

    Integer operator[](Integer var) const;

    const Monom& operator=(const Monom& anotherMonom);

    const Monom& operator*=(Integer var);
    const Monom& operator*=(const Monom& anotherMonom);
    void SetProductOf(const Monom& anotherMonom, Integer var);
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

    Integer FirstMultiVar() const;
    std::set<Integer> GetVariablesSet() const;

    int Compare(const Monom& anotherMonom);
    Integer GcdDegree(const Monom& anotherMonom);
    Integer LcmDegree(const Monom& anotherMonom);
};


inline MonomDL::VarsListNode::VarsListNode()
    : Value(0)
    , Next(0)
{
}

inline MonomDL::VarsListNode::VarsListNode(Monom::Integer newValue, VarsListNode*& newNext)
    : Value(newValue)
    , Next(newNext)
{
}

inline MonomDL::VarsListNode::~VarsListNode()
{
}

inline void* MonomDL::VarsListNode::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void MonomDL::VarsListNode::operator delete(void* ptr)
{
    Allocator.Free(ptr);
}

inline MonomDL::MonomDL()
    : Monom()
    , ListHead(0)
{
}

inline MonomDL::MonomDL(const Monom& anotherMonom)
    : Monom()
    , ListHead(0)
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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

inline MonomDL::VarsListNode* MonomDL::Find(const MonomDL::Integer var) const
{
    if (!ListHead || ListHead->Value > var)
    {
        return 0;
    }

    VarsListNode *previousPointer(ListHead), *currentPointer;
    Integer range(TotalDegree), middle;

    while ((middle = range >> 1) > 0)
    {
        currentPointer = previousPointer;
        for (register Integer i = 0; i < middle; ++i)
        {
            currentPointer = currentPointer->Next;
        }

        if (currentPointer->Value < var)
        {
            previousPointer = currentPointer;
            range -= middle;
        }
        else if (currentPointer->Value > var)
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

inline const MonomDL* MonomDL::CastToMe(const Monom& monom) const
{
    if (monom.GetOrder() != GetOrder())
    {
        throw 1;
    }
    return static_cast<const MonomDL*>(&monom);
}

inline MonomDL::~MonomDL()
{
    SetOne();
}

inline Monom::Order MonomDL::GetOrder() const
{
    return Monom::DegLex;
}

inline void* MonomDL::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void MonomDL::operator delete(void* ptr)
{
    Allocator.Free(ptr);
}

inline MonomDL::Integer MonomDL::operator[](MonomDL::Integer var) const
{
    if (!ListHead || ListHead->Value > var)
    {
        return 0;
    }

    VarsListNode *previousPointer(ListHead), *currentPointer;
    Integer range(TotalDegree), middle;

    while (range > 0)
    {
        middle = range >> 1;
        currentPointer = previousPointer;
        for (register Integer i = 0; i < middle; ++i)
        {
            currentPointer = currentPointer->Next;
        }

        if (currentPointer->Value < var)
        {
            previousPointer = currentPointer->Next;
            range -= middle + 1;
        }
        else if (currentPointer->Value > var)
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

inline const Monom& MonomDL::operator=(const Monom& anotherMonom)
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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

inline const Monom& MonomDL::operator*=(MonomDL::Integer var)
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

inline const Monom& MonomDL::operator*=(const Monom& anotherMonom)
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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
            else if ((*iterator)->Value < anotherIterator->Value)
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

inline void MonomDL::SetProductOf(const Monom& anotherMonom, MonomDL::Integer var)
{
    *this = anotherMonom;
    *this *= var;
}

inline void MonomDL::SetProductOf(const Monom& monomA, const Monom& monomB)
{
    const MonomDL* castedMonomA = CastToMe(monomA);
    const MonomDL* castedMonomB = CastToMe(monomB);

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
        else if (iteratorA->Value < iteratorB->Value)
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

inline const Monom& MonomDL::operator/=(const Monom& anotherMonom)
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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
        else if ((*iterator)->Value < anotherIterator->Value)
        {
            iterator = &((*iterator)->Next);
        }
    }

    return *this;
}

inline void MonomDL::SetQuotientOf(const Monom& monomA, const Monom& monomB)
{
    const MonomDL* castedMonomA = CastToMe(monomA);
    const MonomDL* castedMonomB = CastToMe(monomB);

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
            if (iteratorA->Value < iteratorB->Value)
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

inline void MonomDL::SetOne()
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

inline bool MonomDL::operator==(const Monom& anotherMonom) const
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree != castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator(ListHead),
                     *anotherIterator(castedAnotherMonom->ListHead);
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

inline bool MonomDL::operator!=(const Monom& anotherMonom) const
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree != castedAnotherMonom->TotalDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator(ListHead),
                     *anotherIterator(castedAnotherMonom->ListHead);
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

inline bool MonomDL::operator<(const Monom& anotherMonom) const
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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
        VarsListNode *iterator(ListHead),
                     *anotherIterator(castedAnotherMonom->ListHead);
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

inline bool MonomDL::operator>(const Monom& anotherMonom) const
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

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
        VarsListNode *iterator(ListHead),
                     *anotherIterator(castedAnotherMonom->ListHead);
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

inline bool MonomDL::IsDivisibleBy(const Monom& anotherMonom) const
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

    VarsListNode *iterator(ListHead),
                 *anotherIterator(castedAnotherMonom->ListHead);
    while (iterator && anotherIterator)
    {
        if (iterator->Value == anotherIterator->Value)
        {
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        else if (iterator->Value < anotherIterator->Value)
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

inline bool MonomDL::IsTrueDivisibleBy(const Monom& anotherMonom) const
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree <= castedAnotherMonom->TotalDegree)
    {
        return false;
    }

    VarsListNode *iterator(ListHead),
                 *anotherIterator(castedAnotherMonom->ListHead);
    while (iterator && anotherIterator)
    {
        if (iterator->Value == anotherIterator->Value)
        {
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        else if (iterator->Value < anotherIterator->Value)
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

inline bool MonomDL::IsPommaretDivisibleBy(const Monom& anotherMonom) const
{
    const MonomDL* castedAnotherMonom = CastToMe(anotherMonom);

    if (TotalDegree < castedAnotherMonom->TotalDegree)
    {
        return false;
    }
    if (!castedAnotherMonom->TotalDegree)
    {
        return true;
    }

    VarsListNode *iterator(ListHead),
                 *anotherIterator(castedAnotherMonom->ListHead);
    while (iterator && anotherIterator)
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

inline void MonomDL::SetGcdOf(const Monom& monomA, const Monom& monomB)
{
    const MonomDL* castedMonomA = CastToMe(monomA);
    const MonomDL* castedMonomB = CastToMe(monomB);

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
        else if (iteratorA->Value < iteratorB->Value)
        {
            iteratorA = iteratorA->Next;
        }
        else
        {
            iteratorB = iteratorB->Next;
        }
    }
}

inline void MonomDL::SetLcmOf(const Monom& monomA, const Monom& monomB)
{
    SetProductOf(monomA, monomB);
}

inline MonomDL::Integer MonomDL::FirstMultiVar() const
{
    if (!ListHead)
    {
        return 0;
    }

    VarsListNode* iterator(ListHead);
    while (iterator->Next)
    {
        iterator = iterator->Next;
    }
    return iterator->Value;
}

inline std::set<MonomDL::Integer> MonomDL::GetVariablesSet() const
{
    std::set<Integer> result;
    VarsListNode *iterator = ListHead;
    while (iterator)
    {
        result.insert(iterator->Value);
        iterator = iterator->Next;
    }
    return result;
}

#endif // MONOMDRL_H
