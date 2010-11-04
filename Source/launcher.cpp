#include <fstream>
#include <sstream>
#ifdef __linux__
#include <memory>
#endif // __linux__

#include "launcher.h"
#include "version.h"

namespace
{
    const char VERSION_SHORT_KEY[] = "-v";
    const char VERSION_LONG_KEY[]  = "--version";
    const char HELP_SHORT_KEY[]    = "-h";
    const char HELP_LONG_KEY[]     = "--help";
}

void Launcher::PrintUsage() const
{
    std::cout << "Usage:" << std::endl;
    std::cout <<"\t" << ApplicationName << " <file_name.gnv> - execute given task;" << std::endl;
    std::cout <<"\t" << ApplicationName << " -v, --version - print version;" << std::endl;
    std::cout <<"\t" << ApplicationName << " -h, --help - print this message." << std::endl;
}

void Launcher::PrintVersion() const
{
    std::cout << "version " << GetVersion().GetMajor() << "." << GetVersion().GetMinor() << "." << GetVersion().GetRevision() << std::endl;
}

bool Launcher::AnalizeArguments(int argc, char *argv[])
{
    switch (argc)
    {
        case 1:
            PrintUsage();
            return false;
        case 2:
            for (register int i = 1; i < argc; ++i)
            {
                if (!strcmp(argv[i], VERSION_SHORT_KEY) || !strcmp(argv[i], VERSION_LONG_KEY))
                {
                    PrintVersion();
                    return false;
                }
                else if (!strcmp(argv[i], HELP_SHORT_KEY) || !strcmp(argv[i], HELP_LONG_KEY))
                {
                    PrintUsage();
                    return false;
                }
                else
                {
                    InputFileName = argv[i];
                    return true;
                }
            }
            break;
        default:
            std::cerr << "Too many arguments." << std::endl;
            PrintUsage();
            return false;
    }
}

Launcher::Launcher()
    : ApplicationName()
    , InputFileName()
    , InitialSet()
    , InitialAnswer()
    , GroebnerBasis()
    , GBCommonTimer()
{
}

Launcher::~Launcher()
{
    ClearPolynomList(InitialSet);
    ClearPolynomList(InitialAnswer);
}

bool Launcher::Init(int argc, char *argv[])
{
    ApplicationName = argv[0];
    return AnalizeArguments(argc, argv) && !InputFileName.empty();
}

void Launcher::ReadVariables(std::ifstream& inputFileStream)
{
    char c = '0';
    std::string tmpString;
    while (c != ';' && !inputFileStream.eof())
    {
        inputFileStream >> c;
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
}

void Launcher::ReadPolynomList(std::ifstream& inputFileStream, std::list<Polynom*>& list)
{
    ClearPolynomList(list);

    std::auto_ptr<std::stringstream> tmpStream(new std::stringstream());
    char c = '0';
    std::string tmpString;
    while (c != ';' && !inputFileStream.eof())
    {
        inputFileStream >> c;
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

    Polynom tmpPolynom;
    while (!tmpStream->eof())
    {
        *tmpStream >> tmpPolynom;
        list.push_back(new Polynom(tmpPolynom));
    }
}

bool Launcher::GetTaskFromFile()
{
    std::ifstream inputFileStream(InputFileName.c_str());
    if (!inputFileStream)
    {
        std::cerr << "No such file:" << InputFileName << std::endl;
        return false;
    }

    ReadVariables(inputFileStream);
    ReadPolynomList(inputFileStream, InitialSet);
    ReadPolynomList(inputFileStream, InitialAnswer);

    inputFileStream.close();
    return true;
}

bool Launcher::Run()
{
    if (!GetTaskFromFile())
    {
        return false;
    }

    GBCommonTimer.Start();
    GroebnerBasis.Construct(InitialSet);
    GBCommonTimer.Stop();

    return true;
}

void Launcher::PrintResult() const
{
    //std::cout << GroebnerBasis << std::endl;
    std::cout << "Size: " << GroebnerBasis.Length() << std::endl;
#ifdef COLLECT_STATISTICS
    GroebnerBasis.PrintStatistics(std::cout);
#endif // COLLECT_STATISTICS

    std::cout << GBCommonTimer << std::endl;
    if (CheckAnswer())
    {
        std::cout << "The answer is CORRECT" << std::endl;
    }
    else
    {
        std::cout << "The answer is WRONG" << std::endl;
    }
}

bool Launcher::CheckAnswer() const
{
    if (GroebnerBasis.Length() != InitialAnswer.size())
    {
        return false;
    }
    else
    {
        std::list<Polynom*>::const_iterator iterAnswerList = InitialAnswer.begin();
        for (; iterAnswerList != InitialAnswer.end(); ++iterAnswerList)
        {
            bool foundMatch = false;
            for (register unsigned i = 0; i < GroebnerBasis.Length(); i++)
            {
                if (GroebnerBasis[i] == **iterAnswerList)
                {
                    foundMatch = true;
                    break;
                }
            }
            if (!foundMatch)
            {
                std::cout << "The mistake is here " << **iterAnswerList << std::endl;
                return false;
            }
        }
    }
    return true;
}

void Launcher::ClearPolynomList(std::list<Polynom*>& list)
{
    std::list<Polynom*>::iterator i(list.begin());
    for (; i != list.end(); ++i)
    {
        delete *i;
    }
    list.clear();
}
