#include "..\monomDL.h"
#include "..\monomDRL.h"
#include "..\monomLex.h"
#include <iostream>

void SetVariables()
{
    MonomDRL::AddVariable("x0");
    MonomDRL::AddVariable("x1");
    MonomDRL::AddVariable("x2");
    MonomDRL::AddVariable("x3");
    MonomDRL::AddVariable("x4");
    MonomDRL::AddVariable("x5");
}

bool RunTestGroup1()
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
            currentResult = m1.ToString() == "x1";
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
            currentResult = m1.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "1";
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
            currentResult = m2.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "x1";
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
            currentResult = m1.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "1";
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
            currentResult = m2.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "x1";
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
            currentResult = m1.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "x1*x2";
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
            currentResult = m1.ToString() == "1";
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
            currentResult = m2.ToString() == "x1*x2";
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

bool RunTestGroup2()
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
            currentResult = m1 && m1->ToString() == "x1*x2*x3*x4";
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
            m1.SetOne();
            currentResult = m1.ToString() == "1";
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
            currentResult = m1.Degree() == 4 && m2.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1.Degree() = " << m1.Degree() << "; m2.Degree() = " << m2.Degree() << std::endl;
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
            currentResult = m1 && m1->ToString() == "x1*x2*x3*x4";
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
            m1.SetOne();
            currentResult = m1.ToString() == "1";
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
            currentResult = m1.Degree() == 4 && m2.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1.Degree() = " << m1.Degree() << "; m2.Degree() = " << m2.Degree() << std::endl;
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
            currentResult = m1 && m1->ToString() == "x1*x2*x3*x4";
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
            m1.SetOne();
            currentResult = m1.ToString() == "1";
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
            currentResult = m1.Degree() == 4 && m2.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1.Degree() = " << m1.Degree() << "; m2.Degree() = " << m2.Degree() << std::endl;
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

