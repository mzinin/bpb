#ifndef JANETTREE_H
#define JANETTREE_H

#include "triple.h"

using namespace std;

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

        void step_deg() { i = i->nNextDegree; }
        void step_var() { i = i->nNextVar; }
        operator bool() const { return (i != NULL); }
        ConstIterator nextDegree() const { return i->nNextDegree; }
        ConstIterator nextVar() const { return i->nNextVar; }
        bool isNextDegree() const { return i->nNextDegree; }
        bool isNextVar() const { return i->nNextVar; }
        Triple* trpl() const { return i->nTriple; }
        Monom::Integer degree() const { return i->nDegree; }
    };

    class Iterator
    {
        Node** i;

    public:
        Iterator(Node* &n): i(&n) {}

        void step_deg() { i = &(*i)->nNextDegree; }
        void step_var() { i = &(*i)->nNextVar; }
        operator bool() const { return (*i != NULL); }
        ConstIterator nextDegree() const { return (*i)->nNextDegree; }
        ConstIterator nextVar() const { return (*i)->nNextVar; }
        bool isNextDegree() const { return (*i)->nNextDegree; }
        bool isNextVar() const { return (*i)->nNextVar; }
        operator ConstIterator() const { return *i; }
        Triple*& trpl() const { return (*i)->nTriple; }
        Monom::Integer degree() const { return (*i)->nDegree; }
        void build(Monom::Integer d, Monom::Integer var, Triple *trpl);
        void del();
        void exclude();
        void clear();
    };

    Node* jRoot;

public:
    JanetTree(): jRoot(NULL) {};
    ~JanetTree();

    Triple* find(const Monom& monom) const;
    void insert(Triple *trpl);
    void del(Triple *trpl);
    void clear();
};


inline void JanetTree::Iterator::del()
{
    Node* tmp = *i;
    *i = tmp->nNextDegree;
    delete tmp;
}

inline void JanetTree::Iterator::build(Monom::Integer d, Monom::Integer var, Triple *trpl)
{
    Node* r =  new JanetTree::Node(trpl->getPolyLm()[var]);
    Node* j = r;
    while(d > trpl->getPolyLm()[var])
    {
        d -= trpl->getPolyLm()[var];
        var++;
        j->nNextVar = new JanetTree::Node(trpl->getPolyLm()[var]);
        j = j->nNextVar;
    }
    j->nTriple = trpl;

    r->nNextDegree = *i;
    *i = r;
}

inline void JanetTree::Iterator::clear()
{
    while (nextDegree())
    {
        if ((*i)->nNextVar)
        {
            JanetTree::Iterator((*i)->nNextVar).clear();
        }
        del();
    }
    del();
}

#endif //JANETTREE_H
