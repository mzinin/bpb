#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <list>
#include <string>

#include "groebner_basis.h"
#include "polynom.h"
#include "settings_manager.h"

class Launcher
{
private:
    class CommandLineOption
    {
    public:
        struct OptionValue
        {
            const std::string Value;
            const std::string UsageComment;
            void (SettingsManager::* const Action)();

            OptionValue(const std::string& value, const std::string& usageComment, void (SettingsManager::* const action)());
            ~OptionValue();
        };
    private:
        const char ShortKey;
        const std::string LongKey;
        const std::string UsageComment;
        void (SettingsManager::* const Action)();
        const std::list<OptionValue> Values;
        mutable std::list<OptionValue>::const_iterator ChosenValue;

    public:
        CommandLineOption(const char shortKey, const std::string& longKey, const std::string& usageComment, void (SettingsManager::* const action)());
        CommandLineOption(const char shortKey, const std::string& longKey, const std::string& usageComment, const std::list<OptionValue>& values);
        ~CommandLineOption();

        bool DetectKey(const std::string& option) const;
        void Activate() const;

        void PrintHelp() const;
    };

    static std::list<CommandLineOption> CommandLineOptions;
    std::string ApplicationName;
    std::string InputFileName;
    std::list<Polynom*> InitialSet;
    std::list<Polynom*> InitialAnswer;
    GroebnerBasis GBasis;

public:
    Launcher();
    ~Launcher();

    bool Init(int argc, char *argv[]);
    bool Run();
    void PrintResult() const;

private:
    static void FillOptions();

    void PrintUsage() const;
    void PrintVersion() const;
    bool AnalizeArguments(int argc, char *argv[]);

    void ReadVariables(std::ifstream& inputFileStream);
    void ReadPolynomList(std::ifstream& inputFileStream, std::list<Polynom*>& list);
    bool GetTaskFromFile();

    bool CheckAnswer() const;
    void ClearPolynomList(std::list<Polynom*>& list);
};

#endif // LAUNCHER_H
