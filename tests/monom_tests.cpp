#include "monomDL.h"
#include "monomDRL.h"
#include "monomLex.h"

#include <cstdlib>
#include <iostream>


void setVariables()
{
    MonomDRL::addVariable("x0");
    MonomDRL::addVariable("x1");
    MonomDRL::addVariable("x2");
    MonomDRL::addVariable("x3");
    MonomDRL::addVariable("x4");
    MonomDRL::addVariable("x5");
}

bool runTestGroup1()
{
    const int groupNumber = 1;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1");
            currentResult = m1.toString() == "x1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2");
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x2*x1");
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1;
            currentResult = m1.toString() == "1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2");
            MonomDL m2(m1);
            currentResult = m2.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm2 = " << m2 << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL m1("x1");
            currentResult = m1.toString() == "x1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2");
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x2*x1");
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1;
            currentResult = m1.toString() == "1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2");
            MonomDRL m2(m1);
            currentResult = m2.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm2 = " << m2 << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex m1("x1");
            currentResult = m1.toString() == "x1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2");
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x2*x1");
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1;
            currentResult = m1.toString() == "1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2");
            MonomLex m2(m1);
            currentResult = m2.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm2 = " << m2 << std::endl;
            }
            result = result && currentResult;
        }
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
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL* m1 = new MonomDL("x1*x2*x3*x4");
            currentResult = m1 && m1->toString() == "x1*x2*x3*x4";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2");
            m1.setOne();
            currentResult = m1.toString() == "1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x2*x3*x4*x5"), m2("x2*x3*x5");
            currentResult = m1.degree() == 4 && m2.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1.degree() = " << m1.degree() << "; m2.degree() = " << m2.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x2*x3*x5");
            currentResult = m1[0] == 0 && m1[1] == 0 && m1[2] == 1 && m1[3] == 1 && m1[4] == 0 && m1[5] == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2");
            currentResult = m1[0] == 0 && m1[1] == 1 && m1[2] == 1 && m1[3] == 0 && m1[4] == 0 && m1[5] == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x2");
            currentResult = m1[0] == 0 && m1[1] == 0 && m1[2] == 1 && m1[3] == 0 && m1[4] == 0 && m1[5] == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL* m1 = new MonomDRL("x1*x2*x3*x4");
            currentResult = m1 && m1->toString() == "x1*x2*x3*x4";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2");
            m1.setOne();
            currentResult = m1.toString() == "1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x2*x3*x4*x5"), m2("x2*x3*x5");
            currentResult = m1.degree() == 4 && m2.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1.degree() = " << m1.degree() << "; m2.degree() = " << m2.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x2*x3*x5");
            currentResult = m1[0] == 0 && m1[1] == 0 && m1[2] == 1 && m1[3] == 1 && m1[4] == 0 && m1[5] == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2");
            currentResult = m1[0] == 0 && m1[1] == 1 && m1[2] == 1 && m1[3] == 0 && m1[4] == 0 && m1[5] == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x2");
            currentResult = m1[0] == 0 && m1[1] == 0 && m1[2] == 1 && m1[3] == 0 && m1[4] == 0 && m1[5] == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex* m1 = new MonomLex("x1*x2*x3*x4");
            currentResult = m1 && m1->toString() == "x1*x2*x3*x4";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2");
            m1.setOne();
            currentResult = m1.toString() == "1";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x2*x3*x4*x5"), m2("x2*x3*x5");
            currentResult = m1.degree() == 4 && m2.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1.degree() = " << m1.degree() << "; m2.degree() = " << m2.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x2*x3*x5");
            currentResult = m1[0] == 0 && m1[1] == 0 && m1[2] == 1 && m1[3] == 1 && m1[4] == 0 && m1[5] == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2");
            currentResult = m1[0] == 0 && m1[1] == 1 && m1[2] == 1 && m1[3] == 0 && m1[4] == 0 && m1[5] == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x2");
            currentResult = m1[0] == 0 && m1[1] == 0 && m1[2] == 1 && m1[3] == 0 && m1[4] == 0 && m1[5] == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cout << "\t\tm1[var] = " << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << ",";
            }
            result = result && currentResult;
        }
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
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x2*x3*x4"), m2("x1*x2");
            m1 = m2;
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << "; Inner structure = " << m1.innerStructure() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2"), m2("x1*x2");
            currentResult = m1 == m2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2"), m2("x1*x3");
            currentResult = !(m1 == m2);
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2"), m2("x1*x2");
            currentResult = !(m1 != m2);
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x2"), m2("x1*x3");
            currentResult = m1 != m2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2*x3*x4"), m2("x1*x2");
            m1 = m2;
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << "; Inner structure = " << m1.innerStructure() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2"), m2("x1*x2");
            currentResult = m1 == m2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2"), m2("x1*x3");
            currentResult = !(m1 == m2);
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2"), m2("x1*x2");
            currentResult = !(m1 != m2);
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2"), m2("x1*x3");
            currentResult = m1 != m2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex m1("x1*x2*x3*x4"), m2("x1*x2");
            m1 = m2;
            currentResult = m1.toString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << "; Inner structure = " << m1.innerStructure() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2"), m2("x1*x2");
            currentResult = m1 == m2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2"), m2("x1*x3");
            currentResult = !(m1 == m2);
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2"), m2("x1*x2");
            currentResult = !(m1 != m2);
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x2"), m2("x1*x3");
            currentResult = m1 != m2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << std::endl;
            }
            result = result && currentResult;
        }
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
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x4");
            m1 *= 1;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4");
            m1 *= 2;
            currentResult = m1.toString() == "x1*x2*x4" && m1.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4");
            m1 *= 4;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4");
            m1 *= 1;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4");
            m1 *= 2;
            currentResult = m1.toString() == "x1*x2*x4" && m1.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4");
            m1 *= 4;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex m1("x1*x4");
            m1 *= 1;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4");
            m1 *= 2;
            currentResult = m1.toString() == "x1*x2*x4" && m1.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4");
            m1 *= 4;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }
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
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x4"), m2("x2*x3");
            m1 *= m2;
            currentResult = m1.toString() == "x1*x2*x3*x4" && m1.degree() == 4;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4"), m2("x1*x3");
            m1 *= m2;
            currentResult = m1.toString() == "x1*x3*x4" && m1.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4"), m2;
            m1 *= m2;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4"), m2("x2*x3");
            m1 *= m2;
            currentResult = m1.toString() == "x1*x2*x3*x4" && m1.degree() == 4;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4"), m2("x1*x3");
            m1 *= m2;
            currentResult = m1.toString() == "x1*x3*x4" && m1.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4"), m2;
            m1 *= m2;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex m1("x1*x4"), m2("x2*x3");
            m1 *= m2;
            currentResult = m1.toString() == "x1*x2*x3*x4" && m1.degree() == 4;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4"), m2("x1*x3");
            m1 *= m2;
            currentResult = m1.toString() == "x1*x3*x4" && m1.degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4"), m2;
            m1 *= m2;
            currentResult = m1.toString() == "x1*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }
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
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x3*x4"), m2("x1");
            m1 /= m2;
            currentResult = m1.toString() == "x3*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x3*x4"), m2("x3*x4");
            m1 /= m2;
            currentResult = m1.toString() == "x1" && m1.degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x3*x4"), m2("x1*x3"), m3;
            m3.setQuotientOf(m1, m2);
            currentResult = m3.toString() == "x4" && m3.degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm3 = " << m3 << "; m3.degree() = " << m3.degree() << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3*x4"), m2("x1");
            m1 /= m2;
            currentResult = m1.toString() == "x3*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3*x4"), m2("x3*x4");
            m1 /= m2;
            currentResult = m1.toString() == "x1" && m1.degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3*x4"), m2("x1*x3"), m3;
            m3.setQuotientOf(m1, m2);
            currentResult = m3.toString() == "x4" && m3.degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm3 = " << m3 << "; m3.degree() = " << m3.degree() << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex m1("x1*x3*x4"), m2("x1");
            m1 /= m2;
            currentResult = m1.toString() == "x3*x4" && m1.degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x3*x4"), m2("x3*x4");
            m1 /= m2;
            currentResult = m1.toString() == "x1" && m1.degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.degree() = " << m1.degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x3*x4"), m2("x1*x3"), m3;
            m3.setQuotientOf(m1, m2);
            currentResult = m3.toString() == "x4" && m3.degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm3 = " << m3 << "; m3.degree() = " << m3.degree() << std::endl;
            }
            result = result && currentResult;
        }
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
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x3"), m2("x1*x4");
            currentResult = m1 > m2;
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
            MonomDL m1("x2*x3"), m2("x1*x4");
            currentResult = m1 < m2;
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
            MonomDL m1("x1*x3*x5"), m2("x1*x3*x4");
            currentResult = m1.compare(m2) == -1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " compare " << m2 << " = " << m1.compare(m2) << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x3"), m2("x1*x3");
            currentResult = m1.compare(m2) == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " compare " << m2 << " = " << m1.compare(m2) << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3"), m2("x1*x4");
            currentResult = m1 > m2;
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
            MonomDRL m1("x2*x3"), m2("x1*x4");
            currentResult = m1 > m2;
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
            MonomDRL m1("x1*x3*x5"), m2("x1*x3*x4");
            currentResult = m1.compare(m2) == -1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " compare " << m2 << " = " << m1.compare(m2) << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3"), m2("x1*x3");
            currentResult = m1.compare(m2) == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " compare " << m2 << " = " << m1.compare(m2) << std::endl;
            }
            result = result && currentResult;
        }
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex m1("x1*x3"), m2("x1*x4");
            currentResult = m1 > m2;
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
            MonomLex m1("x2*x3"), m2("x1*x4");
            currentResult = m1 < m2;
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
            MonomLex m1("x1*x3*x5"), m2("x1*x3*x4");
            currentResult = m1.compare(m2) == -1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " compare " << m2 << " = " << m1.compare(m2) << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x3"), m2("x1*x3");
            currentResult = m1.compare(m2) == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " compare " << m2 << " = " << m1.compare(m2) << std::endl;
            }
            result = result && currentResult;
        }
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

