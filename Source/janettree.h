#ifndef JANETTREE_H
#define JANETTREE_H

#include "triple.h"

class JanetTree
{
protected:
    struct Node
    {
        Monom::Integer Degree;
        Triple* CurrentTriple;
        Node* NextDegree;
        Node* NextVariable;

        Node(Monom::Integer degree);
        ~Node();
    };

    class ConstIterator
    {
    private:
        Node* CurrentNode;

    public:
        ConstIterator(Node* node);
        ~ConstIterator();

        void StepNextDegree();
        void StepNextVariable();
        operator bool() const;
        ConstIterator GetNextDegree() const;
        ConstIterator GetNextVariable() const;
        bool HasNextDegree() const;
        bool HasNextVariable() const;
        const Triple* GetTriple() const;
        Monom::Integer GetDegree() const;
    };

    class Iterator
    {
    private:
        Node** CurrentNode;

    public:
        Iterator(Node* &node);
        ~Iterator();

        void StepNextDegree();
        void StepNextVariable();
        operator bool() const;
        ConstIterator GetNextDegree() const;
        ConstIterator GetNextVariable() const;
        bool HasNextDegree() const;
        bool HasNextVariable() const;
        operator ConstIterator() const;
        Triple*& GetTriple() const;
        Monom::Integer GetDegree() const;
        void Build(Monom::Integer degree, Monom::Integer var, Triple *triple);
        void Delete();
        void Exclude();
        void Clear();
    };

    Node* Root;

public:
    JanetTree();
    ~JanetTree();

    const Triple* Find(const Monom& monom) const;
    void Insert(Triple *triple);
    void Delete(const Triple *triple);
    void Clear();

    std::set<Monom::Integer> NonMulti(const Triple* triple) const;
};


inline JanetTree::Node::Node(Monom::Integer degree)
    : Degree(degree)
    , CurrentTriple(0)
    , NextDegree(0)
    , NextVariable(0)
{
}

inline JanetTree::Node::~Node()
{
}

inline JanetTree::ConstIterator::ConstIterator(Node* node)
    : CurrentNode(node)
{
}

inline JanetTree::ConstIterator::~ConstIterator()
{
}

inline void JanetTree::ConstIterator::StepNextDegree()
{
    CurrentNode = CurrentNode->NextDegree;
}

inline void JanetTree::ConstIterator::StepNextVariable()
{
    CurrentNode = CurrentNode->NextVariable;
}

inline JanetTree::ConstIterator::operator bool() const
{
    return CurrentNode;
}

inline JanetTree::ConstIterator JanetTree::ConstIterator::GetNextDegree() const
{
    return CurrentNode->NextDegree;
}

inline JanetTree::ConstIterator JanetTree::ConstIterator::GetNextVariable() const
{
    return CurrentNode->NextVariable;
}

inline bool JanetTree::ConstIterator::HasNextDegree() const
{
    return CurrentNode->NextDegree;
}

inline bool JanetTree::ConstIterator::HasNextVariable() const
{
    return CurrentNode->NextVariable;
}

inline const Triple* JanetTree::ConstIterator::GetTriple() const
{
    return CurrentNode->CurrentTriple;
}

inline Monom::Integer JanetTree::ConstIterator::GetDegree() const
{
    return CurrentNode->Degree;
}

inline JanetTree::Iterator::Iterator(Node* &node)
    : CurrentNode(&node)
{
}

inline JanetTree::Iterator::~Iterator()
{
}

inline void JanetTree::Iterator::StepNextDegree()
{
    CurrentNode = &(*CurrentNode)->NextDegree;
}

inline void JanetTree::Iterator::StepNextVariable()
{
    CurrentNode = &(*CurrentNode)->NextVariable;
}

inline JanetTree::Iterator::operator bool() const
{
    return *CurrentNode;
}

inline JanetTree::ConstIterator JanetTree::Iterator::GetNextDegree() const
{
    return (*CurrentNode)->NextDegree;
}

inline JanetTree::ConstIterator JanetTree::Iterator::GetNextVariable() const
{
    return (*CurrentNode)->NextVariable;
}

inline bool JanetTree::Iterator::HasNextDegree() const
{
    return (*CurrentNode)->NextDegree;
}

inline bool JanetTree::Iterator::HasNextVariable() const
{
    return (*CurrentNode)->NextVariable;
}

inline JanetTree::Iterator::operator JanetTree::ConstIterator() const
{
    return *CurrentNode;
}

inline Triple*& JanetTree::Iterator::GetTriple() const
{
    return (*CurrentNode)->CurrentTriple;
}

inline Monom::Integer JanetTree::Iterator::GetDegree() const
{
    return (*CurrentNode)->Degree;
}

inline void JanetTree::Iterator::Build(Monom::Integer degree, Monom::Integer var, Triple *triple)
{
    Node* r =  new JanetTree::Node(triple->GetPolyLm()[var]);
    Node* j = r;
    while(degree > triple->GetPolyLm()[var])
    {
        degree -= triple->GetPolyLm()[var];
        ++var;
        j->NextVariable = new JanetTree::Node(triple->GetPolyLm()[var]);
        j = j->NextVariable;
    }
    j->CurrentTriple = triple;

    r->NextDegree = *CurrentNode;
    *CurrentNode = r;
}

inline void JanetTree::Iterator::Delete()
{
    Node* tmp = *CurrentNode;
    *CurrentNode = tmp->NextDegree;
    delete tmp;
}

inline void JanetTree::Iterator::Clear()
{
    while (HasNextDegree())
    {
        if ((*CurrentNode)->NextVariable)
        {
            JanetTree::Iterator((*CurrentNode)->NextVariable).Clear();
        }
        Delete();
    }
    Delete();
}

#endif //JANETTREE_H
