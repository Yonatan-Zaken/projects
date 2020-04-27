/*******************************
    Yonatan Zaken
    Bitset
    HPP
    27/04/20
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_BITSET_HPP
#define ILRD_RD8081_BITSET_HPP

#include <string>       // std::string 
#include <cstddef>      // std::size_t
#include <iostream>     // ostream
#include <algorithm>    // algorithm

#include "utility.hpp"         // noexcept
//#include "bitset_functors.hpp" // functors

#define NUM_OF_BITS(N) ((N / ((sizeof(unsigned char) * BITS_IN_BYTE))) + 1)

namespace ilrd
{

template<std::size_t N>
class BitSet
{
public:
    explicit BitSet();
    explicit BitSet(const std::string &bit_set);
    //~BitSet()
    //BitSet(const Bitset &other)
    //BitSet& operator=(const Bitset &rhs)

    std::size_t CountOn() const noexcept;
    std::size_t CountOff() const noexcept;
    std::string ToString() const noexcept;
    bool Get(std::size_t pos) const;

    BitSet& SetAll() noexcept;
    BitSet& Set(std::size_t pos) noexcept;
    BitSet& ResetAll() noexcept;
    BitSet& Reset (std::size_t pos) noexcept;
    BitSet& FlipAll() noexcept;
    BitSet& Flip(std::size_t pos) noexcept;
    BitSet& SetVal(std::size_t pos, bool value);

    BitSet operator~() const noexcept;
    BitSet operator<<(std::size_t shift_by) const noexcept;
    BitSet operator>>(std::size_t shift_by) const noexcept;

    BitSet& operator&=(const BitSet& rhs) noexcept;
    BitSet& operator|=(const BitSet& rhs) noexcept;
    BitSet& operator^=(const BitSet& rhs) noexcept;
    BitSet& operator<<=(std::size_t shift_by) noexcept;
    BitSet& operator>>=(std::size_t shift_by) noexcept;

    bool IsOn(std::size_t pos) const noexcept;
    bool IsOff(std::size_t pos) const noexcept;
    bool operator==(const BitSet& rhs) const noexcept;
    bool operator!=(const BitSet& rhs) const noexcept;
    bool operator[](std::size_t pos) const noexcept; 
    //RFProxy operator[](std::size_t pos) noexcept;

    const BitSet operator|(const BitSet &rhs) const;
    const BitSet operator&(const BitSet &rhs) const;
    const BitSet operator^(const BitSet &rhs) const;

private:
    byte_t m_bits[NUM_OF_BITS(N)];
    std::size_t m_num_of_bytes;
};

template<std::size_t N>
std::ostream& operator<<(std::ostream &out, const BitSet<N> &bit);

/************************************ Masks ***********************************/

const unsigned char mask1 = 0x55;
const unsigned char mask3 = 0x33;
const unsigned char mask5 = 0x0f;

/******************************* Bitset Functors ******************************/

template <std::size_t N>
struct XorFunctor
{
public:
    XorFunctor(const BitSet<N>& rhs): m_rhs(rhs), m_index(0)
    {}

    void operator()(byte_t& i)
    {
        i ^= m_rhs[m_index++];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

/******************************************************************************/

template <std::size_t N>
struct AndFunctor
{
public:
    AndFunctor(const BitSet<N>& rhs): m_rhs(rhs), m_index(0)
    {}

    void operator()(byte_t& i)
    {
        i &= m_rhs[m_index++];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

/******************************************************************************/

template <std::size_t N>
struct OrFunctor
{
public:
    OrFunctor(const BitSet<N>& rhs): m_rhs(rhs), m_index(0)
    {}

    void operator()(byte_t& i)
    {
        i |= m_rhs[m_index++];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

/******************************************************************************/

template <std::size_t N>
struct CountFunctor
{
public:
    CountFunctor(): m_counter(0), m_sum(0)
    {}

    void operator()(byte_t& i)
    {
        m_counter = (i & mask1) + ((i >> 1) & mask1);
        m_counter = (m_counter & mask3) + ((m_counter >> 2) & mask3);
        m_counter = (m_counter & mask5) + ((m_counter >> 4) & mask5);
        m_sum += m_counter;
    }

    std::size_t GetCount() const
    {
        return m_sum;
    }

private:
    std::size_t m_counter;
    std::size_t m_sum;
};

/************************* Bitset template definitions ************************/

template <std::size_t N>
BitSet<N>::BitSet():
    m_bits(),
    m_num_of_bytes(NUM_OF_BITS(N))
{
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>::BitSet(const std::string &bit_set):
    m_bits(),
    m_num_of_bytes(NUM_OF_BITS(N))
{

}

/******************************************************************************/

template <std::size_t N>
std::size_t BitSet<N>::CountOn() const noexcept
{
    CountFunctor<N> f();
    CountFunctor<N> count = std::for_each(m_bits, m_bits + (m_num_of_bytes - 1), f);
    return count.GetCount();    
}

/******************************************************************************/

template <std::size_t N>
std::size_t BitSet<N>::CountOff() const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
std::string BitSet<N>::ToString() const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::Get(std::size_t pos) const
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::SetAll() noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::Set(std::size_t pos) noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::ResetAll() noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::Reset(std::size_t pos) noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::FlipAll() noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::Flip(std::size_t pos) noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::SetVal(std::size_t pos, bool value)
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N> BitSet<N>::operator~() const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N> BitSet<N>::operator<<(std::size_t shift_by) const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N> BitSet<N>::operator>>(std::size_t shift_by) const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator&=(const BitSet& rhs) noexcept
{
    AndFunctor<N> f1(&rhs);
    std::for_each(m_bits, m_bits + (m_num_of_bytes - 1), f1);
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator|=(const BitSet& rhs) noexcept
{
    OrFunctor<N> f1(&rhs);
    std::for_each(m_bits, m_bits + (m_num_of_bytes - 1), f1);
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator^=(const BitSet& rhs) noexcept
{
    OrFunctor<N> f1(&rhs);
    std::for_each(m_bits, m_bits + (m_num_of_bytes - 1), f1);
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator<<=(std::size_t shift_by) noexcept
{

}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator>>=(std::size_t shift_by) noexcept
{

}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::IsOn(std::size_t pos) const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::IsOff(std::size_t pos) const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::operator==(const BitSet& rhs) const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::operator!=(const BitSet& rhs) const noexcept
{

}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::operator[](std::size_t pos) const noexcept
{
    
}

/******************************************************************************/

//RFProxy operator[](std::size_t pos) noexcept;

/******************************************************************************/

template <std::size_t N>
const BitSet<N> BitSet<N>::operator|(const BitSet &rhs) const
{

}

/******************************************************************************/

template <std::size_t N>
const BitSet<N> BitSet<N>::operator&(const BitSet &rhs) const
{

}

/******************************************************************************/

template <std::size_t N>
const BitSet<N> BitSet<N>::operator^(const BitSet &rhs) const
{

}

/******************************************************************************/


}//ilrd

#endif //ILRD_RD8081_BITSET_HPP
