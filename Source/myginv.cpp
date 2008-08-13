#include <iostream>
#include <fstream>
#include "variables.h"
#include "init64.h"
//#include "init128.h"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream fin;
  if (argc==1)
  {
    cout<<"Укажите файл .gnv"<<endl;
    return 1;
  }
  else
  {
    fin.open(argv[1]);
    if (!fin)
    {
      cout<<"Нет такого файла"<<endl;
      return 1;
    }
  }

  Variables vars;
  //-----подсчет переменных
  int i=0;
  char s[161840],c='0';
  while ( c!=';' )
  {
  	fin >> c;
	if (c==',' || c==';')
        {
		vars.add(s);
		s[0]='\0';
		i=0;
	}
	else
        {
		s[i]=c;
		i++;
		s[i]='\0';
	}
  }
  //-----конец подсчета
  fin.close();

  int bytes = (vars.dim()-1)/64;

  switch (bytes)
  {
    case 0:
      init64(argv[1]);
      break;
    case 1:
      //init128(argv[1]);
      break;
  }

  return EXIT_SUCCESS;
}
