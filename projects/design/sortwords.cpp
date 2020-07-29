#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class FileHandler
{
public:
    explicit FileHandler(const std::string& path)
    {
        m_file.open(path.c_str());
    }

    ~FileHandler()
    {
        m_file.close();
    }

    std::ifstream& GetHandle() 
    {
        return m_file;
    }

private:
    std::ifstream m_file;    
};

/******************************************************************************/

class SortWords
{   
public:
    SortWords(std::string sort, std::string split, const char *F1, const char *F2, const char *F3);
    ~SortWords();
private:
    FileHandler m_file1;
    FileHandler m_file2;
    FileHandler m_file3;
    char m_sort;
    char m_split;
    std::map<std::string, int> m_result;
    boost::mutex m_lock;

    void SortFiles();
    void ThreadFunc(FileHandler& file);
};

SortWords::SortWords(std::string sort, std::string split, const char *F1, const char *F2, const char *F3):
    m_file1(F1), m_file2(F2), m_file3(F3), m_sort(sort[1]), m_split(split[1])
{
}

void SortWords::ThreadFunc(FileHandler& file)
{
    std::string currentWord;
    while (file.GetHandle() >> currentWord)
    {
        boost::mutex::scoped_lock lock(m_lock);
        ++m_result[currentWord];
    }
    
}

void SortWords::SortFiles()
{
    boost::thread t1(&SortWords::ThreadFunc, this, m_file1);
    boost::thread t2(&SortWords::ThreadFunc, this, m_file2);
    boost::thread t3(&SortWords::ThreadFunc, this, m_file3);
    t1.join();
    t2.join();
    t3.join();
}

SortWords::~SortWords()
{

}

/******************************************************************************/

int main(int argc, char const *argv[])
{
    std::string sort;
    std::string split;

    std::cout << "enter your options:\n";
    std::cout << "sort ";
    std::cin >> sort;
    std::cout << "split ";
    std::cin >> split;

    return 0;
}
