#include "monomDRL.h"
#include "polynom.h"

#include <cstdlib>
#include <iostream>
#include <sstream>


using MonomType = MonomDRL;
using PolynomType = Polynom<MonomType>;

MonomType monomFromString(const std::string& str)
{
    std::istringstream buffer(str);
    MonomType result;
    buffer >> result;
    return result;
}

PolynomType polynomFromString(const std::string& str)
{
    std::istringstream buffer(str);
    PolynomType result;
    buffer >> result;
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
        PolynomType p1;
        currentResult = p1.toString() == "0";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x4 + x0");
        currentResult = p1.toString() == "x1*x4 + x0";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("(x1+x2)^2");
        currentResult = p1.toString() == "x1 + x2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("1");
        currentResult = p1.toString() == "1";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("0");
        currentResult = p1.toString() == "0";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1^2*x2 + x2^2*x3^2 + x5 + x3");
        currentResult = p1.toString() == "x1*x2 + x2*x3 + x3 + x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2^2*x3^2 + x5 + x3");
        auto p2 = p1;
        currentResult = p2.toString() == "x1*x2 + x2*x3 + x3 + x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp2 = " << p2 << std::endl;
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
        auto p1 = polynomFromString("x1 + x2");
        p1.setOne();
        currentResult = p1.toString() == "1" && !p1.isZero();
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1 + x2");
        p1.setZero();
        currentResult = p1.toString() == "0" && p1.isZero();
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        PolynomType p1;
        currentResult = p1.isZero();
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1");
        currentResult = !p1.isZero();
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
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

bool runTestGroup3()
{
    const int groupNumber = 3;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2 + x1 + x2");
        currentResult = p1.length() == 2;
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2*x4 + x2*x3 + x4*x1 + x5 + x4*x2*x1");
        currentResult = p1.degree() == 2;
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2*x4 + x2*x3 + x4*x1 + x5 + x4*x2*x1");
        currentResult = p1.lm().toString() == "x2*x3";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2*x4 + x2*x3 + x4*x1 + x5 + x4*x2*x1");
        p1.ridOfLm();
        currentResult = p1.toString() == "x1*x4 + x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x2*x3 + x4*x1 + x5 + x4*x2*x1");
        currentResult = p1.toString() == "x1*x2*x4 + x2*x3 + x1*x4 + x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;

        PolynomType* p1 = new PolynomType(polynomFromString("x2*x3 + x4*x1 + x5 + x4*x2*x1"));
        currentResult = p1;
        delete p1;
        p1 = 0;
        currentResult = currentResult && !p1;
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
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

bool runTestGroup4()
{
    const int groupNumber = 4;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2");
        auto p2 = polynomFromString("x3 + x4");
        p2 = p1;
        currentResult = p1.toString() == "x1*x2 + x2" && p2.toString() == "x1*x2 + x2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp2 = " << p2 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2");
        auto m1 = monomFromString("x2");
        p1 += m1;
        currentResult = p1.toString() == "x1*x2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2");
        auto m1 = monomFromString("x1*x2");
        p1 += m1;
        currentResult = p1.toString() == "x2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x4");
        auto m1 = monomFromString("x2");
        p1 += m1;
        currentResult = p1.toString() == "x1*x2 + x2 + x4";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x4");
        auto p2 = polynomFromString("x1^2 + x5");
        p1 += p2;
        currentResult = p1.toString() == "x1*x2 + x1 + x4 + x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x4");
        auto p2 = polynomFromString("x1^2 + x4");
        p1 += p2;
        currentResult = p1.toString() == "x1*x2 + x1";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x4");
        auto p2 = polynomFromString("x1^2 + x1*x2 + x4");
        p1 += p2;
        currentResult = p1.toString() == "x1";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x4");
        auto p2 = polynomFromString("x1*x2 + x4");
        p1 += p2;
        currentResult = p1.toString() == "0" && p1.isZero();
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
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

bool runTestGroup5()
{
    const int groupNumber = 5;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x3^3 + x1*x2 + x2 + x5");
        p1 *= 2;
        currentResult = p1.toString() == "x1*x2 + x2*x3 + x2*x5 + x2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x3^3 + x1*x2 + x2 + x5");
        p1 *= 1;
        currentResult = p1.toString() == "x1*x3 + x1*x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x3^3 + x1*x2 + x5 + x2");
        auto m1 = monomFromString("x1*x2");
        p1 *= m1;
        currentResult = p1.toString() == "x1*x2*x3 + x1*x2*x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x3^3 + x1*x2 + x5 + x2");
        auto p2 = polynomFromString("x1 + x2");
        p1 *= p2;
        currentResult = p1.toString() == "x1*x2 + x1*x3 + x2*x3 + x1*x5 + x2*x5 + x2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1 + x2");
        auto p2 = polynomFromString("x1 + x2");
        p1 *= p2;
        currentResult = p1.toString() == "x1 + x2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\tp1 = " << p1 << std::endl;
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

bool runTestGroup6()
{
    const int groupNumber = 6;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2 + x5");
        auto p2 = polynomFromString("x1*x2 + x2 + x4");
        currentResult = !(p1 == p2);
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2 + x5");
        auto p2 = polynomFromString("x1*x2 + x5 + x2");
        currentResult = (p1 == p2);
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1 + x5");
        auto p2 = polynomFromString("x5 + x2");
        currentResult = (p1 != p2);
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2 + x5");
        auto p2 = polynomFromString("x1*x2 + x2 + x4");
        currentResult = (p1 < p2);
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2 + x5");
        auto p2 = polynomFromString("x1*x3 + x2 + x4");
        currentResult = (p1 > p2);
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2*x3 + x5");
        auto p2 = polynomFromString("x1*x2 + x2 + x4");
        currentResult = PolynomType::compare(p1, p2) == 1;
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2*x5 + x5");
        auto p2 = polynomFromString("x1*x2*x3 + x2*x3 + x4");
        currentResult = PolynomType::compare(p1, p2) == -1;
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1*x2 + x2*x5 + x5");
        auto p2 = polynomFromString("x2*x5 + x5 + x1*x2");
        currentResult = PolynomType::compare(p1, p2) == 0;
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
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

bool runTestGroup7()
{
    const int groupNumber = 7;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1^2*x2 + x2 + x5");
        auto p2 = polynomFromString("x1 + x2");
        p1.reduction(p2);
        currentResult = p1.toString() == "x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
        }
        result = result && currentResult;
    }

    {
        ++currentTestNumber;
        auto p1 = polynomFromString("x1^2*x2 + x1 + x2 + x5");
        auto p2 = polynomFromString("x1 + x2");
        p1.headReduction(p2);
        currentResult = p1.toString() == "x2 + x5";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed. " << p1 << std::endl;
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
    result = result && runTestGroup3();
    result = result && runTestGroup4();
    result = result && runTestGroup5();
    result = result && runTestGroup6();
    result = result && runTestGroup7();

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
