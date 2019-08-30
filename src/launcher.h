#pragma once

#include "groebner_basis.h"
#include "polynom.h"
#include "settings_manager.h"

#include <list>
#include <string>


class Launcher
{
public:
    Launcher();

    bool init(int argc, char* argv[]);
    bool run();

private:
    static void fillOptions();

    void printUsage() const;
    void printVersion() const;
    bool analizeArguments(int argc, char* argv[]);

    template <typename MonomType>
    bool doMonomTypeDependStuff() const;

    template <typename MonomType>
    bool getTaskFromFile(std::list<Polynom<MonomType>*>& initialSet, std::list<Polynom<MonomType>*>& initialAnswer) const;

    template <typename MonomType>
    void readVariables(std::ifstream& inputFileStream) const;

    template <typename MonomType>
    void readPolynomList(std::ifstream& inputFileStream, std::list<Polynom<MonomType>*>& list) const;

    template <typename MonomType>
    void clearPolynomList(std::list<Polynom<MonomType>*>& list) const;

    template <typename MonomType>
    void printResult(GroebnerBasis<MonomType>& gBasis, std::list<Polynom<MonomType>*>& initialAnswer) const;

    template <typename MonomType>
    bool checkAnswer(GroebnerBasis<MonomType>& gBasis, std::list<Polynom<MonomType>*>& initialAnswer) const;

private:
    std::string applicationName_;
    std::string inputFileName_;
};
