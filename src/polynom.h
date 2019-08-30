#pragma once

#include "fast_allocator.h"

#include <iostream>
#include <sstream>
#include <stdexcept>


template <typename MonomType>
class Polynom
{
public:
    using Integer = typename MonomType::Integer;

public:
    Polynom() = default;

    Polynom(const Polynom& anotherPolynom)
    {
        if (!anotherPolynom.monomListHead_)
        {
            return;
        }

        MonomType **iterator = &monomListHead_,
                  *iteratorAnother = anotherPolynom.monomListHead_;
        while (iteratorAnother)
        {
            *iterator = new MonomType(*iteratorAnother);
            iterator = &((*iterator)->next);
            iteratorAnother = iteratorAnother->next;
        }
    }

    ~Polynom()
    {
        setZero();
    }

    void setOne()
    {
        setZero();
        monomListHead_ = new MonomType();
    }

    void setZero()
    {
        if (monomListHead_)
        {
            MonomType* tmpMonom = nullptr;
            while (monomListHead_)
            {
                tmpMonom = monomListHead_;
                monomListHead_ = monomListHead_->next;
                delete tmpMonom;
            }
        }
    }

    bool isZero() const
    {
        return !monomListHead_;
    }

    unsigned long length() const
    {
        unsigned long length = 0;
        MonomType* iterator = monomListHead_;
        while (iterator)
        {
            iterator = iterator->next;
            ++length;
        }
        return length;
    }

    Integer degree() const
    {
        return monomListHead_ ? monomListHead_->degree() : 0;
    }

    const MonomType& lm() const
    {
        return monomListHead_ ? *monomListHead_ : uniteMonom_;
    }

    void ridOfLm()
    {
        if (monomListHead_)
        {
            MonomType* tmpMonom = monomListHead_;
            monomListHead_ = monomListHead_->next;
            delete tmpMonom;
        }
    }

    void* operator new(std::size_t)
    {
        return allocator_.allocate();
    }

    void operator delete(void *ptr)
    {
        allocator_.free(ptr);
    }

    const Polynom& operator=(const Polynom& anotherPolynom)
    {
        if (!anotherPolynom.monomListHead_)
        {
            setZero();
        }
        else
        {
            MonomType *iteratorAnother = anotherPolynom.monomListHead_,
                      **iterator = &monomListHead_;
            while (*iterator && iteratorAnother)
            {
                **iterator = *iteratorAnother;
                iterator = &((*iterator)->next);
                iteratorAnother = iteratorAnother->next;
            }

            if (*iterator)
            {
                MonomType* monomToDelete = *iterator;
                *iterator = nullptr;
                while (monomToDelete)
                {
                    iteratorAnother = monomToDelete;
                    monomToDelete = monomToDelete->next;
                    delete iteratorAnother;
                }
            }
            else while (iteratorAnother)
            {
                *iterator = new MonomType(*iteratorAnother);
                iterator = &((*iterator)->next);
                iteratorAnother = iteratorAnother->next;
            }
        }
        return *this;
    }

    const Polynom& operator+=(const MonomType& newMonom)
    {
        MonomType** position = find(newMonom);
        MonomType* tmpMonom = nullptr;

        if (!position)
        {
            tmpMonom = new MonomType(newMonom);
            tmpMonom->next = monomListHead_;
            monomListHead_ = tmpMonom;
        }
        else
        {
            if (*position && **position == newMonom)
            {
                tmpMonom = *position;
                *position = (*position)->next;
                delete tmpMonom;
            }
            else
            {
                tmpMonom = new MonomType(newMonom);
                tmpMonom->next = (*position)->next;
                (*position)->next = tmpMonom;
            }
        }

        return *this;
    }

