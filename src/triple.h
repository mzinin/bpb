#pragma once

#include "fast_allocator.h"
#include "polynom.h"

#include <set>


template <typename MonomType>
class Triple
{
public:
    using PolynomType = Polynom<MonomType>;
    using Integer = typename MonomType::Integer;

public:
    Triple(PolynomType* initialPolynom)
        : polynomial_(initialPolynom)
    {
        if (polynomial_)
        {
            lm_ = &polynomial_->lm();
            ancestor_ = this;
        }
    }

    Triple(PolynomType* polynom,
           const Triple* ancestor,
           const std::set<Integer>& nmp,
           const Triple* weakAncestor,
           Integer nmVar)
        : variable_(nmVar)
    {
        if (polynom)
        {
            if (variable_ == -1)
            {
                polynomial_ = polynom;
                ancestor_ = ancestor ? ancestor : this;
            }
            else
            {
                polynomial_ = new PolynomType();
                (*polynomial_) += polynom->lm();

                ancestor_ = ancestor;
                weakAncestor_ = weakAncestor;
            }

            lm_ = &polynomial_->lm();
            nmp_ = nmp;
        }
    }

    ~Triple()
    {
        delete polynomial_;
    }

    void* operator new(std::size_t)
    {
        return allocator_.allocate();
    }

    void operator delete(void *ptr)
    {
        allocator_.free(ptr);
    }

    const PolynomType* polynom() const
    {
        return polynomial_;
    }

    PolynomType* polynom()
    {
        return polynomial_;
    }

    const MonomType& polynomLm() const
    {
        return *lm_;
    }

    const Triple* ancestor() const
    {
        return ancestor_;
    }

    const Triple* weakAncestor() const
    {
        return weakAncestor_;
    }

    Integer variable() const
    {
        return variable_;
    }

    const std::set<Integer>& nmp() const
    {
        return nmp_;
    }

    void setNmp(const std::set<Integer>& nmp)
    {
        nmp_ = nmp;
    }

    void setNmp(Integer variable)
    {
        nmp_.insert(variable);
    }

    bool testNmp(Integer variable) const
    {
        return nmp_.count(variable);
    }

    static bool compare(const Triple* tripleA, const Triple* tripleB)
    {
        return *tripleA->lm_ > *tripleB->lm_;
    }

private:
    const MonomType* lm_ = nullptr;
    PolynomType* polynomial_ = nullptr;
    const Triple* ancestor_ = nullptr;
    const Triple* weakAncestor_ = nullptr;
    std::set<Integer> nmp_;
    const Integer variable_ = -1;

    static FastAllocator allocator_;
};

template <typename MonomType>
FastAllocator Triple<MonomType>::allocator_(sizeof(Triple<MonomType>));
