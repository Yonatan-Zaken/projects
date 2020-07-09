#include <stdio.h> // cout
#include <string.h>
#include <iostream>

#include "rcstring.hpp"
/*
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
*/
using namespace ilrd;

static void CtorTest()
{
    printf("Ctors Test: \n");
    
    RCString s1("hello");
    RCString s2("AAKKQQJJ");
    RCString s3(s2);
    RCString s4("abc");
    s4 = s1;
    
    RUN_TEST(0 == strcmp("hello", s1.GetCStr()), "default ctor");
    RUN_TEST(0 == strcmp("AAKKQQJJ", s2.GetCStr()), "default ctor");
    RUN_TEST(0 == strcmp(s3.GetCStr(), s2.GetCStr()), "cctor");
    RUN_TEST(0 == strcmp(s4.GetCStr(), s1.GetCStr()), "assignment ctor");
    
    RCString s5(s4);
    RCString s6(s5);
    
    RUN_TEST(0 == strcmp(s4.GetCStr(), s5.GetCStr()), "cctor");
    RUN_TEST(0 == strcmp(s5.GetCStr(), s6.GetCStr()), "cctor");
    
    RCString s7;
    RUN_TEST(0 == strcmp("", s7.GetCStr()), "default ctor");
    
    s1 = s1;
    RUN_TEST(0 == strcmp("hello", s1.GetCStr()), "self assignment");
    
    printf("\n");
}

static void OperatorTest()
{
    printf("Operator Test: \n");
    
    RCString s1("hello");
    RCString s2("AAKKQQJJ");
    
    s2 += s1;
    s1 += s2;
    
    RUN_TEST(0 == strcmp("AAKKQQJJhello", s2.GetCStr()), "compound +=");
    RUN_TEST(0 == strcmp("helloAAKKQQJJhello", s1.GetCStr()), "compound +=");
    
    RCString s3("<<<<");
    RCString s4(">>>>");
    RCString s5("");
    
    s5 = s3 + s4;
    RUN_TEST(0 == strcmp("<<<<>>>>", s5.GetCStr()), "operator +");
    
    s5[0] = 'Q';
    RUN_TEST('Q' == s5[0], "operator []");
    s5[4] = 'T';
    RUN_TEST('T' == s5[4], "operator []");
    
    const RCString s6(s5);
    
    RUN_TEST('T' == s6[4], "operator []");
    RUN_TEST('<' == s6[1], "operator []");
    
    RCString s7("");
    RCString s8("a");
    
    RUN_TEST(s3 == s3, "operator ==");
    RUN_TEST(s3 != s4, "operator !=");
    RUN_TEST(s7 < s8, "operator <"); 

    RCString s9 = "abc";
    RCString s10("abb");
    
    RUN_TEST(s9 > s10, "operator >");
    
    std::cout << s6 << "\n";
    std::cout << s6 << s10 << "\n";
    
    RCString s11 = "QQQQQQ";
    printf("Enter string: ");
    std::cin >> s11 >> s8;
    std::cout << s11 << "\n";
    std::cout << s8 << "\n";
    
    printf("\n");
}

static void ProxyTest()
{
    printf("Proxy Test: \n");
    
    RCString s1("hello");
    RCString s2("AAKKQQJJ");  
    RCString s3(s2);
    RCString s4(s3);
    
//    char& c = s1[3]; error: cannot bind non-const lvalue reference of type ‘char&’ to an rvalue of type ‘char’

    std::cout << s1[2] << "\n"; 
    s2[0] = 'u';   
    std::cout << s2 << "\n";
    printf("\n");  
}

int main()
{
    CtorTest();
    OperatorTest();
    ProxyTest();
	return 0;
}