bool runTestGroup8()
{
    const int groupNumber = 8;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x2*x5"), m2("x2*x5");
            currentResult = m1.isDivisibleBy(m2);
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
            MonomDL m1("x1*x2*x5"), m2("x1*x4");
            currentResult = !m1.isDivisibleBy(m2);
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
            MonomDL m1("x1*x2*x3"), m2("x1*x2*x3*x4");
            currentResult = !m1.isDivisibleBy(m2);
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
            MonomDL m1("x1*x2*x3"), m2("x1*x2*x3");
            currentResult = m1.isDivisibleBy(m2);
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
            MonomDL m1("x1*x2*x3"), m2("x1*x2*x3");
            currentResult = !m1.isTrueDivisibleBy(m2);
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
    }

    {
        std::cout << "\tDegree Reverse Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDRL m1("x1*x2*x5"), m2("x2*x5");
            currentResult = m1.isDivisibleBy(m2);
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
            MonomDRL m1("x1*x2*x5"), m2("x1*x4");
            currentResult = !m1.isDivisibleBy(m2);
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
            MonomDRL m1("x1*x2*x3"), m2("x1*x2*x3*x4");
            currentResult = !m1.isDivisibleBy(m2);
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
            MonomDRL m1("x1*x2*x3"), m2("x1*x2*x3");
            currentResult = m1.isDivisibleBy(m2);
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
            MonomDRL m1("x1*x2*x3"), m2("x1*x2*x3");
            currentResult = !m1.isTrueDivisibleBy(m2);
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
    }

    {
        std::cout << "\tPure Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomLex m1("x1*x2*x5"), m2("x2*x5");
            currentResult = m1.isDivisibleBy(m2);
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
            MonomLex m1("x1*x2*x5"), m2("x1*x4");
            currentResult = !m1.isDivisibleBy(m2);
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
            MonomLex m1("x1*x2*x3"), m2("x1*x2*x3*x4");
            currentResult = !m1.isDivisibleBy(m2);
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
            MonomLex m1("x1*x2*x3"), m2("x1*x2*x3");
            currentResult = m1.isDivisibleBy(m2);
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
            MonomLex m1("x1*x2*x3"), m2("x1*x2*x3");
            currentResult = !m1.isTrueDivisibleBy(m2);
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
    result = result && runTestGroup8();

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
