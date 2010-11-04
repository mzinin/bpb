#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <list>
#include <string>

#include "involutive.h"
#include "polynom.h"
#include "timer.h"

class Launcher
{
private:
    std::string ApplicationName;
    std::string InputFileName;
    std::list<Polynom*> InitialSet;
    std::list<Polynom*> InitialAnswer;
    GBasis GroebnerBasis;
    Timer GBCommonTimer;

public:
    Launcher();
    ~Launcher();

    bool Init(int argc, char *argv[]);
    bool Run();
    void PrintResult() const;

private:
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