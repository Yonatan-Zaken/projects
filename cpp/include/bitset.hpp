/*******************************
    Yonatan Zaken
    Bitset
    HPP
    27/04/20
    ILRD - RD8081               
*******************************/
// NOTES:
// - N must be positive integer value.
// - In BitSet(std::string) N must equal length of
// string and bigger than zero or else string exception 
// is thrown.
// - In operator[] if pos > N behaviour is undefined

#ifndef ILRD_RD8081_BITSET_HPP
#define ILRD_RD8081_BITSET_HPP

#include <string>       // std::string 
#include <cstddef>      // std::size_t
#include <sys/types.h>  // ssize_t
#include <iostream>     // ostream
#include <algorithm>    // algorithm

#include "utility.hpp"  // noexcept

const std::size_t BITS_IN_BYTE = 8;
#define NUM_OF_BYTES(N) (((N - 1) / ((sizeof(unsigned char) * BITS_IN_BYTE)))\
+ 1)

typedef unsigned char byte_t;

namespace ilrd
{

template<std::size_t N>
class BitSet
{
private: 
    class RFProxy;

public:
    class BitsIterator;
    class BitsConstIterator;

    explicit BitSet();
    explicit BitSet(const std::string &bit_set);
    //~BitSet() = default
    //BitSet(const Bitset &other) = default
    //BitSet& operator=(const Bitset &rhs) = default

    std::size_t CountOn() const noexcept;
    std::size_t CountOff() const noexcept;
    std::string ToString() const;
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
    RFProxy operator[](std::size_t pos) noexcept;

    const BitSet operator|(const BitSet &rhs) const;
    const BitSet operator&(const BitSet &rhs) const;
    const BitSet operator^(const BitSet &rhs) const;
    
    BitsIterator Begin();
    BitsIterator End();
    BitsConstIterator Begin() const;
    BitsConstIterator End() const;
    BitsConstIterator CBegin();
    BitsConstIterator CEnd();

    template <std::size_t U>
    friend struct AndAssignmentFunctor;
    template <std::size_t U>
    friend struct OrAssignmentFunctor;
    template <std::size_t U>
    friend struct XorAssignmentFunctor;

private:
    static const std::size_t m_num_of_bytes = NUM_OF_BYTES(N);
    byte_t m_bits[m_num_of_bytes];
    
    class RFProxy
    {
    public:
        RFProxy(BitSet& bitset, std::size_t pos);
        RFProxy& operator=(const RFProxy& other);
        RFProxy& operator=(bool bit);

        operator bool() const; 

    private:
        BitSet& m_prx_bitset;
        std::size_t m_prx_pos;
    };

public:

    class BitsIterator
    {
    public:
        BitsIterator(BitSet& bit_set, size_t pos);
        //BitsIterator(const BitsIterator &other) = default
        //BitsIterator& operator=(const BitsIterator &rhs) = default
        //~BitsIterator() = default
        
        typedef std::random_access_iterator_tag iterator_category;
        typedef RFProxy value_type;
        typedef ssize_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;

        BitsIterator& operator++();
        BitsIterator& operator--();
        const BitsIterator operator++(int);
        const BitsIterator operator--(int);
        BitsIterator& operator+=(std::size_t move_by);
        BitsIterator& operator-=(std::size_t move_by);

        const BitsIterator operator+(std::size_t inc_by);
        const BitsIterator operator-(std::size_t dec_by) const;
        difference_type operator-(const BitsIterator& iter);
        value_type operator[](std::size_t pos);
        value_type operator*();

        bool operator==(const BitsIterator &rhs);
        bool operator!=(const BitsIterator &rhs);
        bool operator<(const BitsIterator &rhs);
        bool operator>(const BitsIterator &rhs);
        bool operator<=(const BitsIterator &rhs);
        bool operator>=(const BitsIterator &rhs);
        
    private:
        BitSet& m_bit_set;
        std::size_t m_current_pos;
    };

