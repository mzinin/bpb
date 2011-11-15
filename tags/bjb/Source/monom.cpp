#include "monom.h"
#include <sstream>

FastAllocator Monom::VarsListNode::Allocator(sizeof(Monom::VarsListNode));
FastAllocator Monom::Allocator(sizeof(Monom));
Monom::Integer Monom::DimIndepend(0);
Variables* const Monom::IndependVariables(new Variables());


Monom::Monom(const std::string& str)
    : ListHead(0)
    , TotalDegree(0)
    , Next(0)
{
    std::stringstream tmpStream(str); 
    tmpStream >> *this;
}

std::string Monom::ToString() const
{
    std::stringstream tmpStream; 
    tmpStream << *this;
    return tmpStream.str();
}

void Monom::AddVariable(const char* var)
{
    if (IndependVariables->Add(var))
    {
        ++DimIndepend;
    }
}

const char* Monom::GetVariable(Monom::Integer var)
{
    return IndependVariables->Variable(var);
}

bool Monom::IsDivisibleBy(const Monom& anotherMonom) const
{
    VarsListNode *iterator = ListHead,
                 *anotherIterator = anotherMonom.ListHead;
    while (iterator && anotherIterator)
    {
        if (iterator->Variable == anotherIterator->Variable)
        {
            if (iterator->Degree < anotherIterator->Degree)
            {
                break;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        else if (iterator->Variable > anotherIterator->Variable)
        {
            iterator = iterator->Next;
        }
        else
        {
            break;
        }
    }

    return !anotherIterator;
}

bool Monom::IsTrueDivisibleBy(const Monom& anotherMonom) const 
{
    if (TotalDegree <= anotherMonom.TotalDegree)
    {
        return false;
    }

    VarsListNode *iterator = ListHead,
                 *anotherIterator = anotherMonom.ListHead;
    while (iterator && anotherIterator)
    {
        if (iterator->Variable == anotherIterator->Variable)
        {
            if (iterator->Degree < anotherIterator->Degree)
            {
                break;
            }
            iterator = iterator->Next;
            anotherIterator = anotherIterator->Next;
        }
        else if (iterator->Variable > anotherIterator->Variable)
        {
            iterator = iterator->Next;
        }
        else
        {
            break;
        }
    }

    return !anotherIterator;
}

Monom::Integer Monom::GcdDegree(const Monom& monomA, const Monom& monomB)
{
    Integer result = 0;
    VarsListNode *iteratorA(monomA.ListHead),
                 *iteratorB(monomB.ListHead);
    while (iteratorA && iteratorB)
    {
        if (iteratorA->Variable == iteratorB->Variable)
        {
            result += std::min(iteratorA->Degree, iteratorB->Degree);
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else if (iteratorA->Variable > iteratorB->Variable)
        {
            iteratorA = iteratorA->Next;
        }
        else
        {
            iteratorB = iteratorB->Next;
        }
    }
    return result;
}

Monom::Integer Monom::LcmDegree(const Monom& monomA, const Monom& monomB)
{
    Integer result = 0;
    VarsListNode *iteratorA(monomA.ListHead),
                 *iteratorB(monomB.ListHead);
    while (iteratorA && iteratorB)
    {
        if (iteratorA->Variable == iteratorB->Variable)
        {
            result += std::max(iteratorA->Degree, iteratorB->Degree);
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else if (iteratorA->Variable > iteratorB->Variable)
        {
            result += iteratorA->Degree;
            iteratorA = iteratorA->Next;
        }
        else
        {
            result += iteratorB->Degree;
            iteratorB = iteratorB->Next;
        }
    }
    
    while (iteratorA)
    {
        result += iteratorA->Degree;
        iteratorA = iteratorA->Next;
    }
    
    while (iteratorB)
    {
        result += iteratorB->Degree;
        iteratorB = iteratorB->Next;
    }
    return result;
}

void Monom::SetGcdOf(const Monom& monomA, const Monom& monomB)
{
    SetOne();
    VarsListNode **iterator = &ListHead,
                 *iteratorA(monomA.ListHead),
                 *iteratorB(monomB.ListHead);
    while (iteratorA && iteratorB)
    {
        if (iteratorA->Variable == iteratorB->Variable)
        {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorA->Variable;
            (*iterator)->Degree = std::min(iteratorA->Degree, iteratorB->Degree);
            TotalDegree += (*iterator)->Degree;

            iterator = &((*iterator)->Next);
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else if (iteratorA->Variable > iteratorB->Variable)
        {
            iteratorA = iteratorA->Next;
        }
        else
        {
            iteratorB = iteratorB->Next;
        }
    }
}

void Monom::SetLcmOf(const Monom& monomA, const Monom& monomB)
{
    SetOne();
    VarsListNode **iterator = &ListHead,
                 *iteratorA(monomA.ListHead),
                 *iteratorB(monomB.ListHead);
    while (iteratorA && iteratorB)
    {
        if (iteratorA->Variable == iteratorB->Variable)
        {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorA->Variable;
            (*iterator)->Degree = std::max(iteratorA->Degree, iteratorB->Degree);
            TotalDegree += (*iterator)->Degree;

            iterator = &((*iterator)->Next);
            iteratorA = iteratorA->Next;
            iteratorB = iteratorB->Next;
        }
        else if (iteratorA->Variable > iteratorB->Variable)
        {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorA->Variable;
            (*iterator)->Degree = iteratorA->Degree;
            TotalDegree += (*iterator)->Degree;

            iterator = &((*iterator)->Next);
            iteratorA = iteratorA->Next;
        }
        else
        {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorB->Variable;
            (*iterator)->Degree = iteratorB->Degree;
            TotalDegree += (*iterator)->Degree;

            iterator = &((*iterator)->Next);
            iteratorB = iteratorB->Next;
        }
    }
    
    while (iteratorA)
    {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorA->Variable;
            (*iterator)->Degree = iteratorA->Degree;
            TotalDegree += (*iterator)->Degree;

            iterator = &((*iterator)->Next);
            iteratorA = iteratorA->Next;
    }
    
    while (iteratorB)
    {
            *iterator = new VarsListNode();
            (*iterator)->Variable = iteratorB->Variable;
            (*iterator)->Degree = iteratorB->Degree;
            TotalDegree += (*iterator)->Degree;

            iterator = &((*iterator)->Next);
            iteratorB = iteratorB->Next;
    }
}

std::istream& operator>>(std::istream& in, Monom& monom) 
{
    std::streampos posbeg = in.tellg();
    int var = monom.IndependVariables->Read(in);
    if (var < 0) 
    {
        in.clear();
        in.setstate(std::ios::failbit);
    }
    else 
    {
        monom.SetOne();
        int degree;
        do 
        {
            degree = 1;
            std::streampos posbeg = in.tellg();
            if ((in >> std::ws).peek() == '^') 
            {
                in.get();
                in >> std::ws >> degree;
                if (in.fail() || degree < 0) 
                {
                    in.setstate(std::ios::failbit);
                }
            }
            monom.Prolong(var, degree);
            posbeg = in.tellg();
            if (in.peek() != '*')
            {
                var = -1;
            }
            else 
            {
                in.get();
                var = monom.IndependVariables->Read(in);
                if (var < 0) 
                {
                    in.clear();
                    in.seekg(posbeg);
                }
            }
        } while(var >= 0);
        if (in.eof() && degree >= 0)
        {
            in.clear();
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Monom& monom) 
{
    if (!monom.Degree())
    {
        out << '1';
    }
    else 
    {
        int i = 0;
        Variables::ConstIterator j(monom.IndependVariables->Begin());
        while(monom[i] == 0) 
        {
            ++i;
            ++j;
        }
        out << *j;
        if (monom[i] > 1)
        {
            out << '^' << monom[i];
        }
        ++i;
        ++j;
        while(j != monom.IndependVariables->End())
        {
            if (monom[i]) 
            {
                out << '*' << *j;
                if (monom[i] > 1)
                {
                    out << '^' << monom[i];
                }
            }
            ++i;
            ++j;
        }
    }
    return out;
}