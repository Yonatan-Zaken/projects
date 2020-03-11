#include <iostream> // cout

#include "simple_string.hpp"

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

int main()
{

    String s1("hello");
    String s2(s1);
    String s3("QQQQQQ");
    String s4("hi");
    
    std::cout << s1 << std::endl; 
    std::cout << s3 << std::endl;
    
    std::cout << (s1 == s2) << "\n";
    std::cout << (s1 == s3) << "\n";
    
    std::cout << (s1 > s4) << "\n";
    std::cout << (s4 < s1) << "\n";
    
    s1.Cstr();
    s2.Cstr();
    std::cout << s1.Length() << "\n";
    std::cout << s2.Length() << "\n";
    
    return 0;
}
