#include <cstdio>
#include <cmath>
#include <iostream>
#include <ctime>

#include "complex.hpp"

using namespace ilrd;

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS %s\n", error_message);\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

static void ComplxTestCtor()
{
    printf("Complx Test Ctor:\n");
    Complex c1();
    Complex c2(0);
    Complex c3(2.5);
    Complex c4(100.23, 555.22);
    
    RUN_TEST(c2.GetReal() == 0, "test ctor1");
    RUN_TEST(c2.GetImag() == 0, "test ctor1");
    RUN_TEST(c3.GetReal() == 2.5, "test ctor2");
    RUN_TEST(c3.GetImag() == 0, "test ctor2");
    RUN_TEST(c4.GetReal() == 100.23, "test ctor3");
    RUN_TEST(c4.GetImag() == 555.22, "test ctor3");
    
    printf("\n");
}    

static void ComplxTestMemberFuncs()
{
    printf("Complx Test Member Funcs:\n");
    Complex c1(0);
    Complex c2(0);
    
    c1.SetReal(55.2);
    c1.SetImag(200);
    c2.SetReal(-1);
    c2.SetImag(-5000.2);
    
    RUN_TEST(c1.GetReal() == 55.2, "test GetReal");
    RUN_TEST(c1.GetImag() == 200, "test GetImag");
    RUN_TEST(c2.GetReal() == -1, "test GetReal");
    RUN_TEST(c2.GetImag() == -5000.2, "test GetImag");
    
    RUN_TEST(c1.Abs() == sqrt(pow(55.2,2) + pow(200,2)), "test Abs");
    RUN_TEST(c2.Abs() == sqrt(pow(-1,2) + pow(-5000.2,2)), "test Abs");
    
    Complex c3 = c2.Conj();
    RUN_TEST(c3.GetImag() == -c2.GetImag(), "test Conj");
    
    printf("\n");
}

static void ComplxTestOperators()
{
    printf("Complx Test Member Funcs:\n"); 
    Complex c1(0);
    Complex c2(0);
    
    c1.SetReal(55.2); c1.SetImag(200);
    c2.SetReal(20); c2.SetImag(-5000.2);    
    Complex c3 = c1 + c2;

    c1.SetReal(3); c1.SetImag(2);
    c2.SetReal(2); c2.SetImag(-1);
    c3 = c1 * c2;
    c3 = 2 * c1;
    c3 = 5 * 2;
    
    c1.SetReal(20); c1.SetImag(-4);
    c2.SetReal(3); c2.SetImag(2);
    c3 = c1 / c2;
    
    c1 += 2;
    c3 -= c1;
    c2 *= c1;

    std::cout << c1;
    std::cin >> c1 >> c2;
    std::cout << c1;
    std::cout << c2;
    Complex c4(2,3);
    Complex c5(3,0);
    c5 = c5.Conj();
    c1 = c4 / c5;
    
    printf("\n"); 
}

static void BenchmarkTest()
{
    Complex c1(2,4);
    Complex c2(22.12,4.3);
    Complex c3(2.1,4.2);
    
    clock_t begin = 0, end = 0;
    begin = clock();
    
    for (float i = 0; i < 10000000; ++i)
    {
        Complex c2(i,i);
        Complex c3(i,i);
        c1 = c2 + c3;
    }
    
    end = clock();
    printf("By Value: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

int main()
{
    ComplxTestCtor();
    ComplxTestMemberFuncs();
    ComplxTestOperators();
    BenchmarkTest();
	return 0;
}
