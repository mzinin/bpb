#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>


#include "timer.h"
#include "involutive.h"

using namespace std;


int main(int argc, char *argv[])
{
    ifstream fileInputStream;
    if (argc == 1)
    {
        //cout << "Usage:\n\t" << argv[0] << " <file_name.gnv>" << endl;
    	//return EXIT_FAILURE;
        fileInputStream.open("life6.gnv");
    }
    else
    {
        fileInputStream.open(argv[1]);
        if (!fileInputStream)
        {
            cout << "No such file:" << argv[1] << endl;
            return EXIT_FAILURE;
        }
    }


    //read variables
    char c = '0';
    std::string tmpString;
    while (c != ';' && !fileInputStream.eof())
    {
        fileInputStream >> c;
        if (c == ',' || c == ';')
        {
            Monom::addVariable(tmpString.c_str());
            tmpString.clear();
        }
        else
        {
            tmpString += c;
        }
    }
    //variales are read


    Polynom poly;
    list<Polynom*> polyList, answerList;
    list<Polynom*>::iterator iterPolyList(polyList.begin()), iterAnswerList(answerList.begin());


    stringstream* tmpStream = new stringstream();
    c = '0';
    //read initial polynomial set
    while (c != ';' && !fileInputStream.eof())
    {
        fileInputStream >> c;
        if (c == ',' || c == ';')
        {
            *tmpStream << tmpString << endl;
            tmpString.clear();
        }
        else
        {
            tmpString += c;
        }
    }


    while (!tmpStream->eof())
    {
        *tmpStream >> poly;
        iterPolyList = polyList.insert(iterPolyList, new Polynom(poly));
    }

    delete tmpStream;
    //initial polynomial set is read


    tmpStream = new stringstream();
    c = '0';
    //read answer set
    while (c != ';' && !fileInputStream.eof())
    {
        fileInputStream >> c;
        if (c == ',' || c == ';')
        {
            *tmpStream << tmpString << endl;
            tmpString.clear();
        }
        else
        {
            tmpString += c;
        }
    }


    while (!tmpStream->eof())
    {
        *tmpStream >> poly;
        iterAnswerList = answerList.insert(iterAnswerList, new Polynom(poly));
    }

    delete tmpStream;
    //answer set is read


    fileInputStream.close();

    Timer timer;
    timer.start();
    GBasis basisGroebner(polyList);
    timer.stop();
    //cout << basisGroebner << endl;
    cout << timer << endl;


    bool isCorrect = true, Found;
    //checking
    if (basisGroebner.length() != answerList.size())
    {
        isCorrect = false;
    }
    else
    {
        iterAnswerList = answerList.begin();
        while (iterAnswerList != answerList.end())
        {
            Found = false;
            for (int i = 0; i < basisGroebner.length(); i++)
            {
                if (*basisGroebner[i] == **iterAnswerList)
                {
                    Found = true;
                    break;
                }
            }
            if (!Found)
            {
                isCorrect = false;
                cout << "The mistake is here " << **iterAnswerList << endl;
                break;
            }
            iterAnswerList++;
        }
    }
    cout << endl;
    //end checking


    if (isCorrect)
        cout << "The answer is CORRECT" << endl;
    else
        cout << "The answer is WRONG" << endl;


    return EXIT_SUCCESS;
}

/*
int main(int argc, char *argv[])
{
    ifstream fileInputStream;
    if (argc == 1)
    {
        //cout << "Usage:\n\t" << argv[0] << " <file_name.gnv>" << endl;
        //return EXIT_FAILURE;
        fileInputStream.open("test.gnv");
    }
    else
    {
        fileInputStream.open(argv[1]);
        if (!fileInputStream)
        {
            cout << "No such file:" << argv[1] << endl;
            return EXIT_FAILURE;
        }
    }


    //read variables
    char c = '0';
    std::string tmpString;
    while (c != ';' && !fileInputStream.eof())
    {
        fileInputStream >> c;
        if (c == ',' || c == ';')
        {
            Monom::addVariable(tmpString.c_str());
            tmpString.clear();
        }
        else
        {
            tmpString += c;
        }
    }
    //variales are read

    Polynom p1, p2, p3;
    Monom m1, m2, m3;

    fileInputStream >> p1;
    fileInputStream >> p2;

    cout << "1st polynom: " << p1 << "; degree: " << p1.degree() << endl;
    cout << "2nd polynom: " << p2 << "; degree: " << p2.degree() << endl << endl;

    p1.reduction(p2);

    cout << "1st polynom: " << p1 << "; degree: " << p1.degree() << endl;
    cout << "2nd polynom: " << p2 << "; degree: " << p2.degree() << endl << endl;


    fileInputStream.close();
    return EXIT_SUCCESS;
}
*/
