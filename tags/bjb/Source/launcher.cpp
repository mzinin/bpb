#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef __linux__
#include <memory>
#endif // __linux__

#include "fast_allocator.h"
#include "launcher.h"
#include "monom.h"
#include "resource_counter.h"
#include "version.h"

namespace
{
    const char OPTION_SHORT_PREFIX[] = "-";
    const char OPTION_LONG_PREFIX[] = "--";
    const char OPTION_VALUE_DELIMITER = '=';

    const char VERSION_SHORT_KEY   = 'v';
    const char VERSION_LONG_KEY[]  = "version";
    const char VERSION_USAGE_COMMENT[] = "Print version";

    const char HELP_SHORT_KEY  = 'h';
    const char HELP_LONG_KEY[] = "help";
    const char HELP_USAGE_COMMENT[] = "Print this message";

    const char STATISTICS_SHORT_KEY  = 's';
    const char STATISTICS_LONG_KEY[] = "collect-statistics";
    const char STATISTICS_USAGE_COMMENT[] = "Collect and print out statistics";

    const char PRINT_ANSWER_SHORT_KEY  = 'a';
    const char PRINT_ANSWER_LONG_KEY[] = "print-answer";
    const char PRINT_ANSWER_USAGE_COMMENT[] = "Print out constructed Groebner Basis";
}

Launcher::CommandLineOption::OptionValue::OptionValue(const std::string& value, 
                                                      const std::string& usageComment, 
                                                      void (SettingsManager::* const action)())
    : Value(value)
    , UsageComment(usageComment)
    , Action(action)
{
}

Launcher::CommandLineOption::OptionValue::~OptionValue()
{
}

Launcher::CommandLineOption::CommandLineOption(const char shortKey, 
                                               const std::string& longKey, 
                                               const std::string& usageComment, 
                                               void (SettingsManager::* const action)())
    : ShortKey(shortKey)
    , LongKey(longKey)
    , UsageComment(usageComment)
    , Action(action)
    , Values()
    , ChosenValue(Values.end())
{
}

Launcher::CommandLineOption::CommandLineOption(const std::string& longKey, 
                                               const std::string& usageComment, 
                                               const std::list<OptionValue>& values)
    : ShortKey(0)
    , LongKey(longKey)
    , UsageComment(usageComment)
    , Action(0)
    , Values(values)
    , ChosenValue(Values.end())
{
}

Launcher::CommandLineOption::~CommandLineOption()
{
}

bool Launcher::CommandLineOption::DetectKey(const std::string& option) const
{
    if (Values.empty())
    {
        return LongKey == option || option.size() == 1 && option[0] == ShortKey;
    }

    std::size_t position = option.find(OPTION_VALUE_DELIMITER);
    std::string givenOption = option.substr(0, position);
    if (LongKey != givenOption)
    {
        return false;
    }

    if (option.size() < position + 2)
    {
        std::cerr << "Option '" << OPTION_LONG_PREFIX << LongKey << "' requires value, but didn't get one" << std::endl;
        return false;
    }

    std::string givenValue = option.substr(position + 1);
    ChosenValue = Values.begin();
    for (; ChosenValue != Values.end(); ++ChosenValue)
    {
        if (ChosenValue->Value == givenValue)
        {
            break;
        }
    }

    if (ChosenValue == Values.end())
    {
        std::cerr << "Option '" << OPTION_LONG_PREFIX << LongKey << "' got an unknown value '" << givenValue << "'." << std::endl;
        return false;
    }

    return true;
}

void Launcher::CommandLineOption::Activate() const
{
    if (Action && Values.empty())
    {
        (GetSettingsManager().*Action)();
    }
    if (!Values.empty() && ChosenValue != Values.end())
    {
        (GetSettingsManager().*(ChosenValue->Action))();
    }
}

