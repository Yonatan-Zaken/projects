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
#include <string>       // string
#include <cstring>      // memcpy

#include "utility.hpp"         // noexcept

#define NUM_OF_BYTES(N) ((N / ((sizeof(unsigned char) * BITS_IN_BYTE))) + 1)

namespace ilrd
{

const std::size_t BITS_IN_BYTE = 8;

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
    byte_t m_bits[NUM_OF_BYTES(N)];
    std::size_t m_num_of_bytes;
    void SetLastByte(std::size_t pos);
};

template<std::size_t N>
std::ostream& operator<<(std::ostream &out, const BitSet<N> &bit);

/************************************ Masks ***********************************/

const unsigned char MASK_01 = 0x01;
const unsigned char MASK_55 = 0x55;
const unsigned char MASK_33 = 0x33;
const unsigned char MASK_0f = 0x0f;
const unsigned char ASCII_ZERO = 48;

/***************************** Non member functions ***************************/

static inline std::size_t GetBitIndex(std::size_t pos)
{
    return (pos - 1) / BITS_IN_BYTE;
}

static inline std::size_t ShiftBy(std::size_t pos)
{
    return (pos - 1) % BITS_IN_BYTE;
}

static void CleanByte(byte_t& last_byte, std::size_t pos)
{
    std::size_t shift_by = (pos % BITS_IN_BYTE) % BITS_IN_BYTE; 
    last_byte = last_byte >> shift_by;
}

/******************************* Bitset Functors ******************************/

template <std::size_t N>
struct BitsetFunctor
{
public:
    explicit BitsetFunctor(BitSet<N>& bitset): 
        m_bitset(bitset),
        m_index(1)
    {}
    
    void operator()(const char& c)
    {
        m_bitset.SetVal(m_index, c - ASCII_ZERO);
        ++m_index;
    }

private:
    BitSet<N>& m_bitset;
    std::size_t m_index;
};

/******************************************************************************/

template <std::size_t N>
struct XorFunctor
{
public:
    explicit XorFunctor(const BitSet<N>& rhs): 
        m_rhs(rhs.m_bits), 
        m_index(0)
    {}

