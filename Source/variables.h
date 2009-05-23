#ifndef VARIABLES_H
#define VARIABLES_H

#include <cstring>
#include <iostream>
#include <vector>
#include "util.h"
using namespace std;

class Variables
{
public:
    typedef vector<const char*> List;
    typedef vector<const char*>::const_iterator ConstIterator;

private:
    List mList;

public:
    Variables(): mList() {}
    ~Variables();

    bool add(const char *var);
    int find(const char *var) const;
    int read(std::istream& in) const;

    int dim() const
    {
        return mList.size();
    }

    ConstIterator begin() const
    {
        return mList.begin();
    }

    ConstIterator end() const
    {
        return mList.end();
    }

    const char* variable(int varNumber) const
    {
        if (varNumber >= dim())
        {
            varNumber = 0;
        }
        return mList[varNumber];
    }
};

#endif // IVARIABLES_H