void Launcher::CommandLineOption::PrintHelp() const
{
    if (Values.empty())
    {
        std::cout << OPTION_SHORT_PREFIX << ShortKey << ", " << OPTION_LONG_PREFIX << LongKey << std::endl;
        std::cout << "\t" << UsageComment << ";" << std::endl;
    }
    else
    {
        std::cout << OPTION_LONG_PREFIX << LongKey << OPTION_VALUE_DELIMITER << "<value>" << std::endl;
        std::cout << "\t" << UsageComment << "," << std::endl;
        std::cout << "\tAdmissible values are:" << std::endl;

        unsigned valueFieldWidth = 0;
        for (std::list<OptionValue>::const_iterator i = Values.begin(); i != Values.end(); ++i)
        {
            if (i->UsageComment.empty())
            {
                continue;
            }
            if (i->Value.size() > valueFieldWidth)
            {
                valueFieldWidth = i->Value.size();
            }
        }
        for (std::list<OptionValue>::const_iterator i = Values.begin(); i != Values.end(); ++i)
        {
            if (i->UsageComment.empty())
            {
                continue;
            }
            std::cout << "\t\t" << std::setw(valueFieldWidth) << std::left << i->Value << " - ";
            std::cout  << i->UsageComment << (i == Values.end()-- ? "," : ";") << std::endl;
        }
    }
}

Launcher::Launcher()
    : ApplicationName()
    , InputFileName()
{
    FillOptions();
}

Launcher::~Launcher()
{
}

bool Launcher::Init(int argc, char *argv[])
{
    ApplicationName = argv[0];
    bool result = false;

    try
    {
        result = AnalizeArguments(argc, argv);
    }
    catch (const std::exception& error)
    {
        std::cerr << "Launcher::Init caught exception: " << error.what() << std::endl;
    }

    return result;
}

bool Launcher::Run()
{
    try
    {
        if (GetSettingsManager().GetPrintHelp())
        {
            PrintUsage();
            return true;
        }

        if (GetSettingsManager().GetPrintVersion())
        {
            PrintVersion();
            return true;
        }

        if (InputFileName.empty())
        {
            std::cerr << "Task file name is not defined." << std::endl << std::endl;
            PrintUsage();
            return false;
        }

        std::list<Polynom*> initialSet;
        std::list<Polynom*> initialAnswer;

        if (!GetTaskFromFile(initialSet, initialAnswer))
        {
            return false;
        }
        
        GroebnerBasis gBasis;
        GetResourceCounter().GroebnerBasisTimer.Start();
        gBasis.Construct(initialSet);
        GetResourceCounter().GroebnerBasisTimer.Stop();

        PrintResult(gBasis, initialAnswer);
    }
    catch (const std::exception& error)
    {
        std::cerr << "Launcher::Run caught exception: " << error.what() << std::endl;
    }

    return true;
}

void Launcher::FillOptions()
{
    if (!CommandLineOptions.empty())
    {
        return;
    }

    // add help option
    CommandLineOptions.push_back(CommandLineOption(HELP_SHORT_KEY, 
                                                   HELP_LONG_KEY, 
                                                   HELP_USAGE_COMMENT, 
                                                   &SettingsManager::SetPrintHelpEnabled));

    // add version option
    CommandLineOptions.push_back(CommandLineOption(VERSION_SHORT_KEY, 
                                                   VERSION_LONG_KEY, 
                                                   VERSION_USAGE_COMMENT, 
                                                   &SettingsManager::SetPrintVersionEnabled));

    // add statistics option
    CommandLineOptions.push_back(CommandLineOption(STATISTICS_SHORT_KEY, 
                                                   STATISTICS_LONG_KEY, 
                                                   STATISTICS_USAGE_COMMENT, 
                                                   &SettingsManager::SetCollectStatisticsEnabled));

    // add print answer option
    CommandLineOptions.push_back(CommandLineOption(PRINT_ANSWER_SHORT_KEY, 
                                                   PRINT_ANSWER_LONG_KEY, 
                                                   PRINT_ANSWER_USAGE_COMMENT, 
                                                   &SettingsManager::SetPrintAnswerEnabled));
}

void Launcher::PrintUsage() const
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << ApplicationName << " [options] <file_name.gnv> - execute given task;" << std::endl << std::endl;

    std::cout << "Options:" << std::endl;
    for (std::list<CommandLineOption>::const_iterator i = CommandLineOptions.begin(); i != CommandLineOptions.end(); ++i)
    {
        i->PrintHelp();
        std::cout << std::endl;
    }
}

void Launcher::PrintVersion() const
{
    std::cout << "\t" << ApplicationName << std::endl;
    std::cout << "\tVersion " << GetVersion().GetMajor() << "." << GetVersion().GetMinor() << "." << GetVersion().GetRevision() << std::endl;
}

