#include <iostream>
#include "imymonom64.h"

class IMyPoly64;
class IMyPolyInterface64 {
  friend class IMyPoly64;

protected:
  IMyMonomInterface64 *mMonomInterface;

public:
  IMyPolyInterface64();
  static IMyPolyInterface64* create(IMyMonomInterface64* monomInterface);
  ~IMyPolyInterface64() {}

  IMyMonomInterface64* monomInterface() const { return mMonomInterface; }
  IMyPoly64* create();
  IMyPoly64* copy(const IMyPoly64& a);
  IMyPoly64* copy(const IMyPoly64& a, int var);
};

class IMyPoly64 {
  friend class IMyPolyInterface64;
  
protected:
  typedef IMyMonom64* It;
  typedef const IMyMonom64* ConstIt;
  IMyMonom64*  mHead;
  IMyPolyInterface64* mRealization;
  int len;

  void additive(std::istream& in);
  void multiplicative(std::istream& in);
  void unary(std::istream& in);
  void power(std::istream& in);
  void bracket(std::istream& in);

public:
  IMyPoly64(IMyPolyInterface64* r);
  IMyPoly64(const IMyPoly64& a);
  IMyPoly64(const IMyPoly64& a, int var);
  IMyPoly64(const IMyPoly64& a, const IMyMonom64& m);

  IMyMonomInterface64* monomInterface() const { return mRealization->mMonomInterface; }

  class Iterator;
  class ConstIterator {
    friend class IMyPoly64;
    friend class Iterator;

  protected:
    IMyPoly64::ConstIt mConstIt;

  public:
    ConstIterator(): mConstIt(NULL) {};
    ConstIterator(const IMyPoly64::ConstIt constIt):mConstIt(constIt) {}
    ~ConstIterator() {}
    void operator=(const ConstIterator& a) { mConstIt = a.mConstIt; }
    operator bool() const { return mConstIt; }
    bool isNext() const { return (mConstIt->Next != NULL); }
    const IMyMonom64& monom() const { return *mConstIt; }
    const IMyMonom64& operator*() const { return *mConstIt; }
    const IMyMonom64* operator->() const { return mConstIt; }
    void operator++() { mConstIt = mConstIt->Next; }
    void operator++(int i) { mConstIt = mConstIt->Next; }
    bool operator==(const ConstIterator& a) const { return mConstIt == a.mConstIt;; }
    bool operator!=(const ConstIterator& a) const { return mConstIt != a.mConstIt; }
  };

  class Iterator {
    friend class IMyPoly64;
    friend class ConstIterator;

  protected:
    IMyPoly64::It *mIt;

  public:
    Iterator(): mIt(NULL) {};
    Iterator(IMyPoly64::It &it): mIt(&it) {}
    ~Iterator() {}
    void operator=(const Iterator& a) { mIt = a.mIt; }
    operator bool() const { return *mIt; }
    bool isNext() const { return ((*mIt)->Next != NULL); }
    const IMyMonom64& monom() const { return **mIt; }
    IMyMonom64& operator*() const { /*IASSERT(mIt); IASSERT(*mIt);*/ return **mIt; }
    IMyMonom64* operator->() const { /*IASSERT(mIt); IASSERT(*mIt);*/ return *mIt; }
    void operator++() { mIt = &(*mIt)->Next; }
    void operator++(int i) { mIt = &(*mIt)->Next; }
    bool operator==(const Iterator& a) const { return *mIt == *a.mIt; }
    bool operator!=(const Iterator& a) const { return *mIt != *a.mIt; }
    void insert(IMyMonom64 &m) {	
      //IASSERT(mIt);
      m.Next = *mIt;
      *mIt = &m;
    }
    void insert(ConstIterator j) {
      //IASSERT(mIt);	
      IMyMonom64 *tmp = const_cast<IMyMonom64*>(j.mConstIt);
      tmp->Next = *mIt;
      *mIt = tmp;
      tmp = NULL;
    }
    ConstIterator get() {
      //IASSERT(mIt);
      ConstIterator j(*mIt);
      *mIt = (*mIt)->Next;
      IMyMonom64 *tmp = const_cast<IMyMonom64*>(j.mConstIt);
      tmp->Next = NULL;
      tmp = NULL;
      return j;
    }
    void del() {
      //IASSERT(mIt);
      IMyMonom64 *tmp = *mIt;
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
  

  ~IMyPoly64() { begin().clear(); }
  IMyPolyInterface64* polyInterface() const { return mRealization; }

  void setOne();
  void setZero();
  void set(const IMyPoly64& a);
  void operator=(const IMyPoly64& a) { set(a); }

  void swap(IMyPoly64& a);
  bool isZero() const;
  int length() const;

  int degree() const;
  int degree_of_monom(int i) const;
  int deg(int var);

  const IMyMonom64& lm() const;
  void rid_of_lm();

  void add(const IMyMonom64 &m);
  void add(IMyPoly64& a);
  void sub(IMyPoly64& a) { add(a); }

  void mult(int var);
  void mult(int var, unsigned deg);
  void mult(const IMyMonom64& m);
  void mult(const IMyPoly64 &a);

  void pow(unsigned deg);
  void reduction(const IMyPoly64& a);
  void reduction1(const IMyPoly64& a);

  ConstIterator begin() const;
  Iterator begin();

  friend std::ostream& operator<<(std::ostream& out, const IMyPoly64& a);
  friend std::istream& operator>>(std::istream& in, IMyPoly64& a);
  friend bool operator==(const IMyPoly64 &a, const IMyPoly64 &b);
  friend bool operator!=(const IMyPoly64 &a, const IMyPoly64 &b) {return !(a==b);}
  
  void RawCopy(IMyPoly64& a);
  void assertValid(const char* fileName, int fileLine) const;

  IMyPoly64* deriv1();
  IMyPoly64* deriv2();
};

inline const IMyMonom64& IMyPoly64::lm() const {
  //IASSERT(!isZero());
  return *mHead;
}

inline int IMyPoly64::length() const {
  return len;
}

inline bool IMyPoly64::isZero() const {
  return !mHead;
}
