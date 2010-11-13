#ifndef MONOM_H
#define MONOM_H

#include <iostream>
#include <set>

#include "variables.h"

class MonomDRL;
class MonomDL;
class MonomLex;
class MonomOld;

class Monom
{
public:
    typedef short int Integer;
    enum Order
    {
        Lex,
        DegLex,
        DegRevLex,
        OldDRL
    };

protected:
    static Integer DimIndepend;
    static Variables* const IndependVariables;
    Integer TotalDegree;

public:
    Monom* Next;

protected:
    Monom();

public:
    virtual ~Monom();

    virtual Order GetOrder() const = 0;

    virtual Integer Degree() const;
    virtual Integer operator[](Integer var) const = 0;

    virtual const Monom& operator*=(Integer var) = 0;
    virtual const Monom& operator*=(const Monom& anotherMonom) = 0;
    virtual void SetProductOf(const Monom& monomA, Integer var) = 0;
    virtual void SetProductOf(const Monom& monomA, const Monom& monomB) = 0;

    virtual const Monom& operator/=(const Monom& anotherMonom) = 0;
    virtual void SetQuotientOf(const Monom& monomA, const Monom& monomB) = 0;

    virtual bool operator==(const Monom& anotherMonom) const = 0;
    virtual bool operator!=(const Monom& anotherMonom) const = 0;
    virtual bool operator<(const Monom& anotherMonom) const = 0;
    virtual bool operator>(const Monom& anotherMonom) const = 0;

    virtual void SetOne() = 0;

    virtual bool IsDivisibleBy(const Monom& anotherMonom) const = 0;
    virtual bool IsTrueDivisibleBy(const Monom& anotherMonom) const = 0;
    virtual bool IsPommaretDivisibleBy(const Monom& anotherMonom) const = 0;

    virtual void SetGcdOf(const Monom& monomA, const Monom& monomB) = 0;
    virtual void SetLcmOf(const Monom& monomA, const Monom& monomB) = 0;

    virtual Integer FirstMultiVar() const = 0;
    virtual std::set<Integer> GetVariablesSet() const = 0;

    virtual int Compare(const Monom& anotherMonom) = 0;
    virtual Integer GcdDegree(const Monom& anotherMonom) = 0;
    virtual Integer LcmDegree(const Monom& anotherMonom) = 0;

    static void AddVariable(const char *var);
    static const char* GetVariable(Integer var);
    static Integer GetDimIndepend();

    static Monom* GetNewMonom();
    static Monom* GetNewMonom(const Monom& anotherMonom);

    friend std::istream& operator>>(std::istream& in, Monom& a);
    friend std::ostream& operator<<(std::ostream& out, const Monom& a);
};

inline Monom::Monom()
    : TotalDegree(0)
    , Next(0)
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