bool Launcher::AnalizeArguments(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "Arguments are missing." << std::endl << std::endl;
        PrintUsage();
        return false;
    }

    std::list<std::string> arguments;
    for (register int i = 1; i < argc; ++i)
    {
        std::string currentArgument = std::string(argv[i]);

        if (currentArgument.size() > 2 && currentArgument.find(OPTION_LONG_PREFIX) == 0)
        {
            arguments.push_back(currentArgument.substr(strlen(OPTION_LONG_PREFIX)));
        }
        else if (currentArgument.size() > 1 && currentArgument.find(OPTION_SHORT_PREFIX) == 0)
        {
            for (register int p = strlen(OPTION_SHORT_PREFIX); p < currentArgument.size(); ++p)
            {
                arguments.push_back(std::string(1, currentArgument[p]));
            }
        }
        else if (i == argc - 1)
        {
            InputFileName = argv[i];
        }
        else
        {
            std::cerr << "'" << argv[i] << "' - task file name should be the last argument." << std::endl << std::endl;
            PrintUsage();
            return false;
        }
    }

    std::list<std::string>::const_iterator argumentsIterator = arguments.begin();
    for (; argumentsIterator != arguments.end(); ++argumentsIterator)
    {
        std::list<CommandLineOption>::const_iterator optionsIterator = CommandLineOptions.begin();
        for (; optionsIterator != CommandLineOptions.end(); ++optionsIterator)
        {
            if (optionsIterator->DetectKey(*argumentsIterator))
            {
                break;
            }
        }
        
        if (optionsIterator != CommandLineOptions.end())
        {
            optionsIterator->Activate();
        }
        else
        {
            std::cerr << "Unknown option: '" << *argumentsIterator << "'." << std::endl << std::endl;
            PrintUsage();
            return false;
        }
    }

    return true;
}

bool Launcher::GetTaskFromFile(std::list<Polynom*>& initialSet, std::list<Polynom*>& initialAnswer) const
{
    std::ifstream inputFileStream(InputFileName.c_str());
    if (!inputFileStream)
    {
        std::cerr << "No such file: '" << InputFileName << "'." << std::endl;
        return false;
    }

    ReadVariables(inputFileStream);
    ReadPolynomList(inputFileStream, initialSet);
    ReadPolynomList(inputFileStream, initialAnswer);

    inputFileStream.close();
    return true;
}

void Launcher::ReadVariables(std::ifstream& inputFileStream) const
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

void Launcher::ReadPolynomList(std::ifstream& inputFileStream, std::list<Polynom*>& list) const
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

void Launcher::ClearPolynomList(std::list<Polynom*>& list) const
{
    std::list<Polynom*>::iterator i(list.begin());
    for (; i != list.end(); ++i)
    {
        delete *i;
    }
    list.clear();
}

void Launcher::PrintResult(GroebnerBasis& gBasis, std::list<Polynom*>& initialAnswer) const
{
    if (!gBasis.Length())
    {
        return;
    }

    if (GetSettingsManager().GetPrintAnswer())
    {
        std::cout << gBasis << std::endl;
    }

    if (GetSettingsManager().GetCollectStatistics())
    {
        GetResourceCounter().PrintFullStatistics(std::cout);
    }
    else
    {
        GetResourceCounter().PrintBriefStatistics(std::cout);
    }

    if (CheckAnswer(gBasis, initialAnswer))
    {
        std::cout << "The answer is CORRECT" << std::endl << std::endl;
    }
    else
    {
        std::cout << "The answer is WRONG" << std::endl << std::endl;
    }
}

bool Launcher::CheckAnswer(GroebnerBasis& gBasis, std::list<Polynom*>& initialAnswer) const
{
    if (gBasis.Length() != initialAnswer.size())
    {
        return false;
    }
    else
    {
        std::list<Polynom*>::const_iterator iterAnswerList = initialAnswer.begin();
        for (; iterAnswerList != initialAnswer.end(); ++iterAnswerList) 
        {
            bool foundMatch = false;
            for (register unsigned i = 0; i < gBasis.Length(); ++i)
            {
                if (gBasis[i] == **iterAnswerList)
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

std::list<Launcher::CommandLineOption> Launcher::CommandLineOptions = std::list<Launcher::CommandLineOption>();
