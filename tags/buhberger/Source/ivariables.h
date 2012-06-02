#ifndef IVARIABLES_H
#define IVARIABLES_H

#include <cstring>
#include <iostream>
#include <vector>
#include "iutil.h"
using namespace std;
/*!
\english
  \file "util/ivariables.h"
  \brief Contains classes for working with variables.

  Contains class IVariables.
\endenglish
\russian
  \file "util/ivariables.h"
  \brief Содержит классы для работы с переменными.

  Содержит класс IVariables.
\endrussian
*/

/*!
\english
  \brief Defines variable manipulation
  \ingroup util

  This is a list of variables. It defines a set of
  functions for reading and printing variables.
\endenglish
\russian
  \brief Определяет работу с переменными.
  \ingroup util

  Представляют собой список переменных. Определяет
  набор функций по чтению и выводу переменных на печать.
\endrussian
*/
class IVariables {
public:
/*!
\english
  \brief Defines a list of variables.

  Defines an ordered list of variables with a leading veriable
  in the head of the list.
\endenglish
\russian
  \brief Определяет список переменных.

  Определяет упорядоченный список переменных со
  старшей переменной в голове списка.
\endrussian
*/
  typedef vector<const char*> List;
/*!
\english
  \brief Defines the iteragor for variables access.
\endenglish
\russian
  \brief Определяет итератор для доступа к переменным.
\endrussian
*/
  typedef vector<const char*>::const_iterator ConstIterator;

private:
/*!
\english
  \brief Variables list.
\endenglish
\russian
  \brief Список переменных.
\endrussian
*/
  List mList;

public:

/*!
\english
  \brief Default contructor.

  Creates an empty list of variables.
\endenglish
\russian
  \brief Конструктор по умолчанию.

  Создаёт пустой список переменных.
\endrussian
*/
  IVariables(): mList() {}
/*!
\english
  \brief Destructor.

  In particular, it releases the memory allocated for
  the string representation of variables.
\endenglish
\russian
  \brief Деструктор.

  В частности, освобождает память, выделенную
  на строковое представление переменных.
\endrussian
*/
  ~IVariables();

/*!
\english
  \brief Adds a variable in the end of list.
  \pre Variable with a name \a var is not contained in the list of variables.

  Causes an error if variable \a var do not satisfy variable naming rules
  or a variable with the same name already exists in the list.
\endenglish
\russian
  \brief Добавляет переменную в конец списка.
  \pre Переменная с именем \a var в списке переменных не содержится.

  Вызывает ошибку если переменная \a var не соответствует
  правилам задания имени переменной или переменная с этим именем уже есть в списке.
\endrussian
*/
  void add(const char *var);

/*!
\english
  \brief Returns number of variables.
  \return Number of variables in the list.
\endenglish
\russian
  \brief Возвращает число переменных.
  \return Количество переменных в списке.
\endrussian
*/
  int dim() const { return mList.size(); }
/*!
\english
  \brief Returns iterator pointing to the first element in the list.
\endenglish
\russian
  \brief Возвращает итератор указывающий на первый элемент списка.
\endrussian
*/
  ConstIterator begin() const { return mList.begin(); }
  ConstIterator end() const { return mList.end(); }
/*!
\english
  \brief Returns variable.
  \pre IASSERT(0 <=var && var < dim())
\endenglish
\russian
  \brief Возвращает переменную.
  \pre IASSERT(0 <= var && var < dim())
\endrussian
*/
  const char* variable(int var) const {
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
\russian
  \brief Находит переменную.
  \return Порядковый номер найденной переменной начиная с 0,
          иначе -1.
\endrussian
*/
  int find(const char *var) const;
/*!
\english
  \brief Reads variable from the input stream.
  \return Index of the found variable (starting from 0), otherwise -1.

  If variable is not found the input stream is set to the beginning of read.
\endenglish
\russian
  \brief Читает переменную из входного потока.
  \return Порядковый номер найденной переменной начиная с 0,
          иначе -1.

  Если переменная не найдена входной поток устанавливается
  на начало чтения.
\endrussian
*/
  int read(std::istream& in) const;
};

#endif // IVARIABLES_H
