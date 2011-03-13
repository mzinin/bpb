#ifndef MONOM_H
#define MONOM_H

#include <iostream>
#include <set>

#include "fast_allocator.h"
#include "variables.h"

class Monom
{
public:
    typedef short int Integer;
    enum Order
    {
        Lex,
        DegLex,
        DegRevLex,
    };

private:
    struct VarsListNode
    {
        Monom::Integer Value;
        VarsListNode* Previous;
        VarsListNode* Next;
        static FastAllocator Allocator;

        VarsListNode();
        ~VarsListNode();

        void* operator new(size_t);
        void operator delete(void* ptr);
    };
    VarsListNode* ListHead;
    VarsListNode* ListTail;
    Integer TotalDegree;

    static FastAllocator Allocator;
    static Integer DimIndepend;
    static Variables* const IndependVariables;

public:
    Monom* Next;

public:
    Monom();
    Monom(const Monom& anotherMonom);
    ~Monom();

    void* operator new(std::size_t);
    void operator delete(void* ptr);

    void SetOne();
    Integer Degree() const;
    Integer operator[](Integer var) const;

    const Monom& operator=(const Monom& anotherMonom);
    const Monom& operator*=(Integer var);
    const Monom& operator*=(const Monom& anotherMonom);
    const Monom& operator/=(const Monom& anotherMonom);
    void SetQuotientOf(const Monom& monomA, const Monom& monomB);

    bool operator==(const Monom& anotherMonom) const;
    bool operator!=(const Monom& anotherMonom) const;

    bool operator<(const Monom& anotherMonom) const;
    bool operator>(const Monom& anotherMonom) const;
    int Compare(const Monom& anotherMonom) const;

    bool IsDivisibleBy(const Monom& anotherMonom) const;
    bool IsTrueDivisibleBy(const Monom& anotherMonom) const;
    bool IsPommaretDivisibleBy(const Monom& anotherMonom) const;

    Integer FirstMultiVar() const;
    std::set<Integer> GetVariablesSet() const;

    static void AddVariable(const char *var);
    static const char* GetVariable(Integer var);
    static Integer GetDimIndepend();

    friend std::istream& operator>>(std::istream& in, Monom& a);
    friend std::ostream& operator<<(std::ostream& out, const Monom& a);

private:
    VarsListNode* Find(const Monom::Integer var) const;
    bool operatorLessLex(const Monom& anotherMonom) const;
    bool operatorLessDegLex(const Monom& anotherMonom) const;
    bool operatorLessDegRevLex(const Monom& anotherMonom) const;
    bool operatorMoreLex(const Monom& anotherMonom) const;
    bool operatorMoreDegLex(const Monom& anotherMonom) const;
    bool operatorMoreDegRevLex(const Monom& anotherMonom) const;
    int CompareLex(const Monom& anotherMonom) const;
    int CompareDegLex(const Monom& anotherMonom) const;
    int CompareDegRevLex(const Monom& anotherMonom) const;
};


inline Monom::VarsListNode::VarsListNode()
    : Value(0)
    , Previous(0)
    , Next(0)
{
}

inline Monom::VarsListNode::~VarsListNode()
{
}

inline void* Monom::VarsListNode::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void Monom::VarsListNode::operator delete(void* ptr)
{
    Allocator.Free(ptr);
}

inline Monom::Monom()
    : TotalDegree(0)
    , Next(0)
    , ListHead(0)
    , ListTail(0)
{
}

inline Monom::Monom(const Monom& anotherMonom)
    : TotalDegree(anotherMonom.TotalDegree)
    , Next(0)
    , ListHead(0)
    , ListTail(0)
{
    if (!anotherMonom.ListHead)
    {
        return;
    }
    else
    {
        VarsListNode **iterator = &ListHead,
                     *iteratorAnother = anotherMonom.ListHead;
        while (iteratorAnother)
        {
            *iterator = new VarsListNode();
            (*iterator)->Value = iteratorAnother->Value;
            (*iterator)->Previous = ListTail;
            ListTail = *iterator;

            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
}

inline Monom::~Monom()
{
    SetOne();
}

inline Monom::VarsListNode* Monom::Find(const Monom::Integer var) const
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

inline void* Monom::operator new(std::size_t)
{
    return Allocator.Allocate();
}

inline void Monom::operator delete(void* ptr)
{
    Allocator.Free(ptr);
}

inline void Monom::SetOne()
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
    ListTail = 0;
}

inline Monom::Integer Monom::Degree() const
{
    return TotalDegree;
}

inline Monom::Integer Monom::operator[](Monom::Integer var) const
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

inline const Monom& Monom::operator=(const Monom& anotherMonom)
{
    if (this == &anotherMonom)
    {
        return *this;
    }

    if (!anotherMonom.ListHead)
    {
        SetOne();
    }
    else
    {
        TotalDegree = anotherMonom.TotalDegree;

        VarsListNode *iteratorAnother = anotherMonom.ListHead,
                     **iterator = &ListHead;
        while (*iterator && iteratorAnother)
        {
            (*iterator)->Value = iteratorAnother->Value;
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }

        if (*iterator)
        {
            ListTail = (*iterator)->Next->Previous;
            VarsListNode *nodeToDelete = (*iterator)->Next;
            *iterator = 0;
            while (nodeToDelete)
            {
                iteratorAnother = nodeToDelete;
                nodeToDelete = nodeToDelete->Next;
                delete iteratorAnother;
            }
        }
        else if (iteratorAnother)
        {
            while (iteratorAnother)
            {
                *iterator = new VarsListNode();
                (*iterator)->Value = iteratorAnother->Value;
                (*iterator)->Previous = ListTail;
                ListTail = *iterator;

                iterator = &((*iterator)->Next);
                iteratorAnother = iteratorAnother->Next;
            }
        }
    }
    return *this;
}

inline const Monom& Monom::operator*=(Monom::Integer var)
{
    //inserted variable is the only one
    if (!ListHead)
    {
        ListHead = new VarsListNode();
        ListTail = ListHead;
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
            ListHead->Previous = position;
            ListHead = position;
            ++TotalDegree;
        }
        //all other cases
        else if(position->Value != var)
        {
            VarsListNode* newNode = new VarsListNode();
            newNode->Value = var;
            newNode->Next = position->Next;
            newNode->Previous = position;
            position->Next = newNode;
            if (newNode->Next)
            {
                newNode->Next->Previous = newNode;
            }
            else
            {
                ListTail = newNode;
            }
            ++TotalDegree;
        }
    }

    return *this;
}

