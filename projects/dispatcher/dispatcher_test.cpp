#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include "dispatcher.hpp"
#include "tests.hpp"

using namespace ilrd;
using namespace std;

/******************************************************************************/

int globalVar = 0;
int indic = 0;

void UpFunc(int)
{
    ++globalVar;
}

void DownFunc()
{
    --globalVar;
}

/******************************************************************************/

void Indicator()
{
    indic = 1;
    --globalVar;
}

void RemoveFrom(Dispatcher<ObserverBase<int>, int> *, Observer<int> *o)
{
    delete o;
    ++globalVar;
}

void InsertTo(Dispatcher<ObserverBase<int>, int> *d, Observer<int> **arr)
{
    static int i = 0;
    if(!i)
    {
        Observer<int> *o1 = new Observer<int>(d, UpFunc, DownFunc);
        Observer<int> *o2 = new Observer<int>(d, UpFunc, DownFunc);
        Observer<int> *o3 = new Observer<int>(d, UpFunc, DownFunc);
        Observer<int> *o4 = new Observer<int>(d, UpFunc, DownFunc);
        Observer<int> *o5 = new Observer<int>(d, UpFunc, DownFunc);
        Observer<int> *o6 = new Observer<int>(d, UpFunc, DownFunc);

        arr[0] = o1; 
        arr[1] = o2; 
        arr[2] = o3; 
        arr[3] = o4; 
        arr[4] = o5; 
        arr[5] = o6; 
    }
    ++i;

    ++globalVar;
}

/******************************************************************************/

void basicTest1();
void basicTest2();
void basicTest3();

int main()
{
    basicTest1();
    cerr << "\n\n";
    basicTest2();
    cerr << "\n\n";
    basicTest3();

    return 0;
}

/******************************************************************************/

void basicTest1()
{
    indic = 0;
    globalVar = 0;
    {
        Dispatcher<ObserverBase<int>, int> *d1 = new Dispatcher<ObserverBase<int>, int>;
        Observer<int> o1(d1, UpFunc, DownFunc);
        Observer<int> o2(d1, UpFunc, DownFunc);
        Observer<int> o3(d1, UpFunc, DownFunc);
        Observer<int> o4(d1, UpFunc, DownFunc);
        Observer<int> o5(d1, UpFunc, DownFunc);
        Observer<int> o6(d1, UpFunc, DownFunc);

        d1->Broadcast(3);

        TestInt("Testing Basics Update", 6, globalVar);
        delete d1;
    }

    TestInt("Testing Basics UpdateDead", 0, globalVar);   
}

/******************************************************************************/

void basicTest2()
{
    indic = 0;
    globalVar = 0;
    {
        Dispatcher<ObserverBase<int>, int> *d1 = new Dispatcher<ObserverBase<int>, int>;
        Observer<int> o1(d1, UpFunc, DownFunc);
        Observer<int> *o2 = new Observer<int>(d1, UpFunc, Indicator);
        Observer<int> o3(d1, boost::bind(RemoveFrom, d1, o2), DownFunc);
        Observer<int> o4(d1, UpFunc, DownFunc);
        Observer<int> o5(d1, UpFunc, DownFunc);
        Observer<int> o6(d1, UpFunc, DownFunc);

        d1->Broadcast(3);

        TestInt("Testing Basics Update", 6, globalVar);
        TestInt("Testing UnSub from function", 0, indic);
        delete d1;
    }

    TestInt("Testing Basics UpdateDead", 1, globalVar);
}

/******************************************************************************/

void basicTest3()
{
    indic = 0;
    globalVar = 0;

    Observer<int> *arr[6];
    {
        Dispatcher<ObserverBase<int>, int> *d1 = new Dispatcher<ObserverBase<int>, int>;
        Observer<int> o1(d1, UpFunc, DownFunc);
        Observer<int> o2(d1, UpFunc , DownFunc);
        Observer<int> o3(d1, boost::bind(InsertTo, d1, arr), DownFunc);
        Observer<int> o4(d1, UpFunc, DownFunc);
        Observer<int> o5(d1, UpFunc, DownFunc);
        Observer<int> o6(d1, UpFunc, DownFunc);

        d1->Broadcast(3);
        TestInt("Testing Basics Update", 6, globalVar);
        d1->Broadcast(3);
        TestInt("Testing Basics Update", 18, globalVar);

        delete d1;
        for(int i = 0; i < 6; ++i)
        {
            delete arr[i];
        }
    }

    TestInt("Testing Basics UpdateDead", 6, globalVar);
}






