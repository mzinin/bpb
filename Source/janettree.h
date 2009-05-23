#ifndef JANETTREE_H
#define JANETTREE_H

#include <iostream>
#include "triple.h"

using namespace std;

class JanetTree
{
public:
    struct Node
    {
        Monom::Integer mDeg;
        Triple* mTriple;
        Node* mNextDeg;
        Node* mNextVar;

        Node(Monom::Integer deg): mDeg(deg), mTriple(NULL), mNextDeg(NULL), mNextVar(NULL) {}
        ~Node() {}
    };

private:
    class ConstIterator
    {
        Node* i;
    public:
        ConstIterator(Node* n): i(n) {}

        void step_deg() { i = i->mNextDeg; }
        void step_var() { i = i->mNextVar; }
        operator bool() const { return (i != NULL); }
        ConstIterator nextDeg() const { return i->mNextDeg; }
        ConstIterator nextVar() const { return i->mNextVar; }
        bool isNextDeg() const { return i->mNextDeg; }
        bool isNextVar() const { return i->mNextVar; }
        Triple* trpl() const { return i->mTriple; }
        Monom::Integer degree() const { return i->mDeg; }
    };

    class Iterator
    {
        Node** i;

    public:
        Iterator(Node* &n): i(&n) {}

        void step_deg() { i = &(*i)->mNextDeg; }
        void step_var() { i = &(*i)->mNextVar; }
        operator bool() const { return (*i != NULL); }
        ConstIterator nextDeg() const { return (*i)->mNextDeg; }
        ConstIterator nextVar() const { return (*i)->mNextVar; }
        bool isNextDeg() const { return (*i)->mNextDeg; }
        bool isNextVar() const { return (*i)->mNextVar; }
        operator ConstIterator() const { return *i; }
        Triple*& trpl() const { return (*i)->mTriple; }
        Monom::Integer degree() const { return (*i)->mDeg; }
        void build(Monom::Integer d, Monom::Integer var, Triple *trpl);
        void del();
        void exclude();
        void clear();
    };

    Node* mRoot;

public:
    JanetTree(): mRoot(NULL) {};
    ~JanetTree();

    Triple* find(const Monom& m) const;
    void insert(Triple *trpl);
    void del(Triple *trpl);
    void clear();
    set<Monom::Integer> nmulti(Triple *trpl);
};


inline void JanetTree::Iterator::del()
{
    Node* tmp = *i;
    *i = tmp->mNextDeg;
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
        j->mNextVar = new JanetTree::Node(trpl->getPolyLm()[var]);
        j = j->mNextVar;
    }
    j->mTriple = trpl;

    r->mNextDeg = *i;
    *i = r;
}

inline void JanetTree::Iterator::clear()
{
    while (nextDeg())
    {
        if ((*i)->mNextVar)
        {
            JanetTree::Iterator((*i)->mNextVar).clear();
        }
        del();
    }
    del();
}

#endif //JANETTREE_H
