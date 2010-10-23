#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "timer.h"
#include "involutive.h"
#include "version.h"

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
    std::ifstream fileInputStream;
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
                    fileInputStream.open(argv[i]);
                    if (!fileInputStream)
                    {
                        std::cout << "No such file:" << argv[i] << std::endl;
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

    //read variables
    char c = '0';
    std::string tmpString;
    while (c != ';' && !fileInputStream.eof())
    {
        fileInputStream >> c;
        if (c == ',' || c == ';')
        {
            Monom::AddVariable(tmpString.c_str());
            tmpString.clear();
        }
        else
        {
            tmpString += c;
        }
    }
    //variales are read

    Polynom poly;
    std::list<Polynom*> polyList, answerList;
    std::list<Polynom*>::iterator iterPolyList(polyList.begin()), iterAnswerList(answerList.begin());

    std::stringstream* tmpStream = new std::stringstream();
    c = '0';
    //read initial polynomial set
    while (c != ';' && !fileInputStream.eof())
    {
        fileInputStream >> c;
        if (c == ',' || c == ';')
        {
            *tmpStream << tmpString << std::endl;
            tmpString.clear();
        }
        else
        {
            tmpString += c;
        }
    }


    while (!tmpStream->eof())
    {
        *tmpStream >> poly;
        iterPolyList = polyList.insert(iterPolyList, new Polynom(poly));
    }

    delete tmpStream;
    //initial polynomial set is read

    tmpStream = new std::stringstream();
    c = '0';
    //read answer set
    while (c != ';' && !fileInputStream.eof())
    {
        fileInputStream >> c;
        if (c == ',' || c == ';')
        {
            *tmpStream << tmpString << std::endl;
            tmpString.clear();
        }
        else
        {
            tmpString += c;
        }
    }

    while (!tmpStream->eof())
    {
        *tmpStream >> poly;
        iterAnswerList = answerList.insert(iterAnswerList, new Polynom(poly));
    }

    delete tmpStream;
    //answer set is read

    fileInputStream.close();


    Timer timer;
    timer.Start();
    GBasis basisGroebner(polyList);
    timer.Stop();

    //std::cout << basisGroebner << std::endl;
    std::cout << "Size: " << basisGroebner.Length() << std::endl;
    std::cout << timer << std::endl;


    bool isCorrect = true, Found;
    //checking
    if (basisGroebner.Length() != answerList.size())
    {
        isCorrect = false;
    }
    else
    {
        iterAnswerList = answerList.begin();
        while (iterAnswerList != answerList.end())
        {
            Found = false;
            for (register unsigned i = 0; i < basisGroebner.Length(); i++)
            {
                if (*basisGroebner[i] == **iterAnswerList)
                {
                    Found = true;
                    break;
                }
            }
            if (!Found)
            {
                isCorrect = false;
                std::cout << "The mistake is here " << **iterAnswerList << std::endl;
                break;
            }
            iterAnswerList++;
        }
    }
    std::cout << std::endl;
    //end checking

    if (isCorrect)
    {
        std::cout << "The answer is CORRECT" << std::endl;
    }
    else
    {
        std::cout << "The answer is WRONG" << std::endl;
    }

    return EXIT_SUCCESS;
}
