#include <cctype>
#include "variables.h"

Variables::~Variables()
{
    for (register unsigned i = 0; i < mVector.size(); ++i)
    {
        delete mVector[i];
    }
    mVector.clear();
}

bool Variables::Add(const char *var)
{
    int n = strlen(var);
    char *name = new char[n+1];
    int k = 0;
    while (k < n && isspace(var[k]))
    {
        ++k;
    }

    int i = 0;
    while (k < n && !isspace(var[k]))
    {
        name[i] = var[k];
        ++i;
        ++k;
    }
    name[i] = '\0';

    if (Find(name) >= 0)
    {
        return false;
    }
    else
    {
        mVector.push_back(name);
        return true;
    }
}

int Variables::Find(const char *var) const
{
    int r = 0;
    ConstIterator i(mVector.begin());
    while (i != mVector.end() && strcmp(*i, var) != 0)
    {
        ++i;
        ++r;
    }

    if (i == mVector.end())
    {
        r = -1;
    }

    return r;
}

static int ReadVariable(std::istream& in, const char *var)
{
    in >> std::ws;
    int r = 0;
    int i = 0;
    while (var[i] && var[i] == in.get())
    {
        ++i;
        ++r;
    }
    if (var[i])
    {
        r = 0;
    }
    return r;
}

int Variables::Read(std::istream& in) const
{
   std::streampos posbeg = in.tellg(), posend;
   int varCurrent = 0, var = -1;
   int lenCurrent, len;
   ConstIterator i = mVector.begin();
   while (i != mVector.end())
   {
        in.seekg(posbeg);
        lenCurrent = ReadVariable(in, *i);
        if (lenCurrent > 0)
        {
            var = varCurrent;
            len = lenCurrent;
            posend = in.tellg();
            break;
        }
        ++varCurrent;
        ++i;
   }

    while (i != mVector.end())
    {
        in.seekg(posbeg);
        lenCurrent = ReadVariable(in, *i);
        if (lenCurrent > len)
        {
            var = varCurrent;
            len = lenCurrent;
            posend = in.tellg();
        }
        ++varCurrent;
        ++i;
    }

    if (var >= 0)
    {
        in.seekg(posend);
    }
    else
    {
        in.seekg(posbeg);
    }

    return var;
}