    const Polynom& operator+=(const Polynom& anotherPolynom)
    {
        if (anotherPolynom.monomListHead_)
        {
            MonomType **iterator = &monomListHead_,
                      *iteratorAnother = anotherPolynom.monomListHead_,
                      *tmpMonom = nullptr;

            while (*iterator && iteratorAnother)
            {
                switch ((**iterator).compare(*iteratorAnother))
                {
                    case -1:
                        tmpMonom = new MonomType(*iteratorAnother);
                        tmpMonom->next = *iterator;
                        *iterator = tmpMonom;
                        iterator = &(tmpMonom->next);
                        iteratorAnother = iteratorAnother->next;
                        break;

                    case 0:
                        tmpMonom = *iterator;
                        *iterator = (*iterator)->next;
                        delete tmpMonom;
                        iteratorAnother = iteratorAnother->next;
                        break;

                    case 1:
                        iterator = &((*iterator)->next);
                        break;
                }
            }

            while (iteratorAnother)
            {
                *iterator = new MonomType(*iteratorAnother);
                iterator = &((*iterator)->next);
                iteratorAnother = iteratorAnother->next;
            }
        }
        return *this;
    }

    const Polynom& operator*=(Integer var)
    {
        if (monomListHead_)
        {
            Polynom<MonomType> polynomWithVar;
            MonomType **iterator = &monomListHead_,
                      **iteratorWithVar = &polynomWithVar.monomListHead_;

            while (*iterator)
            {
                if ((**iterator)[var])
                {
                    *iteratorWithVar = *iterator;
                    *iterator = (*iterator)->next;
                    (*iteratorWithVar)->next = nullptr;
                    iteratorWithVar = &((*iteratorWithVar)->next);
                }
                else
                {
                    iterator = &((*iterator)->next);
                }
            }

            iterator = &monomListHead_;
            while (*iterator)
            {
                **iterator *= var;
                iterator = &((*iterator)->next);
            }

            mergeWith(polynomWithVar);
        }
        return *this;
    }

    const Polynom& operator*=(const MonomType& anotherMonom)
    {
        if (monomListHead_)
        {
            for (Integer i = 0; i < anotherMonom.dimIndepend(); ++i)
            {
                if (anotherMonom[i])
                {
                    *this *= i;
                }
            }
        }
        return *this;
    }

    const Polynom& operator*=(const Polynom& anotherPolynom)
    {
        if (monomListHead_)
        {
            Polynom<MonomType> *tmpPolynom = nullptr,
                               *tmpResult = new Polynom<MonomType>();
            MonomType* iteratorAnother = anotherPolynom.monomListHead_;

            while (iteratorAnother)
            {
                tmpPolynom = new Polynom<MonomType>(*this);
                *tmpPolynom *= *iteratorAnother;
                tmpResult->mergeWith(*tmpPolynom);
                delete tmpPolynom;
                iteratorAnother = iteratorAnother->next;
            }
            setZero();
            monomListHead_ = tmpResult->monomListHead_;
            tmpResult->monomListHead_ = nullptr;
            delete tmpResult;
        }
        return *this;
    }

    bool operator==(const Polynom& anotherPolynom) const
    {
        MonomType *iterator = monomListHead_,
                  *anotherIterator = anotherPolynom.monomListHead_;

        while (iterator && anotherIterator)
        {
            if (*iterator != *anotherIterator)
            {
                break;
            }
            iterator = iterator->next;
            anotherIterator = anotherIterator->next;
        }
        return !iterator && !anotherIterator;
    }

    bool operator!=(const Polynom& anotherPolynom) const
    {
        return !(*this == anotherPolynom);
    }

    bool operator<(const Polynom& anotherPolynom) const
    {
        MonomType *iterator = monomListHead_,
                  *anotherIterator = anotherPolynom.monomListHead_;

        while (iterator && anotherIterator)
        {
            switch ((*iterator).compare(*anotherIterator))
            {
                case -1:
                    return true;

                case 1:
                    return false;

                case 0:
                    iterator = iterator->next;
                    anotherIterator = anotherIterator->next;
                    break;
            }
        }
        return !iterator && !anotherIterator;
    }

    bool operator>(const Polynom& anotherPolynom) const
    {
        MonomType *iterator = monomListHead_,
                  *anotherIterator = anotherPolynom.monomListHead_;

        while (iterator && anotherIterator)
        {
            switch ((*iterator).compare(*anotherIterator))
            {
                case -1:
                    return false;

                case 1:
                    return true;

                case 0:
                    iterator = iterator->next;
                    anotherIterator = anotherIterator->next;
                    break;
            }
        }
        return iterator && !anotherIterator;
    }

