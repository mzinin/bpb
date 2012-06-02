#include <iostream>
#include <fstream>
#include "ivariables.h"
#include "init64.h"
#include "version.h"

using namespace std;

void Usage(const char* applicationName)
{
    std::cout << "Usage:" << std::endl;
    std::cout <<"\t" << applicationName << " <file_name.gnv> - execute given task;" << std::endl;
    std::cout <<"\t" << applicationName << " -v, --version - print version;" << std::endl;
    std::cout <<"\t" << applicationName << " -h, --help - print this message." << std::endl;
}

void PrintVersion()
{
    std::cout << "version " << GetVersion().GetMajor() << "." << GetVersion().GetMinor() << "." << GetVersion().GetRevision() << std::endl;
}

int main(int argc, char *argv[])
{
    ifstream fin;
    //parse command line arguments
    switch (argc)
    {
        case 1:
            Usage(argv[0]);
            return EXIT_FAILURE;
            break;
        case 2:
            for (register int i = 1; i < argc; ++i)
            {
                if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
                {
                    PrintVersion();
                    return EXIT_SUCCESS;
                }
                else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
                {
                    Usage(argv[0]);
                    return EXIT_SUCCESS;
                }
                else
                {
                    fin.open(argv[i]);
                    if (!fin)
                    {
                        cout << "No such file:" << argv[i] << endl;
                        return EXIT_FAILURE;
                    }
                }
            }
            break;
        default:
            std::cout << "Too many arguments." << std::endl;
            Usage(argv[0]);
            return EXIT_FAILURE;
            break;
    }
  
  IVariables vars;
  //-----подсчет переменных
  int i=0;
  char s[161840],c='0';
  while ( c!=';' ){
  	fin>>c;
	if (c==',' || c==';') {
		vars.add(s);
		s[0]='\0';
		i=0;
	}
	else {
		s[i]=c;
		i++;
		s[i]='\0';
	}
  }
  //-----конец аодсчета переменных
  fin.close();

  int bytes = (vars.dim()-1)/64;

  switch (bytes){
    case 0:
      init64(argv[1]);
      break;
  }

  return EXIT_SUCCESS;
}
