#pragma once

#include "triple.h"


template <typename MonomType>
class JanetTree
{
public:
    using TripleType = Triple<MonomType>;
    using Integer = typename MonomType::Integer;

public:
    ~JanetTree()
    {
        clear();
        delete root_;
    }

    const TripleType* find(const MonomType& monom) const
    {
        if (!root_)
        {
            return nullptr;
        }

        const TripleType* triple = nullptr;

        ConstIterator nodeIterator = root_;
        Integer degree = monom.degree();
        Integer var = 0;

        do
        {
            if (nodeIterator.degree() != monom[var] && nodeIterator.hasNextDegree())
            {
                nodeIterator.stepNextDegree();
            }

            if (nodeIterator.degree() != monom[var])
            {
                break;
            }
            else if (nodeIterator.hasNextVariable())
            {
                degree -= monom[var];
                if (!degree)
                {
                    break;
                }
                ++var;
                nodeIterator.stepNextVariable();
            }
            else
            {
                triple = nodeIterator.triple();
                break;
            }
        } while (true);

        return triple;
    }

    void insert(TripleType* triple)
    {
        if (!triple)
        {
            return;
        }

        Iterator nodeIterator = root_;
        Integer degree = triple->polynomLm().degree();
        if (!root_)
        {
            nodeIterator.build(degree, 0, triple);
            return;
        }

        Integer var = 0;
        do
        {
            while (nodeIterator.degree() < triple->polynomLm()[var] && nodeIterator.hasNextDegree())
            {
                nodeIterator.stepNextDegree();
            }

            if (nodeIterator.degree() > triple->polynomLm()[var])
            {
                nodeIterator.build(degree, var, triple);
                break;
            }
            else if (nodeIterator.degree() == triple->polynomLm()[var])
            {
                degree -= triple->polynomLm()[var];
                ++var;
                nodeIterator.stepNextVariable();
            }
            else
            {
                nodeIterator.stepNextDegree();
                nodeIterator.build(degree, var, triple);
                break;
            }
        } while (true);
    }

    void erase(const TripleType* triple)
    {
        if (!triple)
        {
            return;
        }

        Iterator nodeIterator = root_;
        Integer var = 0;
        unsigned bifurcations = 0;

        // count bifurcations
        if (nodeIterator.hasNextDegree() && nodeIterator.hasNextVariable())
        {
            ++bifurcations;
        }

        do
        {
            while (nodeIterator.degree() < triple->polynomLm()[var])
            {
                nodeIterator.stepNextDegree();
                if (nodeIterator.hasNextDegree() && nodeIterator.hasNextVariable())
                {
                    ++bifurcations;
                }
            }

            if (nodeIterator.hasNextVariable())
            {
                ++var;
                nodeIterator.stepNextVariable();
                if (nodeIterator.hasNextDegree() && nodeIterator.hasNextVariable())
                {
                    ++bifurcations;
                }
            }
            else
            {
                break;
            }
        } while (true);

        // remove node
        nodeIterator = root_;
        var = 0;
        bool varDirection = false;

        if (nodeIterator.hasNextDegree() && nodeIterator.hasNextVariable())
        {
            --bifurcations;
        }
        if (!bifurcations)
        {
            if (nodeIterator.degree() < triple->polynomLm()[var])
            {
                nodeIterator.stepNextDegree();
            }
            else
            {
                varDirection = true;
            }
        }

        while (bifurcations > 0)
        {
            while (nodeIterator.degree() < triple->polynomLm()[var] && bifurcations > 0)
            {
                nodeIterator.stepNextDegree();
                if (nodeIterator.hasNextDegree() && nodeIterator.hasNextVariable())
                {
                    --bifurcations;
                }
            }

            if (!bifurcations)
            {
                if (nodeIterator.degree() < triple->polynomLm()[var])
                {
                    nodeIterator.stepNextDegree();
                    break;
                }
                else
                {
                    varDirection = true;
                    break;
                }
            }

            ++var;
            nodeIterator.stepNextVariable();
            if (nodeIterator.hasNextDegree() && nodeIterator.hasNextVariable())
            {
                --bifurcations;
            }
            if (!bifurcations)
            {
                if (nodeIterator.degree() < triple->polynomLm()[var])
                {
                    nodeIterator.stepNextDegree();
                    break;
                }
                else
                {
                    varDirection = true;
                    break;
                }
            }
        }

        if (varDirection)
        {
            Iterator tmpIterator = nodeIterator;
            tmpIterator.stepNextVariable();
            tmpIterator.clear();
            nodeIterator.erase();
        }
        else
        {
            nodeIterator.clear();
        }
    }

