#pragma once

#include "fast_allocator.h"
#include "variables.h"

#include <cstdint>
#include <iostream>
#include <set>


class Monom
{
public:
    using Integer = uint16_t;

    static const Integer invalidVariable;

    enum Order
    {
        Lex,
        DegLex,
        DegRevLex
    };

public:
    virtual ~Monom() = default;

    virtual Integer degree() const;

    std::string toString() const;
    std::string innerStructure() const;

    virtual void setOne() = 0;
    virtual Integer operator[](Integer var) const = 0;

    virtual Integer firstMultiVar() const = 0;
    virtual std::set<Integer> variablesSet() const = 0;

    static void addVariable(const std::string& var);
    static const std::string& variable(Integer var);
    static Integer dimIndepend();

    friend std::istream& operator>>(std::istream& in, Monom& monom);
    friend std::ostream& operator<<(std::ostream& out, const Monom& monom);

protected:
    struct VarsListNode
    {
        Integer value = 0;
        VarsListNode* next = nullptr;

        static FastAllocator allocator;

        void* operator new(size_t);
        void operator delete(void* ptr);
    };

protected:
    Monom() = default;
    virtual void multiplyBy(Integer var) = 0;
    virtual VarsListNode* find(Integer var) const = 0;

protected:
    VarsListNode* listHead_ = nullptr;
    Integer totalDegree_ = 0;

    static Integer dimIndepend_;
    static Variables independVariables_;
};


inline void* Monom::VarsListNode::operator new(std::size_t)
{
    return allocator.allocate();
}

inline void Monom::VarsListNode::operator delete(void* ptr)
{
    allocator.free(ptr);
}

inline Monom::Integer Monom::degree() const
{
    return totalDegree_;
}

inline Monom::Integer Monom::dimIndepend()
{
    return dimIndepend_;
}
