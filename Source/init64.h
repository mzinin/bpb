#include <iostream>
#include <fstream>
#include <sstream>
#include "timer.h"
#include "involutive64.h"

using namespace std;

int init64(char* fileName)
{
	ifstream fileInputStream(fileName);
	Timer timer;

	//-----чтение переменных
	char c = '0';
	std::string tmpString;
	while (c!=';' && !fileInputStream.eof())
	{
  		fileInputStream >> c;
		if (c==',' || c==';')
        	{
			Monom64::mIndepend->add(tmpString.c_str());
			tmpString.clear();
		}
		else
        	{
			tmpString += c;
		}
  	}
  	//-----конец чтения переменных

	Monom64::Init();
	Poly64 poly;
	list<Poly64*> polyList, answerList;
	list<Poly64*>::iterator iterPolyList(polyList.begin()), iterAnswerList(answerList.begin());

	stringstream* tmpStream = new stringstream();

	c = '0';
	//-----чтение начального набора
	while (c!=';' && !fileInputStream.eof())
	{
		fileInputStream >> c;
		if (c==',' || c==';')
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
		iterPolyList = polyList.insert(iterPolyList, new Poly64(poly));
	}
	delete tmpStream;
	//-----конец чтения начального набора

	tmpStream = new stringstream();

	c = '0';
	//-----чтение ответа
	while (c!=';' && !fileInputStream.eof())
	{
		fileInputStream >> c;
		if (c==',' || c==';')
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
		iterAnswerList = answerList.insert(iterAnswerList, new Poly64(poly));
	}
	delete tmpStream;
	//-----конец чтения ответа
	fileInputStream.close();

	timer.start();
	GBasis64 basisGroebner(polyList);
	timer.stop();
	cout << basisGroebner << endl;
	cout << timer << endl;

	bool isCorrect = true, Found;
	//-----проверка
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
			for (int i=0; i<basisGroebner.length(); i++)
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
  	//-----конец проверки

	if (isCorrect)
		cout << "The answer is CORRECT" << endl;
	else
		cout << "The answer is WRONG" << endl;

	return EXIT_SUCCESS;
}