    void clear()
    {
        if (root_)
        {
            Iterator nodeIterator = root_;
            nodeIterator.clear();
        }
    }

    std::set<Integer> nonMulti(const TripleType* triple) const
    {
        std::set<Integer> result;

        if (triple && root_)
        {
            ConstIterator nodeIterator = root_;
            Integer var = 0;

            do
            {
                while (nodeIterator.degree() < triple->polynomLm()[var])
                {
                    nodeIterator.stepNextDegree();
                }
                if (nodeIterator.hasNextDegree())
                {
                    result.insert(var);
                }

                ++var;
                if (nodeIterator.hasNextVariable())
                {
                    nodeIterator.stepNextVariable();
                }
                else
                {
                    break;
                }
            } while (true);
        }

        return result;
    }

private:
    struct Node
    {
        Integer degree;
        TripleType* currentTriple = nullptr;
        Node* nextDegree = nullptr;
        Node* nextVariable = nullptr;

        Node(Integer deg)
            : degree(deg)
        {
        }
    };

    class ConstIterator
    {
    public:
        ConstIterator(Node* node)
            : currentNode_(node)
        {
        }

        void stepNextDegree()
        {
            currentNode_ = currentNode_->nextDegree;
        }

        void stepNextVariable()
        {
            currentNode_ = currentNode_->nextVariable;
        }

        operator bool() const
        {
            return currentNode_;
        }

        bool hasNextDegree() const
        {
            return currentNode_->nextDegree;
        }

        bool hasNextVariable() const
        {
            return currentNode_->nextVariable;
        }

        const TripleType* triple() const
        {
            return currentNode_->currentTriple;
        }

        Integer degree() const
        {
            return currentNode_->degree;
        }

    private:
        Node* currentNode_;
    };

    class Iterator
    {
    public:
        Iterator(Node*& node)
            : currentNode_(&node)
        {
        }

        void stepNextDegree()
        {
            currentNode_ = &(*currentNode_)->nextDegree;
        }

        void stepNextVariable()
        {
            currentNode_ = &(*currentNode_)->nextVariable;
        }

        operator bool() const
        {
            return *currentNode_;
        }

        bool hasNextDegree() const
        {
            return (*currentNode_)->nextDegree;
        }

        bool hasNextVariable() const
        {
            return (*currentNode_)->nextVariable;
        }

        operator ConstIterator() const
        {
            return *currentNode_;
        }

        TripleType*& triple() const
        {
            return (*currentNode_)->currentTriple;
        }

        Integer degree() const
        {
            return (*currentNode_)->degree;
        }

        void build(Integer degree, Integer var, TripleType* triple)
        {
            if (!triple)
            {
                return;
            }

            Node* r =  new Node(triple->polynomLm()[var]);
            Node* j = r;
            while (degree > triple->polynomLm()[var])
            {
                degree -= triple->polynomLm()[var];
                ++var;
                j->nextVariable = new Node(triple->polynomLm()[var]);
                j = j->nextVariable;
            }
            j->currentTriple = triple;

            r->nextDegree = *currentNode_;
            *currentNode_ = r;
        }

        void erase()
        {
            if (*currentNode_)
            {
                Node* tmp = *currentNode_;
                *currentNode_ = tmp->nextDegree;
                delete tmp;
            }
        }

        void clear()
        {
            while (hasNextDegree())
            {
                if ((*currentNode_)->nextVariable)
                {
                    Iterator((*currentNode_)->nextVariable).clear();
                }
                erase();
            }

            if ((*currentNode_)->nextVariable)
            {
                Iterator((*currentNode_)->nextVariable).clear();
            }
            erase();
        }

    private:
        Node** currentNode_;
    };

private:
    Node* root_ = nullptr;
};