bool RunTestGroup3()
{
    const int groupNumber = 3;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x2*x3*x4"), m2("x1*x2");
            m1 = m2;
            currentResult = m1.ToString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << "; Inner structure = " << m1.GetInnerStructure() << std::endl;
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
            currentResult = m1.ToString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << "; Inner structure = " << m1.GetInnerStructure() << std::endl;
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
            currentResult = m1.ToString() == "x1*x2";
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << "; Inner structure = " << m1.GetInnerStructure() << std::endl;
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

bool RunTestGroup4()
{
    const int groupNumber = 4;
    int currentTestNumber = 0;
    bool result = true, currentResult = false;

    std::cout << "***** Running test group " << groupNumber << " *****" << std::endl;

    {
        std::cout << "\tDegree Lexicographical" << std::endl;
        int currentTestNumber = 0;
        {
            ++currentTestNumber;
            MonomDL m1("x1*x4");
            m1 *= 1;
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4");
            m1 *= 2;
            currentResult = m1.ToString() == "x1*x2*x4" && m1.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4");
            m1 *= 4;
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
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
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4");
            m1 *= 2;
            currentResult = m1.ToString() == "x1*x2*x4" && m1.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4");
            m1 *= 4;
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
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
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4");
            m1 *= 2;
            currentResult = m1.ToString() == "x1*x2*x4" && m1.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4");
            m1 *= 4;
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
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

bool RunTestGroup5()
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
            currentResult = m1.ToString() == "x1*x2*x3*x4" && m1.Degree() == 4;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4"), m2("x1*x3");
            m1 *= m2;
            currentResult = m1.ToString() == "x1*x3*x4" && m1.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x4"), m2;
            m1 *= m2;
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
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
            currentResult = m1.ToString() == "x1*x2*x3*x4" && m1.Degree() == 4;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4"), m2("x1*x3");
            m1 *= m2;
            currentResult = m1.ToString() == "x1*x3*x4" && m1.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x4"), m2;
            m1 *= m2;
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
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
            currentResult = m1.ToString() == "x1*x2*x3*x4" && m1.Degree() == 4;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4"), m2("x1*x3");
            m1 *= m2;
            currentResult = m1.ToString() == "x1*x3*x4" && m1.Degree() == 3;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x4"), m2;
            m1 *= m2;
            currentResult = m1.ToString() == "x1*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
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

bool RunTestGroup6()
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
            currentResult = m1.ToString() == "x3*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x3*x4"), m2("x3*x4");
            m1 /= m2;
            currentResult = m1.ToString() == "x1" && m1.Degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x3*x4"), m2("x1*x3"), m3;
            m3.SetQuotientOf(m1, m2);
            currentResult = m3.ToString() == "x4" && m3.Degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm3 = " << m3 << "; m3.Degree() = " << m3.Degree() << std::endl;
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
            currentResult = m1.ToString() == "x3*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3*x4"), m2("x3*x4");
            m1 /= m2;
            currentResult = m1.ToString() == "x1" && m1.Degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3*x4"), m2("x1*x3"), m3;
            m3.SetQuotientOf(m1, m2);
            currentResult = m3.ToString() == "x4" && m3.Degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm3 = " << m3 << "; m3.Degree() = " << m3.Degree() << std::endl;
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
            currentResult = m1.ToString() == "x3*x4" && m1.Degree() == 2;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x3*x4"), m2("x3*x4");
            m1 /= m2;
            currentResult = m1.ToString() == "x1" && m1.Degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm1 = " << m1 << "; m1.Degree() = " << m1.Degree() << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x3*x4"), m2("x1*x3"), m3;
            m3.SetQuotientOf(m1, m2);
            currentResult = m3.ToString() == "x4" && m3.Degree() == 1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\tm3 = " << m3 << "; m3.Degree() = " << m3.Degree() << std::endl;
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

bool RunTestGroup7()
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
            currentResult = m1.Compare(m2) == -1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " Compare " << m2 << " = " << m1.Compare(m2) << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDL m1("x1*x3"), m2("x1*x3");
            currentResult = m1.Compare(m2) == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " Compare " << m2 << " = " << m1.Compare(m2) << std::endl;
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
            currentResult = m1.Compare(m2) == -1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " Compare " << m2 << " = " << m1.Compare(m2) << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomDRL m1("x1*x3"), m2("x1*x3");
            currentResult = m1.Compare(m2) == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " Compare " << m2 << " = " << m1.Compare(m2) << std::endl;
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
            currentResult = m1.Compare(m2) == -1;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " Compare " << m2 << " = " << m1.Compare(m2) << std::endl;
            }
            result = result && currentResult;
        }

        {
            ++currentTestNumber;
            MonomLex m1("x1*x3"), m2("x1*x3");
            currentResult = m1.Compare(m2) == 0;
            if (currentResult)
            {
                std::cout << "\tTest " << groupNumber << "-" << currentTestNumber << " succeded." << std::endl;
            }
            else
            {
                std::cerr << "\t\tTest " << groupNumber << "-" << currentTestNumber << " failed." << std::endl;
                std::cerr << "\t\t" << m1 << " Compare " << m2 << " = " << m1.Compare(m2) << std::endl;
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

bool RunTestGroup8()
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
            currentResult = m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsDivisibleBy(m2);
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
            currentResult = m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsTrueDivisibleBy(m2);
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
            currentResult = m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsDivisibleBy(m2);
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
            currentResult = m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsTrueDivisibleBy(m2);
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
            currentResult = m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsDivisibleBy(m2);
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
            currentResult = m1.IsDivisibleBy(m2);
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
            currentResult = !m1.IsTrueDivisibleBy(m2);
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
    SetVariables();

    bool result = RunTestGroup1();
    result = result && RunTestGroup2();
    result = result && RunTestGroup3();
    result = result && RunTestGroup4();
    result = result && RunTestGroup5();
    result = result && RunTestGroup6();
    result = result && RunTestGroup7();
    result = result && RunTestGroup8();

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