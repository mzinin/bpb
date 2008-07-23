#include <iostream>
#include <list>
#include "triple64.h"

using namespace std;

class JanetTree64
{
public:
  	struct Node
	{
    		int      mDeg;
    		Triple64*  mTriple;
    		Node*    mNextDeg;
    		Node*    mNextVar;

    		Node(int deg): mDeg(deg), mTriple(NULL), mNextDeg(NULL), mNextVar(NULL) {}
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
    		Triple64* trpl() const { return i->mTriple; }
    		unsigned degree() const { return i->mDeg; }
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
    		Triple64*& trpl() const { return (*i)->mTriple; }
    		unsigned degree() const { return (*i)->mDeg; }
    		void build(int d, int var, Triple64 *trpl);
    		void del();
    		void exclude();
    		void clear();
  	};

  	Node* mRoot;

public:
  	JanetTree64(): mRoot(NULL) {};
  	~JanetTree64();

  	Triple64* find(const Monom64& m) const;
  	void insert(Triple64 *trpl);
  	void del(Triple64 *trpl);
  	void clear();
  	bitset<64> nmulti(Triple64 *trpl);
};