    void operator()(byte_t& byte)
    {
        byte ^= m_rhs[m_index++];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

/******************************************************************************/

template <std::size_t N>
struct XorAssignmentFunctor
{
public:
    explicit XorAssignmentFunctor(const BitSet<N>& rhs): 
        m_rhs(rhs.m_bits), 
        m_index(0)
    {}

    void operator()(byte_t& byte)
    {
        byte ^= m_rhs[m_index++];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

/******************************************************************************/

template <std::size_t N>
struct AndAssignmentFunctor
{
public:
    explicit AndAssignmentFunctor(const BitSet<N>& rhs): 
        m_rhs(rhs.m_bits), 
        m_index(0)
    {}

    void operator()(byte_t& byte)
    {
        byte &= m_rhs[m_index++];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

/******************************************************************************/

template <std::size_t N>
struct OrAssignmentFunctor
{
public:
    explicit OrAssignmentFunctor(const BitSet<N>& rhs):
        m_rhs(rhs.m_bits), 
        m_index(0)
    {}

    void operator()(byte_t& byte)
    {
        byte |= m_rhs[m_index++];
    }   

private:
    byte_t *m_rhs;
    std::size_t m_index;
};

/******************************************************************************/

struct CountFunctor
{
public:
    explicit CountFunctor() noexcept: m_counter(0), m_sum(0)
    {}

    void operator()(const byte_t& byte) noexcept
    {
        m_counter = (byte & MASK_55) + ((byte >> 1) & MASK_55);
        m_counter = (m_counter & MASK_33) + ((m_counter >> 2) & MASK_33);
        m_counter = (m_counter & MASK_0f) + ((m_counter >> 4) & MASK_0f);
        m_sum += m_counter;
    }

    std::size_t GetCount() const noexcept
    {
        return m_sum;
    }

private:
    std::size_t m_counter;
    std::size_t m_sum;
};

/******************************************************************************/

struct SetAllFunctor
{
public:
    void operator()(byte_t& byte)
    {
        byte ^= byte;
        byte = ~byte;
    }
};

/******************************************************************************/

struct ResetAllFunctor
{
public:
    void operator()(byte_t& byte)
    {
        byte ^= byte;
    }
};

/******************************************************************************/

struct FlipAllFunctor
{
public:
    void operator()(byte_t& byte)
    {
        byte = ~byte;
    }
};

/******************************************************************************/

bool BinaryPredicate (const byte_t& lhs, const byte_t& rhs) 
{
  return (lhs == rhs);
}

/************************* Bitset template definitions ************************/

template <std::size_t N>
BitSet<N>::BitSet():
    m_bits(),
    m_num_of_bytes(NUM_OF_BYTES(N))
{
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>::BitSet(const std::string &bit_set):
    m_bits(),
    m_num_of_bytes(NUM_OF_BYTES(N))
{
    if (N > bit_set.length())
    {
        // throw out_of_range
    }
    
    BitSet<N> new_set;
    std::for_each(bit_set.rbegin(), bit_set.rend(), BitsetFunctor<N>(new_set));
    memcpy(m_bits, new_set.m_bits, GetBitIndex(N) + 1);
}

/******************************************************************************/

template <std::size_t N>
std::size_t BitSet<N>::CountOn() const noexcept
{
    CountFunctor count = std::for_each(m_bits, m_bits + m_num_of_bytes , CountFunctor());

    return count.GetCount();    
}

/******************************************************************************/

template <std::size_t N>
std::size_t BitSet<N>::CountOff() const noexcept
{
    return (N - CountOn());
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
    if ((pos > N) || (pos < 0))
    {
        throw std::out_of_range("error Get. position out of range.");
    }
    
    return (*this)[pos];
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::SetAll() noexcept
{
    std::for_each(m_bits, m_bits + m_num_of_bytes, SetAllFunctor());
    CleanByte(m_bits[GetBitIndex(N)], N);

    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::Set(std::size_t pos) noexcept
{
    m_bits[GetBitIndex(pos)] |= (MASK_01 << ShiftBy(pos));
    
    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::ResetAll() noexcept
{
    std::for_each(m_bits, m_bits + m_num_of_bytes, ResetAllFunctor());
    
    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::Reset(std::size_t pos) noexcept
{
    m_bits[GetBitIndex(pos)] &= ~(MASK_01 << ShiftBy(pos));

    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::FlipAll() noexcept
{
    std::for_each(m_bits, m_bits + m_num_of_bytes, FlipAllFunctor());

    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::Flip(std::size_t pos) noexcept
{
    m_bits[GetBitIndex(pos)] ^= (MASK_01 << ShiftBy(pos));

    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::SetVal(std::size_t pos, bool value)
{
    if (1 == value)
    {
        Set(pos);
    }
    else
    {
        Reset(pos);
    }

    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N> BitSet<N>::operator~() const noexcept
{
    FlipAll();
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
    AndAssignmentFunctor<N> f1(rhs);
    std::for_each(m_bits, m_bits + m_num_of_bytes, f1);
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator|=(const BitSet& rhs) noexcept
{
    OrAssignmentFunctor<N> f1(rhs);
    std::for_each(m_bits, m_bits + m_num_of_bytes, f1);
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator^=(const BitSet& rhs) noexcept
{
    XorAssignmentFunctor<N> f1(rhs);
    std::for_each(m_bits, m_bits + m_num_of_bytes, f1);
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
    return (m_bits[GetBitIndex(pos)] & (MASK_01 << ShiftBy(pos)));
}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::IsOff(std::size_t pos) const noexcept
{
    return !IsOn(pos);
}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::operator==(const BitSet& rhs) const noexcept
{
    return std::equal(m_bits, m_bits + m_num_of_bytes, rhs.m_bits, BinaryPredicate);
}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::operator!=(const BitSet& rhs) const noexcept
{
    return !(m_bits == rhs.m_bits);
}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::operator[](std::size_t pos) const noexcept
{
    return (m_bits[GetBitIndex(pos)] & (MASK_01 << ShiftBy(pos)));
}

/******************************************************************************/

//RFProxy operator[](std::size_t pos) noexcept;

/******************************************************************************/

template <std::size_t N>
const BitSet<N> BitSet<N>::operator|(const BitSet &rhs) const
{
    BitSet<N> res = *this;
    
    return (res |= rhs);
}

/******************************************************************************/

template <std::size_t N>
const BitSet<N> BitSet<N>::operator&(const BitSet &rhs) const
{
    BitSet<N> res = *this;

    return (res &= rhs);
}

/******************************************************************************/

template <std::size_t N>
const BitSet<N> BitSet<N>::operator^(const BitSet &rhs) const
{
    BitSet<N> res = *this;

    return (res ^= rhs);
}

/******************************************************************************/


}//ilrd

#endif //ILRD_RD8081_BITSET_HPP
