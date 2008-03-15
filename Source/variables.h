#ifndef VARIABLES_H
#define VARIABLES_H

#include <cstring>
#include <iostream>
#include <vector>
#include "util.h"
using namespace std;
/*!
\english
  \file "util/ivariables.h"
  \brief Contains classes for working with variables.

  Contains class IVariables.
\endenglish
*/

/*!
\english
  \brief Defines variable manipulation
  \ingroup util

  This is a vector of variables. It defines a set of
  functions for reading and printing variables.
\endenglish
*/
class Variables {
public:
/*!
\english
  \brief Defines a vector of variables.

  Defines an ordered vector of variables with a leading veriable
  in the head of the vector.
\endenglish
*/
  typedef vector<const char*> List;
/*!
\english
  \brief Defines the iteragor for variables access.
\endenglish
*/
  typedef vector<const char*>::const_iterator ConstIterator;

private:
/*!
\english
  \brief Variables vector.
\endenglish
*/
  List mList;

public:

/*!
\english
  \brief Default contructor.

  Creates an empty vector of variables.
\endenglish
*/
  Variables(): mList() {}
/*!
\english
  \brief Destructor.

  In particular, it releases the memory allocated for
  the string representation of variables.
\endenglish
*/
  ~Variables();

/*!
\english
  \brief Adds a variable in the end of vector.
  \pre Variable with a name \a var is not contained in the vector of variables.

  Causes an error if variable \a var do not satisfy variable naming rules
  or a variable with the same name already exists in the vector.
\endenglish
*/
  void add(const char *var);

/*!
\english
  \brief Returns number of variables.
  \return Number of variables in the vector.
\endenglish
*/
  int dim() const { return mList.size(); }
/*!
\english
  \brief Returns iterator pointing to the first element in the vector.
\endenglish
*/
  ConstIterator begin() const { return mList.begin(); }
  ConstIterator end() const { return mList.end(); }
/*!
\english
  \brief Returns variable.
  \pre IASSERT(0 <=var && var < dim())
\endenglish
*/
  const char* variable(int var) const
  {
    //IASSERT(0 <= var && var < dim());
    ConstIterator it(mList.begin());
    it+=var;
    return *it;
  }
/*!
\english
  \brief Finds variable.
  \return Index of the found variable (starting from 0), otherwise -1.
\endenglish
*/
  int find(const char *var) const;
/*!
\english
  \brief Reads variable from the input stream.
  \return Index of the found variable (starting from 0), otherwise -1.

  If variable is not found the input stream is set to the beginning of read.
\endenglish
*/
  int read(std::istream& in) const;
};

#endif // IVARIABLES_H
