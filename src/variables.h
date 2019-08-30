#pragma once

#include <cstdint>
#include <deque>
#include <string>


class Variables
{
public:
    using ConstIterator = std::deque<std::string>::const_iterator;

public:
    bool add(const std::string& var);
    int find(const std::string& var) const;
    int read(std::istream& in) const;

    uint16_t size() const;
    ConstIterator begin() const;
    ConstIterator end() const;
    const std::string& variable(uint16_t variableNumber) const;

private:
    std::deque<std::string> variablesNames_;
};


inline uint16_t Variables::size() const
{
    return static_cast<uint16_t>(variablesNames_.size());
}

inline Variables::ConstIterator Variables::begin() const
{
    return variablesNames_.begin();
}

inline Variables::ConstIterator Variables::end() const
{
    return variablesNames_.end();
}

inline const std::string& Variables::variable(uint16_t variableNumber) const
{
    if (variableNumber >= size())
    {
        variableNumber = 0;
    }
    return variablesNames_[variableNumber];
}
