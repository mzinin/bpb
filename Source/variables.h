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

    bool add(const char *var);
    int find(const char *var) const;
    int read(std::istream& in) const;

    int dim() const;
    ConstIterator begin() const;
    ConstIterator end() const;
    const char* variable(int varNumber) const;
};


inline int Variables::dim() const
{
    return mVector.size();
}

inline Variables::ConstIterator Variables::begin() const
{
    return mVector.begin();
}

inline Variables::ConstIterator Variables::end() const
{
    return mVector.end();
}

inline const char* Variables::variable(int varNumber) const
{
    if (varNumber >= dim())
    {
        varNumber = 0;
    }
    return mVector[varNumber];
}

#endif // IVARIABLES_H
