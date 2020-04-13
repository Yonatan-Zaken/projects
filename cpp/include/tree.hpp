/***********************
    Tree
    Header File
    07/04/2020
    ILRD - RD8081               
***********************/

#ifndef ILRD_RD8081_TREE_HPP
#define ILRD_RD8081_TREE_HPP

#include <string> // string

#include "utility.hpp"   // noexcept
#include "directory.hpp" // Directory

namespace ilrd
{

class Tree
{
public:
    explicit Tree(std::string path); 
    Tree(const Tree&); 
    // ~Tree() noexcept; = default
    void Print() const noexcept;
    
private:
    std::string m_path;
    Directory m_root;
    int RecBuildTree(std::string path, Directory* m_root);
    Tree& operator=(const Tree&); // = disabled
};

} // namespace ilrd

#endif // ILRD_RD8081_TREE_HPP
