#ifndef JANETTREE_H
#define JANETTREE_H

#include "triple.h"

class JanetTree
{
protected:
    struct Node
    {
        Monom::Integer nDegree;
        Triple* nTriple;
        Node* nNextDegree;
        Node* nNextVar;

        Node(Monom::Integer deg): nDegree(deg), nTriple(NULL), nNextDegree(NULL), nNextVar(NULL) {}
        ~Node() {}
    };

    class ConstIterator
    {
        Node* i;
    public:
        ConstIterator(Node* n): i(n) {}

        void StepDegree() { i = i->nNextDegree; }
        void StepVariable() { i = i->nNextVar; }
        operator bool() const { return (i != NULL); }
        ConstIterator NextDegree() const { return i->nNextDegree; }
        ConstIterator NextVariable() const { return i->nNextVar; }
        bool IsNextDegree() const { return i->nNextDegree; }
        bool IsNextVariable() const { return i->nNextVar; }
        const Triple* GetTriple() const { return i->nTriple; }
        Monom::Integer Degree() const { return i->nDegree; }
    };

    class Iterator
    {
        Node** i;

    public:
        Iterator(Node* &n): i(&n) {}

        void StepDegree() { i = &(*i)->nNextDegree; }
        void StepVariable() { i = &(*i)->nNextVar; }
        operator bool() const { return (*i != NULL); }
        ConstIterator NextDegree() const { return (*i)->nNextDegree; }
        ConstIterator NextVariable() const { return (*i)->nNextVar; }
        bool IsNextDegree() const { return (*i)->nNextDegree; }
        bool IsNextVariable() const { return (*i)->nNextVar; }
        operator ConstIterator() const { return *i; }
        Triple*& GetTriple() const { return (*i)->nTriple; }
        Monom::Integer Degree() const { return (*i)->nDegree; }
        void Build(Monom::Integer d, Monom::Integer var, Triple *trpl);
        void Delete();
        void Exclude();
        void Clear();
    };

    Node* jRoot;

public:
    JanetTree(): jRoot(NULL) {};
    ~JanetTree();

    const Triple* Find(const Monom& monom) const;
    void Insert(Triple *trpl);
    void Delete(const Triple *trpl);
    void Clear();

#ifdef USE_NOVA_INVOLUTION
    std::set<Monom::Integer> NMulti(const Triple* triple) const;
#endif
};


inline void JanetTree::Iterator::Delete()
{
    Node* tmp = *i;
    *i = tmp->nNextDegree;
    delete tmp;
}

inline void JanetTree::Iterator::Build(Monom::Integer d, Monom::Integer var, Triple *trpl)
{
    Node* r =  new JanetTree::Node(trpl->GetPolyLm()[var]);
    Node* j = r;
    while(d > trpl->GetPolyLm()[var])
    {
        d -= trpl->GetPolyLm()[var];
        var++;
        j->nNextVar = new JanetTree::Node(trpl->GetPolyLm()[var]);
        j = j->nNextVar;
    }
    j->nTriple = trpl;

    r->nNextDegree = *i;
    *i = r;
}

inline void JanetTree::Iterator::Clear()
{
    while (NextDegree())
    {
        if ((*i)->nNextVar)
        {
            JanetTree::Iterator((*i)->nNextVar).Clear();
        }
        Delete();
    }
    Delete();
}

#endif //JANETTREE_H
