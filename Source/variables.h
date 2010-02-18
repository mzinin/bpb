#ifndef VARIABLES_H
#define VARIABLES_H

#include <cstring>
#include <iostream>
#include <vector>
#include "util.h"

class Variables
{
public:
    typedef std::vector<const char*> Vector;
    typedef std::vector<const char*>::const_iterator ConstIterator;

private:
    Vector mVector;

public:
    Variables(): mVector() {}
    ~Variables();

    bool Add(const char *var);
    int Find(const char *var) const;
    int Read(std::istream& in) const;

    int Dim() const;
    ConstIterator Begin() const;
    ConstIterator End() const;
    const char* Variable(int varNumber) const;
};


inline int Variables::Dim() const
{
    return mVector.size();
}

inline Variables::ConstIterator Variables::Begin() const
{
    return mVector.begin();
}

inline Variables::ConstIterator Variables::End() const
{
    return mVector.end();
}

inline const char* Variables::Variable(int varNumber) const
{
    if (varNumber >= Dim())
    {
        varNumber = 0;
    }
    return mVector[varNumber];
}

#endif // IVARIABLES_H
