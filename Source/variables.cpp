#include <iostream>

#include "variables.h"

namespace
{
    int ReadVariable(std::istream& in, const char* var)
    {
        in >> std::ws;
        int commonLength = 0;
        int i = 0;
        while (var[i] && var[i] == in.get())
        {
            ++i;
            ++commonLength;
        }
        if (var[i])
        {
            commonLength = 0;
        }
        return commonLength;
    }
}

Variables::Variables()
    : VariablesNames()
{
}

Variables::~Variables()
{
    for (register unsigned i = 0; i < Size(); ++i)
    {
        delete VariablesNames[i];
    }
    VariablesNames.clear();
}

bool Variables::Add(const char* var)
{
    int varLength = strlen(var);
    char *name = new char[varLength + 1];
    int k = 0;
    while (k < varLength && isspace(var[k]))
    {
        ++k;
    }

    int i = 0;
    while (k < varLength && !isspace(var[k]))
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
        VariablesNames.push_back(name);
        return true;
    }
}

int Variables::Find(const char *var) const
{
    int position = 0;
    ConstIterator i(VariablesNames.begin());
    while (i != VariablesNames.end() && strcmp(*i, var) != 0)
    {
        ++i;
        ++position;
    }

    if (i == VariablesNames.end())
    {
        position = -1;
    }

    return position;
}

int Variables::Read(std::istream& in) const
{
   std::streampos startPosition = in.tellg(), endPosition = 0;
   int currentVariable = 0, foundVariable = -1;
   int currentCommonLength = 0, maxCommonLength = 0;
   ConstIterator i = VariablesNames.begin();
   while (i != VariablesNames.end())
   {
        in.seekg(startPosition);
        currentCommonLength = ReadVariable(in, *i);
        if (currentCommonLength > 0)
        {
            foundVariable = currentVariable;
            maxCommonLength = currentCommonLength;
            endPosition = in.tellg();
            break;
        }
        ++currentVariable;
        ++i;
   }

    while (i != VariablesNames.end())
    {
        in.seekg(startPosition);
        currentCommonLength = ReadVariable(in, *i);
        if (currentCommonLength > maxCommonLength)
        {
            foundVariable = currentVariable;
            maxCommonLength = currentCommonLength;
            endPosition = in.tellg();
        }
        ++currentVariable;
        ++i;
    }

    if (foundVariable >= 0)
    {
        in.seekg(endPosition);
    }
    else
    {
        in.seekg(startPosition);
    }

    return foundVariable;
}
