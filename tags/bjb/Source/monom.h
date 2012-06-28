#ifndef MONOM_H
#define MONOM_H

#include <string>
#include "fast_allocator.h"
#include "variables.h"

class Monom 
{
public:
    typedef short int Integer;

public:
    Monom();
    Monom(const Monom& anotherMonom);
    Monom(const std::string& str);
    ~Monom();

    std::string ToString() const;

    void* operator new(std::size_t);
    void operator delete(void* ptr);

    void SetOne();
    Integer Degree() const;
    Integer operator[](const Integer var) const;

    const Monom& operator=(const Monom& anotherMonom);
    bool operator==(const Monom& anotherMonom) const;
    bool operator!=(const Monom& anotherMonom) const;

    void Prolong(Integer var, Integer degree = 1);
    void Multiply(const Monom& anotherMonom);
    
    void Divide(const Monom& anotherMonom);
    void SetQuotientOf(const Monom& monomA, const Monom& monomB);

    bool operator<(const Monom& anotherMonom) const;
    bool operator>(const Monom& anotherMonom) const;
    static int Compare(const Monom& monomA, const Monom& monomB);

    bool IsDivisibleBy(const Monom& anotherMonom) const;
    bool IsTrueDivisibleBy(const Monom& anotherMonom) const;
    bool HasSameOnlyVariable(const Monom& anotherMonom) const;

    static Integer GcdDegree(const Monom& monomA, const Monom& monomB);
    static Integer LcmDegree(const Monom& monomA, const Monom& monomB);
    void SetGcdOf(const Monom& monomA, const Monom& monomB);
    void SetLcmOf(const Monom& monomA, const Monom& monomB);

    static void AddVariable(const std::string& var);
    static const std::string& GetVariable(Integer var);
    static Integer GetDimIndepend();

    friend std::istream& operator>>(std::istream& in, Monom& monom);
    friend std::ostream& operator<<(std::ostream& out, const Monom& monom);

public:
    Monom* Next;

private:
    struct VarsListNode
    {
        Integer Variable;
        Integer Degree;
        VarsListNode* Next;
        static FastAllocator Allocator;

        VarsListNode();
        ~VarsListNode();

        void* operator new(size_t);
        void operator delete(void* ptr);
    };
    VarsListNode* Find(const Integer var) const;
    
    VarsListNode* ListHead;
    Integer TotalDegree;

    static Integer DimIndepend;
    static Variables IndependVariables;
    static FastAllocator Allocator;
};

inline Monom::VarsListNode::VarsListNode()
    : Variable(0)
    , Degree(0)
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
    : ListHead(0)
    , TotalDegree(0)
    , Next(0)
{
}

inline Monom::Monom(const Monom& anotherMonom)
    : ListHead(0)
    , TotalDegree(anotherMonom.TotalDegree)
    , Next(0)
{
    if (!anotherMonom.ListHead)
    {
        return;
    }
    else
    {
        TotalDegree = anotherMonom.TotalDegree;
        VarsListNode **iterator = &ListHead,
                     *iteratorAnother = anotherMonom.ListHead;
        while (iteratorAnother)
        {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorAnother->Variable;
            (*iterator)->Degree = iteratorAnother->Degree;

            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
}

inline Monom::~Monom()
{
    SetOne();
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
}

inline Monom::Integer Monom::Degree() const
{
    return TotalDegree;
}

inline Monom::Integer Monom::operator[](Monom::Integer var) const
{
    VarsListNode* varPosition = Find(var);
    return (varPosition && varPosition->Variable == var) ? varPosition->Degree : 0;
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
            (*iterator)->Variable = iteratorAnother->Variable;
            (*iterator)->Degree = iteratorAnother->Degree;
            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        } 

        if (*iterator)
        {
            VarsListNode* nodeToDelete = *iterator;
            *iterator = 0;
            while (nodeToDelete)
            {
                iteratorAnother = nodeToDelete;
                nodeToDelete = nodeToDelete->Next;
                delete iteratorAnother;
            }
        }
        else while (iteratorAnother)
        {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorAnother->Variable;
            (*iterator)->Degree = iteratorAnother->Degree;

            iterator = &((*iterator)->Next);
            iteratorAnother = iteratorAnother->Next;
        }
    }
    return *this;
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
            if (iterator->Variable != anotherIterator->Variable ||
                iterator->Degree != anotherIterator->Degree)
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
            if (iterator->Variable != anotherIterator->Variable ||
                iterator->Degree != anotherIterator->Degree)
            {
                break;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return anotherIterator;
    }
}