    static int compare(const Polynom& polynomA, const Polynom& polynomB)
    {
        MonomType *iteratorA = polynomA.monomListHead_,
                  *iteratorB = polynomB.monomListHead_;

        while (iteratorA && iteratorB)
        {
            switch ((*iteratorA).compare(*iteratorB))
            {
                case -1:
                    return -1;

                case 1:
                    return 1;

                case 0:
                    iteratorA = iteratorA->next;
                    iteratorB = iteratorB->next;
                    break;
            }
        }

        if (iteratorA)
        {
            return 1;
        }
        if (iteratorB)
        {
            return -1;
        }
        return 0;
    }

    void reduction(const Polynom& anotherPolynom)
    {
        if (monomListHead_ && anotherPolynom.monomListHead_)
        {
            MonomType* tmpMonom = new MonomType();
            Polynom<MonomType>* tmpPolynom = nullptr;
            MonomType* iterator = monomListHead_;
            const MonomType& anotherLm = anotherPolynom.lm();

            while (iterator)
            {
                if (iterator->isDivisibleBy(anotherLm))
                {
                    tmpMonom->setQuotientOf(*iterator, anotherLm);
                    tmpPolynom = new Polynom<MonomType>(anotherPolynom);
                    *tmpPolynom *= *tmpMonom;
                    mergeWith(*tmpPolynom);
                    delete tmpPolynom;
                    iterator = monomListHead_;
                }
                else
                {
                    break;
                }
            }

            if (monomListHead_)
            {
                MonomType* iterator2 = iterator;
                iterator = iterator->next;
                while (iterator)
                {
                    if (iterator->isDivisibleBy(anotherLm))
                    {
                        tmpMonom->setQuotientOf(*iterator, anotherLm);
                        tmpPolynom = new Polynom<MonomType>(anotherPolynom);
                        *tmpPolynom *= *tmpMonom;
                        mergeWith(*tmpPolynom);
                        delete tmpPolynom;
                        iterator = iterator2->next;
                    }
                    else
                    {
                        iterator2 = iterator2->next;
                        iterator = iterator2->next;
                    }
                }
            }
            delete tmpMonom;
        }
    }

    void headReduction(const Polynom& anotherPolynom)
    {
        if (monomListHead_ && anotherPolynom.monomListHead_)
        {
            MonomType* tmpMonom = new MonomType();
            Polynom<MonomType>* tmpPolynom = nullptr;
            MonomType* iterator = monomListHead_;
            const MonomType& anotherLm = anotherPolynom.lm();

            while (iterator)
            {
                if (iterator->isDivisibleBy(anotherLm))
                {
                    tmpMonom->setQuotientOf(*iterator, anotherLm);
                    tmpPolynom = new Polynom<MonomType>(anotherPolynom);
                    *tmpPolynom *= *tmpMonom;
                    mergeWith(*tmpPolynom);
                    delete tmpPolynom;
                    iterator = monomListHead_;
                }
                else
                {
                    break;
                }
            }
            delete tmpMonom;
        }
    }

    std::string toString() const
    {
        std::stringstream tmpStream;
        tmpStream << *this;
        return tmpStream.str();
    }

    template <typename SomeMonomType>
    friend std::ostream& operator<<(std::ostream& out, const Polynom<SomeMonomType>& polynom);

    template <typename SomeMonomType>
    friend std::istream& operator>>(std::istream& in, Polynom<SomeMonomType>& polynom);

private:
    MonomType** find(const MonomType& monom)
    {
        if (!monomListHead_ || *monomListHead_ < monom)
        {
            return nullptr;
        }

        MonomType** previousPointer = &monomListHead_;
        MonomType** currentPointer = nullptr;
        unsigned long range(length()), middle;

        while ((middle = range >> 1) > 0)
        {
            currentPointer = previousPointer;
            for (unsigned long i = 0; i < middle; ++i)
            {
                currentPointer = &((*currentPointer)->next);
            }

            switch ((**currentPointer).compare(monom))
            {
            case 1:
                previousPointer = currentPointer;
                range -= middle;
                break;

            case -1:
                range = middle;
                break;

            case 0:
                return currentPointer;
            }
        }
        return previousPointer;
    }

