#include <iostream> // cout

#include "simplestring.hpp"

using namespace ilrd;

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

String foo(String s_)
{
    String s2(s_);
    return s2;
}

static void Test()
{
    String str1 = "123";
    String str2;
    str2 = foo(str1);
}

int main()
{
    Test();
    String s1("hello");
    String s2(s1);
    String s3("QQQQQQ");
    String s4("hi");
    String s5();
    std::cout << s1 << std::endl; 
    std::cout << s3 << std::endl;
    
    std::cout << (s1 == s2) << "\n";
    std::cout << (s1 == s3) << "\n";
    
    std::cout << (s1 > s4) << "\n";
    std::cout << (s4 < s1) << "\n";
    
    std::cout << s1.Cstr() << "\n";
    std::cout << s2.Cstr() << "\n";
    std::cout << s1.Length() << "\n";
    std::cout << s2.Length() << "\n";
    
    return 0;
}
