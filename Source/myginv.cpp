#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "timer.h"
#include "involutive.h"


int main(int argc, char *argv[])
{
    ifstream fileInputStream;
    if (argc == 1)
    {
        cout << "Usage:\n\t" << argv[0] << " <file_name.gnv>" << endl;
    	return EXIT_FAILURE;
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
            Monom::AddVariable(tmpString.c_str());
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
    timer.Start();
    GBasis basisGroebner(polyList);
    timer.Stop();

    //cout << basisGroebner << endl;
    cout << "Size: " << basisGroebner.Length() << endl;
    cout << timer << endl;


    bool isCorrect = true, Found;
    //checking
    if (basisGroebner.Length() != answerList.size())
    {
        isCorrect = false;
    }
    else
    {
        iterAnswerList = answerList.begin();
        while (iterAnswerList != answerList.end())
        {
            Found = false;
            for (register unsigned i = 0; i < basisGroebner.Length(); i++)
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
    {
        cout << "The answer is CORRECT" << endl;
    }
    else
    {
        cout << "The answer is WRONG" << endl;
    }

    return EXIT_SUCCESS;
}
