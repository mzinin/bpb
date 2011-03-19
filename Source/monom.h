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
        DegRevLex
    };

protected:
    struct VarsListNode
    {
        Integer Value;
        VarsListNode* Next;
        static FastAllocator Allocator;

        VarsListNode();
        ~VarsListNode();

        void* operator new(size_t);
        void operator delete(void* ptr);
    };
    VarsListNode* ListHead;
    Integer TotalDegree;

    static Integer DimIndepend;
    static Variables* const IndependVariables;

protected:
    Monom();
    virtual void MultiplyBy(Integer var) = 0;
    virtual VarsListNode* Find(const Integer var) const = 0;

public:
    virtual ~Monom();
    virtual Integer Degree() const;

    virtual void SetOne() = 0;
    virtual Integer operator[](const Integer var) const = 0;

    virtual Integer FirstMultiVar() const = 0;
    virtual std::set<Integer> GetVariablesSet() const = 0;

    static void AddVariable(const char *var);
    static const char* GetVariable(Integer var);
    static Integer GetDimIndepend();

    friend std::istream& operator>>(std::istream& in, Monom& monom);
    friend std::ostream& operator<<(std::ostream& out, const Monom& monom);
};

inline Monom::VarsListNode::VarsListNode()
    : Value(0)
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
{
}

inline Monom::~Monom()
{
}

inline Monom::Integer Monom::Degree() const
{
    return TotalDegree;
}

inline Monom::Integer Monom::GetDimIndepend()
{
    return DimIndepend;
}

#endif