    class BitsConstIterator
    {
    public:
        BitsConstIterator(const BitSet& bit_set, std::size_t pos);
        //BitsConstIterator(const BitsConstIterator &other) = default
        //BitsConstIterator& operator=(const BitsConstIterator &rhs) = default
        //~BitsConstIterator() = default
        
        typedef std::random_access_iterator_tag iterator_category;
        typedef bool value_type;
        typedef ssize_t difference_type;
        typedef const value_type* pointer;
        typedef const value_type& reference;

        BitsConstIterator& operator++();
        BitsConstIterator& operator--();
        const BitsConstIterator operator++(int);
        const BitsConstIterator operator--(int);
        BitsConstIterator& operator+=(std::size_t move_by);
        BitsConstIterator& operator-=(std::size_t move_by);

        const BitsConstIterator operator+(std::size_t inc_by);
        const BitsConstIterator operator-(std::size_t dec_by);
        difference_type operator-(const BitsConstIterator& iter);
        value_type operator[](std::size_t pos);
        value_type operator*();

        bool operator==(const BitsConstIterator &rhs);
        bool operator!=(const BitsConstIterator &rhs);
        bool operator<(const BitsConstIterator &rhs);
        bool operator>(const BitsConstIterator &rhs);
        bool operator<=(const BitsConstIterator &rhs);
        bool operator>=(const BitsConstIterator &rhs);

    private:
        const BitSet& m_bit_set;
        std::size_t m_current_pos;
    };

};

template<std::size_t N>
std::ostream& operator<<(std::ostream &out, const BitSet<N> &bit);

/******************************* Masks & Constants*****************************/

const byte_t MASK_01 = 0x01;
const byte_t MASK_55 = 0x55;
const byte_t MASK_33 = 0x33;
const byte_t MASK_0f = 0x0f;
const byte_t MASK_ff = 0xff;
const byte_t ASCII_ZERO = 48;
const std::string binary_lut[ASCII_SIZE] = 
{
    "00000000", "00000001", "00000010", "00000011", "00000100", "00000101",
    "00000110", "00000111", "00001000", "00001001", "00001010", "00001011",
    "00001100", "00001101", "00001110", "00001111", "00010000", "00010001",
    "00010010", "00010011", "00010100", "00010101", "00010110", "00010111",
    "00011000", "00011001", "00011010", "00011011", "00011100", "00011101",
    "00011110", "00011111", "00100000", "00100001", "00100010", "00100011",
    "00100100", "00100101", "00100110", "00100111", "00101000", "00101001",
    "00101010", "00101011", "00101100", "00101101", "00101110", "00101111",
    "00110000", "00110001", "00110010", "00110011", "00110100", "00110101",
    "00110110", "00110111", "00111000", "00111001", "00111010", "00111011",
    "00111100", "00111101", "00111110", "00111111", "01000000", "01000001",
    "01000010", "01000011", "01000100", "01000101", "01000110", "01000111",
    "01001000", "01001001", "01001010", "01001011", "01001100", "01001101",
    "01001110", "01001111", "01010000", "01010001", "01010010", "01010011",
    "01010100", "01010101", "01010110", "01010111", "01011000", "01011001",
    "01011010", "01011011", "01011100", "01011101", "01011110", "01011111",
    "01100000", "01100001", "01100010", "01100011", "01100100", "01100101",
    "01100110", "01100111", "01101000", "01101001", "01101010", "01101011",
    "01101100", "01101101", "01101110", "01101111", "01110000", "01110001",
    "01110010", "01110011", "01110100", "01110101", "01110110", "01110111",
    "01111000", "01111001", "01111010", "01111011", "01111100", "01111101",
    "01111110", "01111111", "10000000", "10000001", "10000010", "10000011",
    "10000100", "10000101", "10000110", "10000111", "10001000", "10001001",
    "10001010", "10001011", "10001100", "10001101", "10001110", "10001111",
    "10010000", "10010001", "10010010", "10010011", "10010100", "10010101",
    "10010110", "10010111", "10011000", "10011001", "10011010", "10011011",
    "10011100", "10011101", "10011110", "10011111", "10100000", "10100001",
    "10100010", "10100011", "10100100", "10100101", "10100110", "10100111",
    "10101000", "10101001", "10101010", "10101011", "10101100", "10101101",
    "10101110", "10101111", "10110000", "10110001", "10110010", "10110011",
    "10110100", "10110101", "10110110", "10110111", "10111000", "10111001",
    "10111010", "10111011", "10111100", "10111101", "10111110", "10111111",
    "11000000", "11000001", "11000010", "11000011", "11000100", "11000101",
    "11000110", "11000111", "11001000", "11001001", "11001010", "11001011",
    "11001100", "11001101", "11001110", "11001111", "11010000", "11010001",
    "11010010", "11010011", "11010100", "11010101", "11010110", "11010111",
    "11011000", "11011001", "11011010", "11011011", "11011100", "11011101",
    "11011110", "11011111", "11100000", "11100001", "11100010", "11100011",
    "11100100", "11100101", "11100110", "11100111", "11101000", "11101001",
    "11101010", "11101011", "11101100", "11101101", "11101110", "11101111",
    "11110000", "11110001", "11110010", "11110011", "11110100", "11110101",
    "11110110", "11110111", "11111000", "11111001", "11111010", "11111011",
    "11111100", "11111101", "11111110", "11111111"
};

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
    std::size_t shift_by = (BITS_IN_BYTE - pos % BITS_IN_BYTE) % BITS_IN_BYTE; 
    last_byte &= (MASK_ff >> shift_by);
}

