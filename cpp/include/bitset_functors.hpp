/*******************************
    Yonatan Zaken
    Bitset Functors
    HPP
    27/04/20
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_BITSET_FUNCTORS_HPP
#define ILRD_RD8081_BITSET_FUNCTORS_HPP

#include <string>       // std::string 
#include <cstddef>      // std::size_t
#include <iostream>     // ostream

#include "utility.hpp"  // noexcept
#include "bitset.hpp"

namespace ilrd
{

template <std::size_t N>
struct XorAssignment
{
public:
    XorAssignment(const BitSet<N>& rhs): m_rhs(rhs), m_index(0)
    {
    }

    void operator()(byte_t& i)
    {
        i ^= m_rhs[m_index];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

}// namespace ilrd

#endif //ILRD_RD8081_BITSET_FUNCTORS_HPP
