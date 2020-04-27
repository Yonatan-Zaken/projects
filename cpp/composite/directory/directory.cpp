/***********************
    Directory
    CPP File
    07/04/2020
    ILRD - RD8081               
***********************/
#include <iostream> // cout

#include "directory.hpp" // directory

namespace ilrd
{

Directory::Directory(std::string dirname): m_dirname(dirname)
{}

Directory::~Directory() noexcept
{
    unsigned int size = m_entry_list.size();
    for (unsigned int i = 0; i < size; ++i)
    {
        delete m_entry_list[i];
    }
}

void Directory::Display(int level) const noexcept
{
    std::string buffer(level, '\t');
    std::cout << buffer << "\033[1;36m" << m_dirname << "\033[0m\n";    
    unsigned int size = m_entry_list.size();
            
    for (unsigned int i = 0; i < size; ++i)
    {
        m_entry_list[i]->Display(level + 1);
    }
}

void Directory::AddEntry(const Entry *new_entry)
{
    m_entry_list.push_back(new_entry);
}

} // namespace ilrd


