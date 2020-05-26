/*********************
    Serializer
    Header File
    24/05/2020
    ILRD - RD8081               
*********************/

#ifndef ILRD_RD8081_SERIALIZER_HPP
#define ILRD_RD8081_SERIALIZER_HPP

#include <string> // std::string
#include <iostream> // ostream
#include <typeinfo> // typeid
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/core/demangle.hpp>

#include "utility.hpp" // Uncopyable
#include "factory.hpp" // Factory

namespace ilrd
{

// Requirements: BASE must overload operator<<
template <class BASE>
class Serializer : private Uncopyable
{  
public:
    // explicit Serializer() = default;
    // ~Serializer() noexcept = default;

    void Serialize(const BASE& objToSerialize, std::ostream& stream);
    boost::shared_ptr<BASE> Deserialize(std::istream& stream);

    template <class DERIVED>
    void Add(typename Factory<BASE, std::string, std::istream&>::recipe_t recipe);

private:
    Factory<BASE, std::string, std::istream&> m_factory;
};

/******************************************************************************/

template <class BASE>
void Serializer<BASE>::Serialize(const BASE& objToSerialize, std::ostream& stream)
{
    objToSerialize << stream;
}

/******************************************************************************/

template <class BASE>
boost::shared_ptr<BASE> Serializer<BASE>::Deserialize(std::istream& stream)
{
    std::string name;
    
    stream >> name;
    return m_factory.Fabricate(name, stream);
}

/******************************************************************************/

template <class BASE>
template <class DERIVED>
void Serializer<BASE>::Add(typename Factory<BASE, std::string, std::istream&>::recipe_t recipe)
{
        m_factory.AddRecipe(typeid(DERIVED).name(), recipe);
}

} // namespace ilrd

#endif // ILRD_RD8081_SERIALIZER_HPP