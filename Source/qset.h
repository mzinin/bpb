#ifndef QSET_H
#define QSET_H

#include "triple.h"
#include <list>
#include <algorithm>

class QSET
{
private:
    std::list<Triple*> tripleList;

public:
    QSET();
    QSET(const std::list<Polynom*>& basis);
    ~QSET();

    void Insert(std::list<Polynom*>& addList);
    void Insert(std::list<Triple*>& addList);
#ifdef USE_NOVA_INVOLUTION
    void Update(Triple* newTriple, const std::set<Monom::Integer>& nonMultiVars, std::list<Triple*>& set);
#else
    void Update(Triple* newTriple, const std::list<Triple*>& set);
#endif
    Triple* Get();

    bool Empty() const;
    std::size_t Size() const;
    void DeleteDescendants(const Triple* ancestor);
};

inline bool QSET::Empty() const
{
    return tripleList.empty();
}

inline std::size_t QSET::Size() const
{
    return tripleList.size();
}

#endif // QSET_H
