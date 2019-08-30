#include "janettree.h"
#include "monomDRL.h"
#include "polynom.h"
#include "triple.h"

#include <cstdlib>
#include <iostream>
#include <set>


using MonomType = MonomDRL;
using PolynomType = Polynom<MonomType>;
using TripleType = Triple<MonomType>;
using JanetTreeType = JanetTree<MonomType>;

MonomType monomFromString(const std::string& str)
{
    std::istringstream buffer(str);
    MonomType result;
    buffer >> result;
    return result;
}

PolynomType* polynomFromString(const std::string& str)
{
    std::istringstream buffer(str);
    PolynomType* result = new PolynomType();;
    buffer >> *result;
    return result;
}

void setVariables()
{
    MonomType::addVariable("x0");
    MonomType::addVariable("x1");
    MonomType::addVariable("x2");
    MonomType::addVariable("x3");
    MonomType::addVariable("x4");
    MonomType::addVariable("x5");
}

bool runTestGroup1()
{
    const int groupNumber = 1;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        TripleType t1(polynomFromString("x1^2*x3 + x1")), t2(polynomFromString("x1*x2 + x2")), t3(polynomFromString("x1*x4^2 + x3"));

        JanetTreeType jTree;
        jTree.insert(&t1);
        jTree.insert(&t2);
        jTree.insert(&t3);

        std::set<MonomType::Integer> nmv = jTree.nonMulti(&t2);

        currentResult = nmv.empty();
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tnmv.size() = " << nmv.size() << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        TripleType t1(polynomFromString("x1^2*x3 + x1")), t2(polynomFromString("x1*x2 + x2")), t3(polynomFromString("x1*x4^2 + x3"));

        JanetTreeType jTree;
        jTree.insert(&t1);
        jTree.insert(&t2);
        jTree.insert(&t3);

        std::set<MonomType::Integer> nmv = jTree.nonMulti(&t1);
        currentResult = nmv.size() == 1 && nmv.count(2);
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tnmv.size() = " << nmv.size() << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        TripleType t1(polynomFromString("x1^2*x3 + x1")), t2(polynomFromString("x1*x2 + x2")), t3(polynomFromString("x1*x4^2 + x3"));

        JanetTreeType jTree;
        jTree.insert(&t1);
        jTree.insert(&t2);
        jTree.insert(&t3);

        std::set<MonomType::Integer> nmv = jTree.nonMulti(&t3);

        currentResult = nmv.size() == 2 && nmv.count(2) && nmv.count(3);
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tnmv.size() = " << nmv.size() << std::endl;
        }
        result = result && currentResult;
    }

    if (result)
    {
        std::cout << "***** Test group " << groupNumber << " succeded *****" << std::endl << std::endl;
    }
    else
    {
        std::cout << "*** Test group " << groupNumber << " FAILED ***" << std::endl;
    }
    return result;
}

bool runTestGroup2()
{
    const int groupNumber = 2;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        TripleType t1(polynomFromString("x0^2")), t2(polynomFromString("x1^2")), t3(polynomFromString("x2^2"));

        JanetTreeType jTree;
        jTree.insert(&t1);
        jTree.insert(&t2);
        jTree.insert(&t3);

        auto m1 = monomFromString("x1^2*x2^2");
        const auto* found = jTree.find(m1);

        currentResult = found && found->polynomLm().toString() == "x1";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\found->polynomLm() = " << found->polynomLm() << std::endl;
        }
        result = result && currentResult;
    }

    if (result)
    {
        std::cout << "***** Test group " << groupNumber << " succeded *****" << std::endl << std::endl;
    }
    else
    {
        std::cout << "*** Test group " << groupNumber << " FAILED ***" << std::endl;
    }
    return result;
}

int main()
{
    setVariables();

    bool result = runTestGroup1();
    result = result && runTestGroup2();

    if (result)
    {
        std::cout << "***** All tests succeeded *****" << std::endl;
    }
    else
    {
        std::cout << "***** SOME TESTS FAILED!!! *****" << std::endl;
    }

    return EXIT_SUCCESS;
}
