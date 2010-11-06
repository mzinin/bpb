#include <fstream>
#include <iomanip>
#include <sstream>

#ifdef __linux__
#include <memory>
#endif // __linux__

#include "fast_allocator.h"
#include "launcher.h"
#include "resource_counter.h"
#include "settings_manager.h"
#include "version.h"

namespace
{
    const char VERSION_SHORT_KEY[] = "-v";
    const char VERSION_LONG_KEY[]  = "--version";
    const char HELP_SHORT_KEY[]    = "-h";
    const char HELP_LONG_KEY[]     = "--help";
    const char STATISTICS_SHORT_KEY[] = "-s";
    const char STATISTICS_LONG_KEY[]  = "--collect-statistics";
    const char NOVA_INVOLUTION_SHORT_KEY[] = "-n";
    const char NOVA_INVOLUTION_LONG_KEY[]  = "--nova-involution";
    const char PRINT_ANSWER_SHORT_KEY[] = "-a";
    const char PRINT_ANSWER_LONG_KEY[]  = "--print-answer";
}

void Launcher::PrintUsage() const
{
    std::cout << "Usage:" << std::endl;
    std::cout << "     " << ApplicationName << " [options] <file_name.gnv> - execute given task;" << std::endl;
    std::cout << " Or: " << ApplicationName << " [key];" << std::endl << std::endl;

    std::cout << "Options:" << std::endl;
    std::cout << "    " << STATISTICS_SHORT_KEY << ", " << std::setw(25) << std::left << STATISTICS_LONG_KEY << " - collect and print out statistics;" << std::endl;
    std::cout << "    " << NOVA_INVOLUTION_SHORT_KEY << ", " << std::setw(25) << std::left << NOVA_INVOLUTION_LONG_KEY << " - use Nova involutive division instead of Pommaret one;" << std::endl;
    std::cout << "    " << PRINT_ANSWER_SHORT_KEY << ", " << std::setw(25) << std::left << PRINT_ANSWER_LONG_KEY << " - print out constructed Groebner Basis;" << std::endl << std::endl;

    std::cout << "Keys:" << std::endl;
    std::cout << "    " << VERSION_SHORT_KEY << ", " << std::setw(12) << std::left << VERSION_LONG_KEY << " - print version;" << std::endl;
    std::cout << "    " << HELP_SHORT_KEY << ", " << std::setw(12) << std::left << HELP_LONG_KEY << " - print this message." << std::endl;
}

void Launcher::PrintVersion() const
{
    std::cout << "version " << GetVersion().GetMajor() << "." << GetVersion().GetMinor() << "." << GetVersion().GetRevision() << std::endl;
}

bool Launcher::AnalizeArguments(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "Arguments are missing." << std::endl << std::endl;
        PrintUsage();
        return false;
    }

    for (register int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], VERSION_SHORT_KEY) || !strcmp(argv[i], VERSION_LONG_KEY))
        {
            PrintVersion();
            GetSettingsManager().ConstructBasis = false;
            return true;
        }
        else if (!strcmp(argv[i], HELP_SHORT_KEY) || !strcmp(argv[i], HELP_LONG_KEY))
        {
            PrintUsage();
            GetSettingsManager().ConstructBasis = false;
            return true;
        }
        else if (!strcmp(argv[i], STATISTICS_SHORT_KEY) || !strcmp(argv[i], STATISTICS_LONG_KEY))
        {
            GetSettingsManager().CollectStatistics = true;
            continue;
        }
        else if (!strcmp(argv[i], NOVA_INVOLUTION_SHORT_KEY) || !strcmp(argv[i], NOVA_INVOLUTION_LONG_KEY))
        {
            GetSettingsManager().UseNovaInvolution = true;
            continue;
        }
        else if (!strcmp(argv[i], PRINT_ANSWER_SHORT_KEY) || !strcmp(argv[i], PRINT_ANSWER_LONG_KEY))
        {
            GetSettingsManager().PrintAnswer = true;
            continue;
        }
        else if (i == argc - 1)
        {
            InputFileName = argv[i];
        }
        else
        {
            std::cerr << "Unknown option or key: '" << argv[i] << "'." << std::endl << std::endl;
            PrintUsage();
            return false;
        }
    }

    return true;
}

Launcher::Launcher()
    : ApplicationName()
    , InputFileName()
    , InitialSet()
    , InitialAnswer()
    , GBasis()
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
        std::cerr << "No such file: '" << InputFileName << "'." << std::endl;
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

    GetResourceCounter().GroebnerBasisTimer.Start();
    GBasis.Construct(InitialSet);
    GetResourceCounter().GroebnerBasisTimer.Stop();

    return true;
}

void Launcher::PrintResult() const
{
    if (GetSettingsManager().PrintAnswer)
    {
        std::cout << GBasis << std::endl;
    }

    if (GetSettingsManager().CollectStatistics)
    {
        GetResourceCounter().PrintFullStatistics(std::cout);
    }
    else
    {
        GetResourceCounter().PrintBriefStatistics(std::cout);
    }

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
    if (GBasis.Length() != InitialAnswer.size())
    {
        return false;
    }
    else
    {
        std::list<Polynom*>::const_iterator iterAnswerList = InitialAnswer.begin();
        for (; iterAnswerList != InitialAnswer.end(); ++iterAnswerList)
        {
            bool foundMatch = false;
            for (register unsigned i = 0; i < GBasis.Length(); ++i)
            {
                if (GBasis[i] == **iterAnswerList)
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
