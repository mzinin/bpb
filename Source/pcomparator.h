#ifndef PCOMPARATOR_H
#define PCOMPARATOR_H

template<class T> class PointerLessComparator
{
public:
    bool operator() (const T* const& p1, const T* const& p2)
    {
        return *p1 < *p2;
    }
};

template<class T> class PointerMoreComparator
{
    public:
        bool operator() (const T* const& p1, const T* const& p2)
        {
            return *p1 > *p2;
        }
};

#endif //PCONPARATOR_H
