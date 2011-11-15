#include "..\polynom.h"
#include <iostream>

void SetVariables()
{
    Monom::AddVariable("x0");
    Monom::AddVariable("x1");
    Monom::AddVariable("x2");
    Monom::AddVariable("x3");
    Monom::AddVariable("x4");
    Monom::AddVariable("x5");
}

bool RunTestGroup1()
{
    const int groupNumber = 1;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        Polynom p1;
        currentResult = p1.ToString() == "0";
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
        Polynom p1("x1*x4 + x0");
        currentResult = p1.ToString() == "x1*x4 + x0";
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
        Polynom p1("(x1+x2)^2");
        currentResult = p1.ToString() == "x1^2 + x2^2";
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
        Polynom p1("1");
        currentResult = p1.ToString() == "1";
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
        Polynom p1("0");
        currentResult = p1.ToString() == "0";
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
        Polynom p1("x1^2*x2 + x2^2*x3^2 + x5 + x3");
        currentResult = p1.ToString() == "x2^2*x3^2 + x1^2*x2 + x3 + x5";
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
        Polynom p1("x1*x2 + x2^2*x3^2 + x5 + x3");
        Polynom p2(p1);
        currentResult = p2.ToString() == "x2^2*x3^2 + x1*x2 + x3 + x5";
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

bool RunTestGroup2()
{
    const int groupNumber = 2;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        Polynom p1("x1 + x2");
        p1.SetOne();
        currentResult = p1.ToString() == "1" && !p1.IsZero();
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
        Polynom p1("x1 + x2");
        p1.SetZero();
        currentResult = p1.ToString() == "0" && p1.IsZero();
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
        Polynom p1;
        currentResult = p1.IsZero();
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
        Polynom p1("x1");
        currentResult = !p1.IsZero();
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
        Polynom p1("x1^2");
        currentResult = !p1.IsBinomial();
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
        Polynom p1("x1^2 + x2");
        currentResult = !p1.IsBinomial();
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
        Polynom p1("x3^2 + x3");
        currentResult = p1.IsBinomial();
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
        Polynom p1("x1*x2 + x1");
        currentResult = !p1.IsBinomial();
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

bool RunTestGroup3()
{
    const int groupNumber = 3;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        Polynom p1("x1*x2 + x2 + x1 + x2");
        currentResult = p1.Length() == 2;
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
        Polynom p1("x1*x2*x4 + x2*x3 + x4*x1 + x5 + x4*x2*x1");
        currentResult = p1.Degree() == 2;
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
        Polynom p1("x1*x2*x4 + x2*x3 + x4*x1 + x5 + x4*x2*x1");
        currentResult = p1.Lm().ToString() == "x2*x3";
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
        Polynom p1("x1*x2*x4 + x2*x3 + x4*x1 + x5 + x4*x2*x1");
        p1.RidOfLm();
        currentResult = p1.ToString() == "x1*x4 + x5";
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
        Polynom* p1 = new Polynom("x2*x3 + x4*x1 + x5 + x4*x2*x1");
        currentResult = p1 && p1->ToString() == "x1*x2*x4 + x2*x3 + x1*x4 + x5";
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
        Polynom* p1 = new Polynom("x2*x3 + x4*x1 + x5 + x4*x2*x1");
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

bool RunTestGroup4()
{
    const int groupNumber = 4;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;
    
    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;
    
    {
        ++currentTestNumber;
        Polynom p1("x1*x2 + x2"), p2("x3 + x4");
        p2 = p1;
        currentResult = p1.ToString() == "x1*x2 + x2" && p2.ToString() == "x1*x2 + x2";
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
        Polynom p1("x1*x2 + x2");
        Monom m1("x2");
        p1 += m1;
        currentResult = p1.ToString() == "x1*x2";
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
        Polynom p1("x1*x2 + x2");
        Monom m1("x1*x2");
        p1 += m1;
        currentResult = p1.ToString() == "x2";
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
        Polynom p1("x1*x2 + x4");
        Monom m1("x2");
        p1 += m1;
        currentResult = p1.ToString() == "x1*x2 + x2 + x4";
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
        Polynom p1("x1*x2 + x4"), p2("x1^2 + x5");
        p1 += p2;
        currentResult = p1.ToString() == "x1^2 + x1*x2 + x4 + x5";
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
        Polynom p1("x1*x2 + x4"), p2("x1^2 + x4");
        p1 += p2;
        currentResult = p1.ToString() == "x1^2 + x1*x2";
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
        Polynom p1("x1*x2 + x4"), p2("x1^2 + x1*x2 + x4");
        p1 += p2;
        currentResult = p1.ToString() == "x1^2";
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
        Polynom p1("x1*x2 + x4"), p2("x1*x2 + x4");
        p1 += p2;
        currentResult = p1.ToString() == "0" && p1.IsZero();
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

bool RunTestGroup5()
{
    const int groupNumber = 5;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;
    
    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;
    
    {
        ++currentTestNumber;
        Polynom p1("x3^3 + x1*x2 + x2 + x5");
        p1.Multiply(2, 2);
        currentResult = p1.ToString() == "x2^2*x3^3 + x1*x2^3 + x2^3 + x2^2*x5";
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
        Polynom p1("x3^3 + x1*x2 + x2 + x5");
        p1.Multiply(1, 1);
        currentResult = p1.ToString() == "x1*x3^3 + x1^2*x2 + x1*x2 + x1*x5";
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
        Polynom p1("x3^3 + x1*x2 + x5 + x2");
        Monom m1("x1*x2");
        p1.Multiply(m1);
        currentResult = p1.ToString() == "x1*x2*x3^3 + x1^2*x2^2 + x1*x2^2 + x1*x2*x5";
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
        Polynom p1("x3^3 + x1*x2 + x5 + x2"), p2("x1 + x2");
        p1.Multiply(p2);
        currentResult = p1.ToString() == "x1*x3^3 + x2*x3^3 + x1^2*x2 + x1*x2^2 + x1*x2 + x2^2 + x1*x5 + x2*x5";
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
        Polynom p1("x1 + x2"), p2("x1 + x2");
        p1.Multiply(p2);
        currentResult = p1.ToString() == "x1^2 + x2^2";
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

bool RunTestGroup6()
{
    const int groupNumber = 6;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;
    
    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;
    
    {
        ++currentTestNumber;
        Polynom p1("x1*x2 + x2 + x5"), p2("x1*x2 + x2 + x4");
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
        Polynom p1("x1*x2 + x2 + x5"), p2("x1*x2 + x5 + x2");
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
        Polynom p1("x1 + x5"), p2("x5 + x2");
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
        Polynom p1("x1*x2 + x2 + x5"), p2("x1*x2 + x2 + x4");
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
        Polynom p1("x1*x2 + x2 + x5"), p2("x1*x3 + x2 + x4");
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
        Polynom p1("x1*x2 + x2*x3 + x5"), p2("x1*x2 + x2 + x4");
        currentResult = Polynom::Compare(p1, p2) == 1;
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
        Polynom p1("x1*x2 + x2*x5 + x5"), p2("x1*x2*x3 + x2*x3 + x4");
        currentResult = Polynom::Compare(p1, p2) == -1;
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
        Polynom p1("x1*x2 + x2*x5 + x5"), p2("x2*x5 + x5 + x1*x2");
        currentResult = Polynom::Compare(p1, p2) == 0;
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

bool RunTestGroup7()
{
    const int groupNumber = 7;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;
    
    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;
    
    {
        ++currentTestNumber;
        Polynom p1("x1^2*x2 + x2 + x5"), p2("x1 + x2");
        p1.Reduction(p2);
        currentResult = p1.ToString() == "x2^3 + x2 + x5";
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
        Polynom p1("x1^2*x2 + x1 + x2 + x5"), p2("x1 + x2");
        p1.HeadReduction(p2);
        currentResult = p1.ToString() == "x2^3 + x1 + x2 + x5";
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

int main()
{
    SetVariables();

    bool result = RunTestGroup1();
    result = result && RunTestGroup2();
    result = result && RunTestGroup3();
    result = result && RunTestGroup4();
    result = result && RunTestGroup5();
    result = result && RunTestGroup6();
    result = result && RunTestGroup7();

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