inline const Monom& Monom::operator*=(const Monom& anotherMonom)
{
    if (!ListHead)
    {
        *this = anotherMonom;
    }
    else
    {
        if (anotherMonom.ListHead)
        {
            VarsListNode **iterator = &ListHead,
                         *anotherIterator = anotherMonom.ListHead;

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
                    newNode->Previous = newNode->Next->Previous;
                    *iterator = newNode;
                    newNode->Next->Previous = newNode;
                    ++TotalDegree;

                    iterator = &(newNode->Next);
                    anotherIterator = anotherIterator->Next;
                }
            }

            while (anotherIterator)
            {
                *iterator = new VarsListNode();
                (*iterator)->Value = anotherIterator->Value;
                (*iterator)->Previous = ListTail;
                ListTail = *iterator;
                ++TotalDegree;

                iterator = &((*iterator)->Next);
                anotherIterator = anotherIterator->Next;
            }
        }
    }

    return *this;
}

inline const Monom& Monom::operator/=(const Monom& anotherMonom)
{
    VarsListNode **iterator = &ListHead,
                 *anotherIterator = anotherMonom.ListHead;

    while (*iterator && anotherIterator)
    {
        if ((*iterator)->Value == anotherIterator->Value)
        {
            VarsListNode* nodeToDelete = *iterator;
            *iterator = (*iterator)->Next;
            if (nodeToDelete->Next)
            {
                nodeToDelete->Next->Previous = nodeToDelete->Previous;
            }
            else
            {
                ListTail = nodeToDelete->Previous;
            }
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

inline void Monom::SetQuotientOf(const Monom& monomA, const Monom& monomB)
{
    SetOne();
    VarsListNode **iterator = &ListHead,
                 *iteratorA = monomA.ListHead,
                 *iteratorB = monomB.ListHead;

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
            (*iterator)->Previous = ListTail;
            ListTail = *iterator;

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
        (*iterator)->Previous = ListTail;
        ListTail = *iterator;

        iterator = &((*iterator)->Next);
        iteratorA = iteratorA->Next;
    }
}

inline bool Monom::operator==(const Monom& anotherMonom) const
{
    if (TotalDegree != anotherMonom.TotalDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = anotherMonom.ListHead;
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

inline bool Monom::operator!=(const Monom& anotherMonom) const
{
    if (TotalDegree != anotherMonom.TotalDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = anotherMonom.ListHead;
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

inline bool Monom::IsDivisibleBy(const Monom& anotherMonom) const
{
    VarsListNode *iterator = ListHead,
                 *anotherIterator = anotherMonom.ListHead;
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

inline bool Monom::IsTrueDivisibleBy(const Monom& anotherMonom) const
{
    if (TotalDegree <= anotherMonom.TotalDegree)
    {
        return false;
    }

    VarsListNode *iterator = ListHead,
                 *anotherIterator = anotherMonom.ListHead;
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

inline bool Monom::IsPommaretDivisibleBy(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return false;
    }
    if (!anotherMonom.TotalDegree)
    {
        return true;
    }

    VarsListNode *iterator = ListHead,
                 *anotherIterator = anotherMonom.ListHead;
    while (iterator && iterator->Value > anotherIterator->Value)
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

inline Monom::Integer Monom::FirstMultiVar() const
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

inline std::set<Monom::Integer> Monom::GetVariablesSet() const
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

inline Monom::Integer Monom::GetDimIndepend()
{
    return DimIndepend;
}

#endif
