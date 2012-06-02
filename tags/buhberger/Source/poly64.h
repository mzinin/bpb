#include <iostream>
#include "monom64.h"

class Poly64 {
protected:
  typedef Monom64* It;
  typedef const Monom64* ConstIt;
  Monom64*  mHead;
  unsigned len;

  void additive(std::istream& in);
  void multiplicative(std::istream& in);
  void unary(std::istream& in);
  void power(std::istream& in);
  void bracket(std::istream& in);

public:
  //Poly64(): mHead(NULL), len(0) {}
  Poly64() { memset(this, 0, sizeof(Poly64)); }
  Poly64(const Poly64& a);
  Poly64(const Poly64& a, int var);
  Poly64(const Poly64& a, const Monom64& m);

  class Iterator;
  class ConstIterator {
    friend class Poly64;
    friend class Iterator;

  protected:
    Poly64::ConstIt mConstIt;

  public:
    ConstIterator(): mConstIt(NULL) {};
    ConstIterator(const Poly64::ConstIt constIt):mConstIt(constIt) {}
    ~ConstIterator() {}
    void operator=(const ConstIterator& a) { mConstIt = a.mConstIt; }
    operator bool() const { return mConstIt; }
    bool isNext() const { return (mConstIt->Next != NULL); }
    const Monom64& monom() const { return *mConstIt; }
    const Monom64& operator*() const { return *mConstIt; }
    const Monom64* operator->() const { return mConstIt; }
    void operator++() { mConstIt = mConstIt->Next; }
    void operator++(int i) { mConstIt = mConstIt->Next; }
    bool operator==(const ConstIterator& a) const { return mConstIt == a.mConstIt;; }
    bool operator!=(const ConstIterator& a) const { return mConstIt != a.mConstIt; }
  };

  class Iterator {
    friend class Poly64;
    friend class ConstIterator;

  protected:
    Poly64::It *mIt;

  public:
    Iterator(): mIt(NULL) {};
    Iterator(Poly64::It &it): mIt(&it) {}
    ~Iterator() {}
    void operator=(const Iterator& a) { mIt = a.mIt; }
    operator bool() const { return *mIt; }
    bool isNext() const { return ((*mIt)->Next != NULL); }
    const Monom64& monom() const { return **mIt; }
    Monom64& operator*() const { /*IASSERT(mIt); IASSERT(*mIt);*/ return **mIt; }
    Monom64* operator->() const { /*IASSERT(mIt); IASSERT(*mIt);*/ return *mIt; }
    void operator++() { mIt = &(*mIt)->Next; }
    void operator++(int i) { mIt = &(*mIt)->Next; }
    bool operator==(const Iterator& a) const { return *mIt == *a.mIt; }
    bool operator!=(const Iterator& a) const { return *mIt != *a.mIt; }
    void insert(const Monom64 &m) {	
      Monom64 *tmp = new Monom64(m);
      tmp->Next = *mIt;
      *mIt = tmp;
    }
    void insert_no_copy(Iterator another) {	
      Monom64 *tmp = *another.mIt;
      *another.mIt = (*another.mIt)->Next;
      tmp->Next = *mIt;
      *mIt = tmp;
    }
    void insert(ConstIterator j) {
      Monom64 *tmp = const_cast<Monom64*>(j.mConstIt);
      tmp->Next = *mIt;
      *mIt = tmp;
      tmp = NULL;
    }
    ConstIterator get() {
      ConstIterator j(*mIt);
      *mIt = (*mIt)->Next;
      Monom64 *tmp = const_cast<Monom64*>(j.mConstIt);
      tmp->Next = NULL;
      tmp = NULL;
      return j;
    }
    void del() {
      Monom64 *tmp = *mIt;
      *mIt = (*mIt)->Next;
      delete tmp;
    }
    void move_to(Iterator another) {
      *another.mIt = *mIt;
      *mIt = (*mIt)->Next;
      (*another.mIt)->Next = NULL;
    }
    void clear() {
      while (*mIt)
        del();
    }
  };
  

  ~Poly64() { begin().clear(); }

  void setOne();
  void setZero();
  void set(const Poly64& a);
  void operator=(const Poly64& a) { set(a); }

  void swap(Poly64& a);
  bool isZero() const;
  int length() const;

  int degree() const;
  int degree_of_monom(int i) const;
  int deg(int var);

  const Monom64& lm() const;
  const Monom64& monom(int i) const;
  void rid_of_lm();

  void add(const Monom64 &m);
  void add(Poly64& a);
  void add_no_copy(Poly64& a);
  void sub(Poly64& a) { add(a); }

  void mult(int var);
  void mult(int var, unsigned deg);
  void mult(const Monom64& m);
  void mult(const Poly64 &a);

  void pow(unsigned deg);
  void reduction(const Poly64& a);
  void head_reduction(const Poly64& a);

  ConstIterator begin() const;
  Iterator begin();

  friend std::ostream& operator<<(std::ostream& out, const Poly64& a);
  friend std::istream& operator>>(std::istream& in, Poly64& a);
  friend bool operator==(const Poly64 &a, const Poly64 &b);
  friend bool operator!=(const Poly64 &a, const Poly64 &b) {return !(a==b);}
  
  void assertValid(const char* fileName, int fileLine) const;
};

inline const Monom64& Poly64::lm() const {
  return *mHead;
}

inline const Monom64& Poly64::monom(int i) const {
  Monom64 *r(mHead);
  for (int j=0; j<i; j++) r = r->Next;
  return *r;
}

inline int Poly64::length() const {
  return len;
}

inline bool Poly64::isZero() const {
  return !mHead;
}


