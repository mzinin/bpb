#include "qset.h"

QSET::QSET(): tripleList()
{
}

QSET::QSET(const list<Polynom*>& basis): tripleList()
{
    list<Polynom*>::const_iterator itBasis(basis.begin());
    while (itBasis != basis.end())
    {
        tripleList.push_back(new Triple(*itBasis));
        itBasis++;
    }
    tripleList.sort(Triple::Compare);
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

void QSET::Insert(list<Polynom*>& addList)
{
    list<Polynom*>::const_iterator itBasis(addList.begin());
    while ( itBasis != addList.end() )
    {
        tripleList.push_back(new Triple(*itBasis));
        itBasis++;
    }
    tripleList.sort(Triple::Compare);
}

void QSET::Insert(list<Triple*>& addList)
{
    addList.sort(Triple::Compare);
    tripleList.merge(addList, Triple::Compare);
}


void QSET::Update(Triple* newTriple, list<Triple*>& set)
{
    Monom::Integer firstMultiVar = newTriple->GetPolyLm().FirstMultiVar();
    Monom tmpMonom;

    for (register Monom::Integer var = 0; var < firstMultiVar; var++)
    {
        if (!newTriple->TestNmp(var))
	{
#ifdef USE_REAL_MINSTRATEGY
            Monom::Integer hiddenDegree = 0;
            if (newTriple->GetPolyLm()[var]) hiddenDegree++;
#endif
            Polynom* tmpPolynom = new Polynom(*newTriple->GetPoly());
            (*tmpPolynom) *= var;

            newTriple->SetNmp(var);

            if (!tmpPolynom->IsZero())
            {
                set.push_back(new Triple(tmpPolynom
                                        ,newTriple->GetAnc()
                                        ,newTriple->GetNmp()
                                        ,newTriple
                                        ,var
#ifdef USE_REAL_MINSTRATEGY
                                        ,hiddenDegree
#endif
                                        )
                             );
            }
            delete tmpPolynom;
        }
    }
}


Triple* QSET::Get()
{
    Triple* result = tripleList.back();
    tripleList.pop_back();
    return result;
}

void QSET::DeleteDescendants(const Triple* ancestor)
{
    list<Triple*>::iterator it(tripleList.begin());
    while ( it != tripleList.end() )
    {
        if ((**it).GetAnc() == ancestor || (**it).GetWAnc() == ancestor)
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
