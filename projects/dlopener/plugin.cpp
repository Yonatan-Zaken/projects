#include <iostream>

extern "C"
{

void InitPlugin()
{
    std::cout << "init plugin so\n";
}

void RemovePlugin()
{
    std::cout << "remove plugin so\n";
}

}
