#include <algorithm>   // generate, for_each
#include <iostream>    // cout 
#include <vector>      // vector

class Generate
{
public:
    Generate(int from = 0, int jump = 1): m_start(from), m_jump(jump) {}    
    
    int operator()()
    {
        int tmp = m_start;
        m_start += m_jump;
        return tmp;
    }
    
private:
    int m_start;
    int m_jump;
};

class Sum
{
public:
    Sum(): m_sum(0) {}
    
    void operator()(int& i)
    {
        m_sum +=i;
    }

    int GetSum() const { return m_sum; }    
        
private:
    int m_sum;
};

/******************************************************************************/

static void print_v(const std::vector<int>& v);

int main()
{
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), Generate(7, -1));
    print_v(v);
    
    Sum sum_1;
    Sum s = std::for_each(v.begin(), v.end(), sum_1);
    
    print_v(v);
    std::cout << "sum: " << s.GetSum() << "\n";
        
    return 0;
}

/******************************************************************************/

static void print_v(const std::vector<int>& v)
{
    std::cout << "vector: ";
    
    for (std::vector<int>::const_iterator it = v.begin(); it < v.end(); ++it)
    {
        std::cout << *it << " ";
    }
    
    std::cout << "\n";
}
