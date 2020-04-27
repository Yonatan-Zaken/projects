/***********************
    Tree
    CPP File
    07/04/2020
    ILRD - RD8081               
***********************/
#include <string>   // string
#include <dirent.h> // opendir

#include "tree.hpp" // tree
#include "file.hpp" // file

namespace ilrd
{

Tree::Tree(std::string path): m_path(path), m_root(path)
{
    RecBuildTree(path, &m_root);    
}

Tree::Tree(const Tree& other): m_path(other.m_path), m_root(other.m_path)
{
    RecBuildTree(m_path, &m_root);
}

void Tree::Print() const noexcept
{
    m_root.Display(0);      
}

int Tree::RecBuildTree(std::string path, Directory* m_root)
{
    struct dirent *entry = NULL;
    DIR *dp = NULL;
    int status = FAIL;
    
    if (NULL != (dp = opendir(path.c_str())))
    {
        status = SUCCESS;
        while (NULL != (entry = readdir(dp)))
        {
            std::string dir_path = std::string(path) + "/" + std::string(entry->d_name);
            std::string entry_name = entry->d_name;
            
            if(("." != entry_name) && (".." != entry_name))
            {
                if (DT_REG == entry->d_type)
                {
                    m_root->AddEntry(new File(entry_name));      
                }
                
                else if (DT_DIR == entry->d_type)
                {
                    Directory *new_dir = new Directory(entry_name);   
                    m_root->AddEntry(new_dir);
                    RecBuildTree(dir_path, new_dir);         
                }
            }
        }
    }
    closedir(dp);
    return status;
}

} // namespace ilrd