/**************************** RFProxy definitions *****************************/

template <std::size_t N>
BitSet<N>::RFProxy::RFProxy(BitSet& bitset, std::size_t pos):
    m_prx_bitset(bitset),
    m_prx_pos(pos)
{
}

/******************************************************************************/

template <std::size_t N>
typename BitSet<N>::RFProxy& BitSet<N>::RFProxy::operator=(const RFProxy& other)
{
    *this = other.m_prx_bitset.Get(other.m_prx_pos); 

    return *this;
}

/******************************************************************************/

template <std::size_t N>
typename BitSet<N>::RFProxy& BitSet<N>::RFProxy::operator=(bool bit)
{
    m_prx_bitset.SetVal(m_prx_pos, bit);

    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>::RFProxy::operator bool() const
{
    return m_prx_bitset.Get(m_prx_pos);
}

/************************* Bitset template definitions ************************/

template <std::size_t N>
BitSet<N>::BitSet():
    m_bits()
{
}

/******************************************************************************/

template <std::size_t N>
struct BitFromStrFunctor
{
public:
    explicit BitFromStrFunctor(BitSet<N>& bitset): 
        m_bitset(bitset),
        m_index(1)
    {
    }

    void operator()(const char& c);

private:
    BitSet<N>& m_bitset;
    std::size_t m_index;
};

template <std::size_t N>
void BitFromStrFunctor<N>::operator()(const char& c)
{
        m_bitset.SetVal(m_index, ('1' == c));
        ++m_index;
}

template <std::size_t N>
BitSet<N>::BitSet(const std::string &bit_set):
    m_bits()
{   
    std::size_t found = bit_set.find_first_not_of("01");
    if (std::string::npos != found)
    {
        throw std::string("invalid string");
    }
    
    std::for_each(bit_set.rbegin(), bit_set.rend(), 
    BitFromStrFunctor<N>(*this));
}

/******************************************************************************/

struct CountFunctor
{
public:
    explicit CountFunctor() noexcept: m_counter(0), m_sum(0)
    {
    }

    void operator()(const byte_t& byte) noexcept;
    std::size_t GetCount() const noexcept;

private:
    std::size_t m_counter;
    std::size_t m_sum;
};

void CountFunctor::operator()(const byte_t& byte) noexcept
{
        m_counter = (byte & MASK_55) + ((byte >> 1) & MASK_55);
        m_counter = (m_counter & MASK_33) + ((m_counter >> 2) & MASK_33);
        m_counter = (m_counter & MASK_0f) + ((m_counter >> 4) & MASK_0f);
        m_sum += m_counter;    
}

std::size_t CountFunctor::GetCount() const noexcept
{
    return m_sum;
}

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

struct ToStringFunctor
{
public:
    explicit ToStringFunctor(std::string& to_string): 
        m_string(to_string),
        m_temp_string(" ")
    {
    }

    void operator()(const byte_t& byte)
    {
        m_temp_string = binary_lut[byte];
        m_string = m_temp_string + m_string;
    }

private:
    std::string& m_string;
    std::string m_temp_string;
};

template <std::size_t N>
std::string BitSet<N>::ToString() const 
{
    std::string bitset_str;
    ToStringFunctor to_str(bitset_str);
    std::for_each(m_bits, m_bits + m_num_of_bytes, to_str);

    return bitset_str;
}

/******************************************************************************/

template <std::size_t N>
bool BitSet<N>::Get(std::size_t pos) const
{
    if (pos > N)
    {
        throw std::out_of_range("error Get. position out of range.");
    }
    
    return (*this)[pos];
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::SetAll() noexcept
{
    std::fill(m_bits, m_bits + m_num_of_bytes, MASK_ff);
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
    std::fill(m_bits, m_bits + m_num_of_bytes, 0);
    
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

struct FlipAllFunctor
{
public:
    void operator()(byte_t& byte) noexcept
    {
        byte = ~byte;
    }
};

template <std::size_t N>
BitSet<N>& BitSet<N>::FlipAll() noexcept
{
    std::for_each(m_bits, m_bits + m_num_of_bytes, FlipAllFunctor());
    CleanByte(m_bits[GetBitIndex(N)], N);

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
    if (pos > N)
    {
        throw std::out_of_range("error Get. position out of range.");
    }
    
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
    BitSet<N> temp_bitset(*this);
    temp_bitset.FlipAll();

    return temp_bitset;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N> BitSet<N>::operator<<(std::size_t shift_by) const noexcept
{
    BitSet<N> new_set(*this);
    
    return (new_set <<= shift_by);    
}

/******************************************************************************/

template <std::size_t N>
BitSet<N> BitSet<N>::operator>>(std::size_t shift_by) const noexcept
{
    BitSet<N> new_set(*this);
    
    return (new_set >>= shift_by);
}

/******************************************************************************/

template <std::size_t N>
struct AndAssignmentFunctor
{
public:
    explicit AndAssignmentFunctor(const BitSet<N>& rhs): 
        m_rhs(rhs.m_bits), 
        m_index(0)
    {
    }

    void operator()(byte_t& byte)
    {
        byte &= m_rhs[m_index++];
    }   

private:
    const byte_t *m_rhs;
    std::size_t m_index;
};

template <std::size_t N>
BitSet<N>& BitSet<N>::operator&=(const BitSet& rhs) noexcept
{
    AndAssignmentFunctor<N> f1(rhs);
    std::for_each(m_bits, m_bits + m_num_of_bytes, f1);

    return *this;
}

/******************************************************************************/

template <std::size_t N>
struct OrAssignmentFunctor
{
public:
    explicit OrAssignmentFunctor(const BitSet<N>& rhs):
        m_rhs(rhs.m_bits), 
        m_index(0)
    {
    }

    void operator()(byte_t& byte)
    {
        byte |= m_rhs[m_index++];
    }   

private:
    const byte_t *m_rhs;
    std::size_t m_index;
};

template <std::size_t N>
BitSet<N>& BitSet<N>::operator|=(const BitSet& rhs) noexcept
{
    OrAssignmentFunctor<N> f1(rhs);
    std::for_each(m_bits, m_bits + m_num_of_bytes, f1);

    return *this;
}

/******************************************************************************/

template <std::size_t N>
struct XorAssignmentFunctor
{
public:
    explicit XorAssignmentFunctor(const BitSet<N>& rhs): 
        m_rhs(rhs.m_bits), 
        m_index(0)
    {
    }

    void operator()(byte_t& byte)
    {
        byte ^= m_rhs[m_index++];
    }   

private:
    const byte_t *m_rhs;
    std::size_t m_index;
};

template <std::size_t N>
BitSet<N>& BitSet<N>::operator^=(const BitSet& rhs) noexcept
{
    XorAssignmentFunctor<N> f1(rhs);
    std::for_each(m_bits, m_bits + m_num_of_bytes, f1);

    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator<<=(std::size_t shift_by) noexcept
{
    if (N <= shift_by)
    {
        ResetAll();
    }
    else
    {
        BitSet<N> new_set;
        std::copy(Begin(), Begin() + (N - shift_by), new_set.Begin() + shift_by);
        *this = new_set;
    }
    
    return *this;
}

/******************************************************************************/

template <std::size_t N>
BitSet<N>& BitSet<N>::operator>>=(std::size_t shift_by) noexcept
{
    if (N <= shift_by)
    {
        ResetAll();
    }
    else
    {
        std::copy(Begin() + shift_by, End(), Begin());
        std::fill(Begin() + (N- shift_by), End(), 0);
    }
    
    return *this;
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

bool BinaryPredicate(const byte_t& lhs, const byte_t& rhs) 
{
  return (lhs == rhs);
}

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

template <std::size_t N>
typename BitSet<N>::RFProxy BitSet<N>::operator[](std::size_t pos) noexcept
{
    return RFProxy(*this, pos);
}

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

template<std::size_t N>
std::ostream& operator<<(std::ostream &out, const BitSet<N> &bit)
{
    out << bit.ToString();

    return out;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator BitSet<N>::Begin()
{
    return BitsIterator(*this, 1);
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator BitSet<N>::End()
{
    return (BitSet<N>::BitsIterator(*this, N + 1));
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator BitSet<N>::Begin() const
{
    return BitSet<N>::BitsConstIterator(*this, 1);
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator BitSet<N>::End() const
{
    return BitSet<N>::BitsConstIterator(*this, N + 1);
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator BitSet<N>::CBegin() 
{
    return BitSet<N>::BitsConstIterator(*this, 1);
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator BitSet<N>::CEnd() 
{
    return BitSet<N>::BitsConstIterator(*this, N + 1);
}

/**************************** BitsIterator definitions ************************/

template<std::size_t N>
BitSet<N>::BitsIterator::BitsIterator(BitSet& bit_set, std::size_t pos):
    m_bit_set(bit_set),
    m_current_pos(pos)
{
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator& BitSet<N>::BitsIterator::operator++() 
{
    ++m_current_pos;    

    return *this;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator& BitSet<N>::BitsIterator::operator--() 
{
    --m_current_pos;    

    return *this;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsIterator BitSet<N>::BitsIterator::operator++(int)
{
    BitSet<N>::BitsIterator temp_iter(m_bit_set, m_current_pos);
    ++m_current_pos;

    return temp_iter;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsIterator BitSet<N>::BitsIterator::operator--(int)
{
    BitSet<N>::BitsIterator temp_iter(m_bit_set, m_current_pos);
    --m_current_pos;

    return temp_iter;
}


/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator& BitSet<N>::BitsIterator::operator+=(std::size_t move_by)
{
    m_current_pos += move_by;

    return *this;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator& BitSet<N>::BitsIterator::operator-=(std::size_t move_by)
{
    m_current_pos -= move_by;

    return *this;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsIterator BitSet<N>::BitsIterator::operator+(std::size_t inc_by)
{
    BitSet<N>::BitsIterator temp_iter(m_bit_set, m_current_pos); 
    temp_iter += inc_by;

    return temp_iter;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsIterator BitSet<N>::BitsIterator::operator-(std::size_t inc_by) const
{
    BitSet<N>::BitsIterator temp_iter(m_bit_set, m_current_pos); 
    temp_iter -= inc_by;

    return temp_iter;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator::value_type BitSet<N>::BitsIterator::operator[](std::size_t pos)
{   
    return m_bit_set[m_current_pos + pos];
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator::value_type BitSet<N>::BitsIterator::operator*()
{
    return m_bit_set[m_current_pos];
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsIterator::operator==(const BitsIterator &rhs)
{
    return (m_current_pos == rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsIterator::operator!=(const BitsIterator &rhs)
{
    return !(*this == rhs);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsIterator::operator<(const BitsIterator &rhs)
{
    return (m_current_pos < rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsIterator::operator>(const BitsIterator &rhs)
{
    return (m_current_pos > rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsIterator::operator<=(const BitsIterator &rhs)
{
    return (m_current_pos <= rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsIterator::operator>=(const BitsIterator &rhs)
{
    return (m_current_pos >= rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsIterator::difference_type BitSet<N>::BitsIterator::operator-(const BitsIterator& iter)
{
    return (m_current_pos - iter.m_current_pos);
}

/************************* BitsConstIterator definitions **********************/

template<std::size_t N>
BitSet<N>::BitsConstIterator::BitsConstIterator(const BitSet& bit_set, std::size_t pos):
    m_bit_set(bit_set),
    m_current_pos(pos)
{
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator& BitSet<N>::BitsConstIterator::operator++() 
{
    ++m_current_pos;    

    return *this;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator& BitSet<N>::BitsConstIterator::operator--() 
{
    --m_current_pos;    

    return *this;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsConstIterator BitSet<N>::BitsConstIterator::operator++(int)
{
    BitSet<N>::BitsConstIterator temp_iter(m_bit_set, m_current_pos);
    ++m_current_pos;

    return temp_iter;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsConstIterator BitSet<N>::BitsConstIterator::operator--(int)
{
    BitSet<N>::BitsConstIterator temp_iter(m_bit_set, m_current_pos);
    --m_current_pos;

    return temp_iter;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator& BitSet<N>::BitsConstIterator::operator+=(std::size_t move_by)
{
    m_current_pos += move_by;

    return *this;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator& BitSet<N>::BitsConstIterator::operator-=(std::size_t move_by)
{
    m_current_pos -= move_by;

    return *this;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsConstIterator BitSet<N>::BitsConstIterator::operator+(std::size_t inc_by)
{
    BitSet<N>::BitsConstIterator temp_iter(m_bit_set, m_current_pos); 
    temp_iter += inc_by;

    return temp_iter;
}

/******************************************************************************/

template<std::size_t N>
const typename BitSet<N>::BitsConstIterator BitSet<N>::BitsConstIterator::operator-(std::size_t inc_by)
{
    BitSet<N>::BitsConstIterator temp_iter(m_bit_set, m_current_pos); 
    temp_iter -= inc_by;

    return temp_iter;
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator::value_type BitSet<N>::BitsConstIterator::operator[](std::size_t pos)
{   
    return m_bit_set.Get(m_current_pos + pos);
}

/******************************************************************************/

template<std::size_t N>
typename BitSet<N>::BitsConstIterator::value_type BitSet<N>::BitsConstIterator::operator*()
{
    return m_bit_set.Get(m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsConstIterator::operator==(const BitsConstIterator &rhs)
{
    return (m_current_pos == rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsConstIterator::operator!=(const BitsConstIterator &rhs)
{
    return !(*this == rhs);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsConstIterator::operator<(const BitsConstIterator &rhs)
{
    return (m_current_pos < rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsConstIterator::operator>(const BitsConstIterator &rhs)
{
    return (m_current_pos > rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsConstIterator::operator<=(const BitsConstIterator &rhs)
{
    return (m_current_pos <= rhs.m_current_pos);
}

/******************************************************************************/

template<std::size_t N>
bool BitSet<N>::BitsConstIterator::operator>=(const BitsConstIterator &rhs)
{
    return (m_current_pos >= rhs.m_current_pos);
}

/******************************************************************************/
/*
template<std::size_t N>
BitSet<N>::BitsConstIterator::operator ssize_t() 
{
    return m_current_pos;
}
*/
/******************************************************************************/

}// namespace ilrd

#endif //ILRD_RD8081_BITSET_HPP