inline void Monom::Prolong(Monom::Integer var, Monom::Integer degree)
{
    //inserted variable is the only one
    if (!ListHead)
    {
        ListHead = new VarsListNode();
        ListHead->Variable = var;
        ListHead->Degree = degree;
    }
    else
    {
        VarsListNode* position = Find(var);
        //inserted variable is the eldest one
        if (!position)
        {
            position = new VarsListNode();
            position->Variable = var;
            position->Degree = degree;
            position->Next = ListHead;
            ListHead = position;
        }
        //all other cases
        else if(position->Variable != var)
        {
            VarsListNode* newNode = new VarsListNode();
            newNode->Variable = var;
            newNode->Degree = degree;
            newNode->Next = position->Next;
            position->Next = newNode;
        }
        else
        {
            position->Degree += degree;
        }
    }
    TotalDegree += degree;
}

inline void Monom::Multiply(const Monom& anotherMonom)
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
                if ((*iterator)->Variable == anotherIterator->Variable)
                {
                    (*iterator)->Degree += anotherIterator->Degree;
                    TotalDegree += anotherIterator->Degree;
                    iterator = &((*iterator)->Next);
                    anotherIterator = anotherIterator->Next;
                }
                else if ((*iterator)->Variable > anotherIterator->Variable)
                {
                    iterator = &((*iterator)->Next);
                }
                else
                {
                    VarsListNode* newNode = new VarsListNode();
                    newNode->Variable = anotherIterator->Variable;
                    newNode->Degree = anotherIterator->Degree;
                    newNode->Next = *iterator;
                    *iterator = newNode;
                    TotalDegree += anotherIterator->Degree;

                    iterator = &(newNode->Next);
                    anotherIterator = anotherIterator->Next;
                }
            }

            while (anotherIterator)
            {
                *iterator = new VarsListNode();
                (*iterator)->Variable = anotherIterator->Variable;
                (*iterator)->Degree = anotherIterator->Degree;
                TotalDegree += anotherIterator->Degree;

                iterator = &((*iterator)->Next);
                anotherIterator = anotherIterator->Next;
            }
        }
    }
}

inline void Monom::Divide(const Monom& anotherMonom)
{
    VarsListNode **iterator = &ListHead,
                 *anotherIterator = anotherMonom.ListHead;

    while (*iterator && anotherIterator)
    {
        if ((*iterator)->Variable == anotherIterator->Variable)
        {
            if ((*iterator)->Degree == anotherIterator->Degree)
            {
                VarsListNode* nodeToDelete = *iterator;
                *iterator = (*iterator)->Next;
                delete nodeToDelete;
            }
            else
            {
                (*iterator)->Degree -= anotherIterator->Degree;
            }
            TotalDegree -= anotherIterator->Degree;
            anotherIterator = anotherIterator->Next;
        }
        else if ((*iterator)->Variable > anotherIterator->Variable)
        {
            iterator = &((*iterator)->Next);
        }
    }
}

