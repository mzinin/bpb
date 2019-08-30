#pragma once

#include "triple.h"

#include <algorithm>
#include <list>


template <typename MonomType>
class QSet
{
public:
    using PolynomType = Polynom<MonomType>;
    using TripleType = Triple<MonomType>;

public:
    QSet() = default;

    QSet(const std::list<PolynomType*>& basis)
    {
        insert(basis);
    }

    ~QSet()
    {
        clear();
    }

    void insert(const std::list<PolynomType*>& addList)
    {
        for (auto* item : addList)
        {
            if (item)
            {
                tripleList_.push_back(new TripleType(item));
            }
        }
        tripleList_.sort(TripleType::compare);
    }

    void insert(std::list<TripleType*>& addList)
    {
        addList.sort(TripleType::compare);
        tripleList_.merge(addList, TripleType::compare);
    }

    TripleType* get()
    {
        auto* result = tripleList_.back();
        tripleList_.pop_back();
        return result;
    }

    void clear()
    {
        for (auto* item : tripleList_)
        {
            delete item;
        }
        tripleList_.clear();
    }

    bool empty() const
    {
        return tripleList_.empty();
    }

    std::size_t size() const
    {
        return tripleList_.size();
    }

    void deleteDescendants(const TripleType* ancestor)
    {
        if (!ancestor)
        {
            return;
        }

        for (auto it = tripleList_.begin(); it != tripleList_.end();)
        {
            if ((**it).ancestor() == ancestor || (**it).weakAncestor() == ancestor)
            {
                delete *it;
                it = tripleList_.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

private:
    std::list<TripleType*> tripleList_;
};
