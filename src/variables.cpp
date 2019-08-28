#include <iostream>

#include "variables.h"

namespace
{
    int ReadVariable(std::istream& in, const std::string& var)
    {
        in >> std::ws;
        int commonLength = 0;
        int i = 0;
        while (i < var.size() && var[i] == in.get())
        {
            ++i;
            ++commonLength;
        }
        if (i != var.size())
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
}

bool Variables::Add(const std::string& var)
{
    size_t k = 0;
    while (k < var.size() && isspace(var[k]))
    {
        ++k;
    }

    std::string name;
    while (k < var.size() && !isspace(var[k]))
    {
        name += var[k];
        ++k;
    }

    if (Find(name) >= 0)
    {
        return false;
    }

    VariablesNames.push_back(name);
    return true;
}

int Variables::Find(const std::string& var) const
{
    int position = 0;
    ConstIterator i(VariablesNames.begin());
    while (i != VariablesNames.end() && *i != var)
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
