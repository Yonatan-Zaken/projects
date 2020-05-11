/*******************************
    Yonatan Zaken
    FDListner
    CPP
    ILRD - RD8081               
*******************************/

#include "utility.hpp"
#include "fdlistner.hpp"
using namespace ilrd;

int main()
{
    std::vector<FDListener::key_t> vector;
    vector.push_back(FDListener::key_t(1, FDListener::READ));
    vector.push_back(FDListener::key_t(3, FDListener::READ));
    vector.push_back(FDListener::key_t(5, FDListener::WRITE));
    vector.push_back(FDListener::key_t(8, FDListener::WRITE));

    FDListener::Monitor(vector);

	return 0;
}
