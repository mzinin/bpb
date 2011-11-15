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

    public:
        CommandLineOption(const char shortKey, const std::string& longKey, const std::string& usageComment, void (SettingsManager::* const action)());
        CommandLineOption(const std::string& longKey, const std::string& usageComment, const std::list<OptionValue>& values);
        ~CommandLineOption();

        bool DetectKey(const std::string& option) const;
        void Activate() const;
        
        void PrintHelp() const;
        
    private:
        const char ShortKey;
        const std::string LongKey;
        const std::string UsageComment;
        void (SettingsManager::* const Action)();
        const std::list<OptionValue> Values;
        mutable std::list<OptionValue>::const_iterator ChosenValue;
    };

    static std::list<CommandLineOption> CommandLineOptions;
    std::string ApplicationName;
    std::string InputFileName;

public:
    Launcher();
    ~Launcher();

    bool Init(int argc, char *argv[]);
    bool Run();

private:
    static void FillOptions();

    void PrintUsage() const;
    void PrintVersion() const;
    bool AnalizeArguments(int argc, char *argv[]);
    
    bool GetTaskFromFile(std::list<Polynom*>& initialSet, std::list<Polynom*>& initialAnswer) const;

    void ReadVariables(std::ifstream& inputFileStream) const;
    void ReadPolynomList(std::ifstream& inputFileStream, std::list<Polynom*>& list) const;
    void ClearPolynomList(std::list<Polynom*>& list) const;

    void PrintResult(GroebnerBasis& gBasis, std::list<Polynom*>& initialAnswer) const;
    bool CheckAnswer(GroebnerBasis& gBasis, std::list<Polynom*>& initialAnswer) const;
};

#endif // LAUNCHER_H