#include "..\janettree.h"
#include <iostream>
#include <set>

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
        Triple t1(new Polynom("x1^2*x3 + x1")), t2(new Polynom("x1*x2 + x2")), t3(new Polynom("x1*x3^2 + x3"));
        
        JanetTree jTree;
        jTree.Insert(&t1);
        jTree.Insert(&t2);
        jTree.Insert(&t3);
        
        std::set<Monom::Integer> nmv = jTree.NonMulti(&t1);
        
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
        Triple t1(new Polynom("x1^2*x3 + x1")), t2(new Polynom("x1*x2 + x2")), t3(new Polynom("x1*x3^2 + x3"));

        JanetTree jTree;
        jTree.Insert(&t1);
        jTree.Insert(&t2);
        jTree.Insert(&t3);

        std::set<Monom::Integer> nmv = jTree.NonMulti(&t2);
        currentResult = nmv.size() == 1 && nmv.count(1);
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
        Triple t1(new Polynom("x1^2*x3 + x1")), t2(new Polynom("x1*x2 + x2")), t3(new Polynom("x1*x3^2 + x3"));
        
        JanetTree jTree;
        jTree.Insert(&t1);
        jTree.Insert(&t2);
        jTree.Insert(&t3);
        
        std::set<Monom::Integer> nmv = jTree.NonMulti(&t3);
        
        currentResult = nmv.size() == 2 && nmv.count(1) && nmv.count(2);
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

bool RunTestGroup2()
{
    const int groupNumber = 2;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        ++currentTestNumber;
        Triple t1(new Polynom("x0^2")), t2(new Polynom("x1^2")), t3(new Polynom("x2^2"));
        
        JanetTree jTree;
        jTree.Insert(&t1);
        jTree.Insert(&t2);
        jTree.Insert(&t3);
        
        Monom m1("x1^2*x2^2");
        const Triple* found = jTree.Find(m1);
        
        currentResult = found && found->GetPolynomLm().ToString() == "x1^2";
        if (currentResult)
        {
            std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
        }
        else
        {
            std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
            std::cerr << "\t\found->GetPolynomLm() = " << found->GetPolynomLm() << std::endl;
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