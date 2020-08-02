#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class FindMax
{
public:
    FindMax(int **mat, std::size_t rows, std::size_t cols, std::size_t numOfThreads);

    int Start();

private:
    int **m_mat;
    std::size_t m_rows;
    std::size_t m_cols;
    std::size_t m_numOfThreads;
    void ThreadFunc(std::size_t startRow, std::size_t endRow);
};

FindMax::FindMax(int **mat, std::size_t rows, std::size_t cols, std::size_t   
numOfThreads):
    m_mat(mat),
    m_rows(rows),
    m_cols(cols),
    m_numOfThreads(numOfThreads)
{
}

int FindMax::Start()
{

    for (size_t i = 0; i < m_numOfThreads; ++i)
    {
        std::size_t start = i * (m_rows / m_numOfThreads);
        std::size_t end = (i + 1) * (m_rows / m_numOfThreads);
        boost::thread t(boost::bind(&FindMax::ThreadFunc, this, start, end));
        t.join();
    }
    
}

void FindMax::ThreadFunc(std::size_t startRow, std::size_t endRow)
{
    int max = m_mat[startRow][0];

    for (size_t i = startRow; i < endRow; i++)
    {
        for (size_t j = 0; j < m_cols; j++)
        {
            if (max < m_mat[i][j])
            {
                max = m_mat[i][j];
            }
        }
    }
    
    std::cout << "Max element in this thread: " << max << "\n";
}

int main()
{

    int **mat1 = new int *[4];
    for(int i = 0; i < 4; ++i)
    {
        mat1[i] = new int[4];
    }

    int count = 0;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            mat1[i][j] = count++;
        }
    }
    
    FindMax fm(mat1, 4, 4, 2);
    fm.Start();

    return 0;
}