    void mergeWith(Polynom& anotherPolynom)
    {
        MonomType **iterator = &monomListHead_,
                  *iteratorAnother = anotherPolynom.monomListHead_,
                  *tmpPointer = nullptr;

        while (*iterator && iteratorAnother)
        {
            switch ((**iterator).compare(*iteratorAnother))
            {
            case -1:
                tmpPointer = iteratorAnother;
                iteratorAnother = iteratorAnother->next;
                tmpPointer->next = *iterator;
                *iterator = tmpPointer;
                iterator = &(tmpPointer->next);
                break;

            case 0:
                tmpPointer = *iterator;
                *iterator = (*iterator)->next;
                delete tmpPointer;
                tmpPointer = iteratorAnother;
                iteratorAnother = iteratorAnother->next;
                delete tmpPointer;
                break;

            case 1:
                iterator = &((*iterator)->next);
                break;
            }
        }

        if (iteratorAnother)
        {
            *iterator = iteratorAnother;
        }
        anotherPolynom.monomListHead_ = nullptr;
    }

    void additive(std::istream& in)
    {
        multiplicative(in);

        int op = (in >> std::ws).peek();
        Polynom<MonomType> tmpPolynom;
        while (op == '+' || op == '-')
        {
            in.get();
            tmpPolynom.multiplicative(in);
            *this += tmpPolynom;
            op = in.peek();
        }
    }

    void multiplicative(std::istream& in)
    {
        unary(in);

        int op = (in >> std::ws).peek();
        Polynom<MonomType> tmpPolynom;
        while (op == '*')
        {
            in.get();
            tmpPolynom.unary(in);
            *this *= tmpPolynom;
            op = in.peek();
        }
    }

    void unary(std::istream& in)
    {
        int ch = (in >> std::ws).peek();
        if (ch != '+' && ch != '-')
        {
            bracket(in);
        }
        else
        {
            do
            {
                ch = (in >> std::ws).peek();
            } while (ch == '+' || ch == '-');
            bracket(in);
        }
    }

    void bracket(std::istream& in)
    {
        int op = (in >> std::ws).peek();
        if (op == '(')
        {
            in.get();
            additive(in);
            if (in.get() != ')')
            {
                std::cerr << "expected ')'" << std::endl;
                throw std::invalid_argument("expected ')' while polynom parsing");
            }
        }
        else
        {
            setOne();
            MonomType* tmpMonom = new MonomType();
            in >> *tmpMonom;
            if (!in.fail())
            {
                *this *= *tmpMonom;
                delete tmpMonom;
            }
            else
            {
                delete tmpMonom;
                in.clear();
                if (in.get() != '1')
                {
                    std::cerr << "expected 'monomial'" << std::endl;
                    throw std::invalid_argument("expected monomial while polynom parsing");
                }
            }
        }
    }

private:
    MonomType* monomListHead_ = nullptr;

    static FastAllocator allocator_;
    static MonomType uniteMonom_;
};


template <typename MonomType>
FastAllocator Polynom<MonomType>::allocator_(sizeof(Polynom<MonomType>));

template <typename MonomType>
MonomType Polynom<MonomType>::uniteMonom_;


template <typename MonomType>
std::ostream& operator<<(std::ostream& out, const Polynom<MonomType>& polynom)
{
    if (!polynom.monomListHead_)
    {
        out << "0";
    }
    else
    {
        MonomType* iteratorA(polynom.monomListHead_);
        out << *iteratorA;
        iteratorA = iteratorA->next;
        while (iteratorA)
        {
            out << " + " << *iteratorA;
            iteratorA = iteratorA->next;
        }
    }

    return out;
}

template <typename MonomType>
std::istream& operator>>(std::istream& in, Polynom<MonomType>& polynom)
{
    polynom.additive(in);
    return in;
}
