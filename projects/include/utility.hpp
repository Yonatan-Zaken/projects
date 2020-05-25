#ifndef ILRD_RD8081_UTILITY_HPP
#define ILRD_RD8081_UTILITY_HPP

#if __cplusplus<201104 
#define noexcept throw()
#define nullptr NULL  
#endif

// other
#define UNUSED(x) (void)(x)
#define ASCII_SIZE 256
#define SUCCESS 0
#define FAIL 1

// return min of two numbers
#ifndef MIN
#define MIN( n1, n2 )   ((n1) > (n2) ? (n2) : (n1))
#endif

// return max of two numbers 
#ifndef MAX
#define MAX( n1, n2 )   ((n1) > (n2) ? (n1) : (n2))
#endif

// Aligns the supplied size to the specified PowerOfTwo
#define ALIGN_SIZE( size_to_align, power_of_two )\
    (((size_to_align) + (power_of_two) - 1) & ~((power_of_two) - 1))

// Implementation of Uncopyable class  
// disable copy/assignment constructors
namespace ilrd
{

class Uncopyable
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}
    
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

} // namespace ilrd

#include <inttypes.h>

namespace ilrd
{

namespace details
{
    static const uint64_t BLOCK_SIZE = 4096;

    static const uint8_t REPLY_READ_METADATA_SIZE = 2 * sizeof(uint8_t) + sizeof(uint64_t);

    static const uint8_t REPLY_WRITE_METADATA_SIZE = REPLY_READ_METADATA_SIZE;

    static const uint8_t REQUEST_METADATA_SIZE = sizeof(uint8_t) + 2 * sizeof(uint64_t);
    
    static const uint64_t REPLY_READ_SIZE = BLOCK_SIZE + REPLY_READ_METADATA_SIZE;
    
    static const uint64_t REPLY_WRITE_SIZE = REPLY_READ_METADATA_SIZE;

    static const uint64_t RECV_BLOCK_SIZE = BLOCK_SIZE + REQUEST_METADATA_SIZE;

    static const uint8_t OPERATION_TYPE_OFFSET = 0;
    static const uint8_t REQUEST_ID_OFFSET = 1;
    static const uint8_t BLOCK_ID_OFFSET = 9;
    static const uint8_t ERROR_CODE_OFFSET = 9;
    static const uint8_t READ_DATA_BLOCK_OFFSET = 10;
    static const uint8_t WRITE_DATA_BLOCK_OFFSET = 17;
    

} // namespace details

} // namespace ilrd
/*
// automation macros for tests 
#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS: [%s]\n", error_message);\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL: [%s]\n", error_message);\
        printf(NORMAL);\
    }\
}
*/
#endif // ILRD_RD8081_UTILITY_HPP

