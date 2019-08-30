#include "variables.h"

#include <cctype>
#include <iostream>


namespace
{
    int readVariable(std::istream& in, const std::string& var)
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

bool Variables::add(const std::string& var)
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

    if (find(name) >= 0)
    {
        return false;
    }

    variablesNames_.push_back(name);
    return true;
}

int Variables::find(const std::string& var) const
{
    int position = 0;
    ConstIterator i(variablesNames_.begin());
    while (i != variablesNames_.end() && *i != var)
    {
        ++i;
        ++position;
    }

    if (i == variablesNames_.end())
    {
        position = -1;
    }

    return position;
}

int Variables::read(std::istream& in) const
{
   std::streampos startPosition = in.tellg(), endPosition = 0;
   int currentVariable = 0, foundVariable = -1;
   int currentCommonLength = 0, maxCommonLength = 0;
   ConstIterator i = variablesNames_.begin();

   while (i != variablesNames_.end())
   {
        in.seekg(startPosition);
        currentCommonLength = readVariable(in, *i);
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

    while (i != variablesNames_.end())
    {
        in.seekg(startPosition);
        currentCommonLength = readVariable(in, *i);
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
