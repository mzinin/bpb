#ifndef VARIABLES_H
#define VARIABLES_H

#include <cstring>
#include <deque>
#include <iostream>
#include <string>

class Variables 
{
public:
    typedef std::deque<std::string> Vector;
    typedef std::deque<std::string>::const_iterator ConstIterator;

    Variables();
    ~Variables();

    bool Add(const std::string& var);
    int Find(const std::string& var) const;
    int Read(std::istream& in) const;
    
    int Size() const;
    ConstIterator Begin() const;
    ConstIterator End() const;
    const std::string& Variable(int variableNumber) const;

private:
    Vector VariablesNames;
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

inline const std::string& Variables::Variable(int variableNumber) const 
{
    if (variableNumber >= Size())
    {
        variableNumber = 0;
    }
    return VariablesNames[variableNumber];
}

#endif // IVARIABLES_H
