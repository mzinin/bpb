#ifndef VARIABLES_H
#define VARIABLES_H

#include <cstring>
#include <iostream>
#include <vector>

class Variables 
{
public:
    typedef std::vector<const char*> Vector;
    typedef std::vector<const char*>::const_iterator ConstIterator;

private:
    Vector VariablesNames;

public:
    Variables();
    ~Variables();

    bool Add(const char* var);
    int Find(const char* var) const;
    int Read(std::istream& in) const;
    
    int Size() const;
    ConstIterator Begin() const;
    ConstIterator End() const;
    const char* Variable(int variableNumber) const;
};


inline int Variables::Size() const 
{ 
    return VariablesNames.size();
}

inline Variables::ConstIterator Variables::Begin() const
{ 
    return VariablesNames.begin();
}

inline Variables::ConstIterator Variables::End() const 
{ 
    return VariablesNames.end(); 
}

inline const char* Variables::Variable(int variableNumber) const 
{
    if (variableNumber >= Size())
    {
        variableNumber = 0;
    }
    return VariablesNames[variableNumber];
}

#endif // IVARIABLES_H