inline void Monom::SetQuotientOf(const Monom& monomA, const Monom& monomB)
{
    SetOne();
    VarsListNode **iterator = &ListHead,
                 *iteratorA = monomA.ListHead,
                 *iteratorB = monomB.ListHead;

    while (iteratorA && iteratorB)
    {
        if (iteratorA->Variable == iteratorB->Variable)
        {
            if (iteratorA->Degree != iteratorB->Degree)
            {
                *iterator = new VarsListNode();
                (*iterator)->Variable = iteratorA->Variable;
                (*iterator)->Degree = iteratorA->Degree - iteratorB->Degree;
                TotalDegree += (*iterator)->Degree;
                iterator = &((*iterator)->Next);
            }
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else
        {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorA->Variable;
            (*iterator)->Degree = iteratorA->Degree;
            TotalDegree += (*iterator)->Degree;
            iterator = &((*iterator)->Next);

            if (iteratorA->Variable > iteratorB->Variable)
            {
                iteratorA = iteratorA->Next;
            }
        }
    }

    while (iteratorA)
    {
        *iterator = new VarsListNode();
        (*iterator)->Variable = iteratorA->Variable;
        (*iterator)->Degree = iteratorA->Degree;
        TotalDegree += (*iterator)->Degree;
        iterator = &((*iterator)->Next);

        iteratorA = iteratorA->Next;
    }
}

inline bool Monom::operator<(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return true;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return false;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = anotherMonom.ListHead;
        while (anotherIterator)
        {
            if (iterator->Variable < anotherIterator->Variable)
            {
                return false;
            }
            else if (iterator->Variable > anotherIterator->Variable)
            {
                return true;
            }
            else
            {
                if (iterator->Degree < anotherIterator->Degree)
                {
                    return false;
                }
                else if (iterator->Degree > anotherIterator->Degree)
                {
                    return true;
                }
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return false;
    }
}

inline bool Monom::operator>(const Monom& anotherMonom) const
{
    if (TotalDegree < anotherMonom.TotalDegree)
    {
        return false;
    }
    else if (TotalDegree > anotherMonom.TotalDegree)
    {
        return true;
    }
    else
    {
        VarsListNode *iterator = ListHead,
                     *anotherIterator = anotherMonom.ListHead;
        while (anotherIterator)
        {
            if (iterator->Variable < anotherIterator->Variable)
            {
                return true;
            }
            else if (iterator->Variable > anotherIterator->Variable)
            {
                return false;
            }
            else
            {
                if (iterator->Degree < anotherIterator->Degree)
                {
                    return true;
                }
                else if (iterator->Degree > anotherIterator->Degree)
                {
                    return false;
                }
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        return false;
    }
}

inline int Monom::Compare(const Monom& monomA, const Monom& monomB)
{
    if (monomA.TotalDegree < monomB.TotalDegree)
    {
        return -1;
    }
    else if (monomA.TotalDegree > monomB.TotalDegree)
    {
        return 1;
    }
    else
    {
        VarsListNode *iteratorA(monomA.ListHead),
                     *iteratorB(monomB.ListHead);
        while (iteratorA)
        {
            if (iteratorA->Variable < iteratorB->Variable)
            {
                return 1;
            }
            else if (iteratorA->Variable > iteratorB->Variable)
            {
                return -1;
            }
            else
            {
                if (iteratorA->Degree < iteratorB->Degree)
                {
                    return 1;
                }
                else if (iteratorA->Degree > iteratorB->Degree)
                {
                    return -1;
                }
            }
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        return 0;
    }
}

inline bool Monom::HasSameOnlyVariable(const Monom& anotherMonom) const
{
    return ListHead && 
           anotherMonom.ListHead &&
           ListHead->Variable == anotherMonom.ListHead->Variable &&
           !ListHead->Next &&
           !anotherMonom.ListHead->Next;
}

inline Monom::Integer Monom::GetDimIndepend()
{
    return DimIndepend;
}

inline Monom::VarsListNode* Monom::Find(const Monom::Integer var) const
{
    if (!ListHead || ListHead->Variable < var)
    {
        return 0;
    }

    VarsListNode* position = ListHead;
    while (position && position->Next && position->Next->Variable >= var)
    {
        position = position->Next;
    }
    return position;
}


#endif // MONOM_H

