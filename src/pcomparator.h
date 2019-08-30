#pragma once


template <class T>
class PointerLessComparator
{
public:
    bool operator() (const T* const& p1, const T* const& p2)
    {
        return *p1 < *p2;
    }
};


template <class T>
class PointerGreaterComparator
{
    public:
        bool operator() (const T* const& p1, const T* const& p2)
        {
            return *p1 > *p2;
        }
};
