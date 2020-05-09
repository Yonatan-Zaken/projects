/*******************************
    Yonatan Zaken
    FDListner
    CPP
    ILRD - RD8081               
*******************************/

#include <algorithm>
#include <cstddef>
#include <cstdio>

#include "fdlistner.hpp"

namespace ilrd
{

struct CompareFunctor
{
    bool cmp(const FDListener::pair_t &a, const FDListener::pair_t &b)
    {
        return (a.first < b.first);
    }
};

FDListener::vector_t FDListener::Monitor(const FDListener::vector_t &vector)
{
    fd_set read_master = {0};
    fd_set read_fds = {0};
    
    fd_set write_master = {0};
    fd_set write_fds = {0};
    
    fd_set except_master = {0};
    fd_set except_fds = {0};
    
    FD_ZERO(&read_master);
    FD_ZERO(&write_master);
    FD_ZERO(&except_master); 
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_ZERO(&except_fds);   
    
    int fdmax = 0; 
    std::max_element(vector.begin(), vector.end(), CompareFunctor());
    
    if (-1 == select(fdmax+1, &read_fds, &write_fds, &except_fds, NULL)) 
    {
        perror("select");
        
    }

    for(int i = 0; i <= fdmax; ++i) 
    {
        
        if (FD_ISSET(i, &read_fds)) 
        { 

        }

        if (FD_ISSET(i, &write_fds)) 
        { 

        }  

        if (FD_ISSET(i, &read_fds)) 
        { 

        } 
    }
}

void FDListener::InitSets()
{

}

} // namespace ilrd
