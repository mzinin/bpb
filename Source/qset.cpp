#include "qset.h"

QSET::QSET(): tripleList()
{
}

QSET::QSET(list<Polynom*> &basis): tripleList()
{
    list<Polynom*>::const_iterator itBasis(basis.begin());
    while (itBasis != basis.end())
    {
        tripleList.push_back(new Triple(*itBasis));
        itBasis++;
    }
    tripleList.sort(Triple::compare);
}

QSET::~QSET()
{
    list<Triple*>::iterator it(tripleList.begin());
    while( it != tripleList.end() )
    {
        delete *it;
        it++;
    }
    tripleList.clear();
}

void QSET::insert(list<Polynom*> &addList)
{
    list<Polynom*>::const_iterator itBasis(addList.begin());
    while ( itBasis != addList.end() )
    {
        tripleList.push_back(new Triple(*itBasis));
        itBasis++;
    }
    tripleList.sort(Triple::compare);
}

void QSET::insert(list<Triple*> &addList)
{
    addList.sort(Triple::compare);
    tripleList.merge(addList, Triple::compare);
}


void QSET::update(Triple* newTriple, list<Triple*> &set)
{
    Monom::Integer firstMultiVar = newTriple->getPolyLm().firstMultiVar();
    Monom tmpMonom;

    for (register Monom::Integer var = 0; var < firstMultiVar; var++)
    {
        if (!newTriple->testNmp(var))
	{
            Polynom* tmpPolynom = new Polynom(*newTriple->getPoly());
            (*tmpPolynom) *= var;
            if (!tmpPolynom->isZero())
            {
                tmpMonom = newTriple->getPolyLm();
                tmpMonom *= var;
                if (tmpMonom == tmpPolynom->lm())
                {
                    set.push_back(new Triple(tmpPolynom,
                                             newTriple->getAnc(),
                                             newTriple,
                                             newTriple->getNmp(),
                                             var));
                }
                else
                {
                    set.push_back(new Triple(tmpPolynom));
                }
            }
            newTriple->setNmp(var);
        }
    }
}

Triple* QSET::get()
{
    Triple* result = tripleList.back();
    tripleList.pop_back();
    return result;
}

void QSET::deleteDescendants(Triple* ancestor)
{
    list<Triple*>::iterator it(tripleList.begin());
    while ( it != tripleList.end() )
    {
        if ((**it).getAnc() == ancestor)
        {
            delete *it;
            it = tripleList.erase(it);
        }
        else
        {
            it++;
        }
    }
}
