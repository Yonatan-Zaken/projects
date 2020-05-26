/*********************
    Factory
    Header File
    21/05/2020
    ILRD - RD8081             
*********************/

#ifndef ILRD_RD8081_FACTORY_HPP
#define ILRD_RD8081_FACTORY_HPP

#include <cassert>  // assert
#include <boost/function.hpp> // boost::function
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <map> // std::map

#include "utility.hpp" // Uncopyable

namespace ilrd
{

template <class BASE, class KEY, class PARAM>
class Factory: private Uncopyable
{
public:	
    typedef boost::function<boost::shared_ptr<BASE> (PARAM)> recipe_t;

    // explicit Factory() = default;
    // ~Factory() noexcept = default;

    void AddRecipe(const KEY& key, recipe_t function);
    // AddRecipe with existing key will replace the recipe

    boost::shared_ptr<BASE> Fabricate(const KEY& key, PARAM param);
   
private:
    typedef std::map<KEY, recipe_t> recipeList_t;

    recipeList_t m_recipeList;
};

/****************************** Factory Definitions ***************************/

template <class BASE, class KEY, class PARAM>
void Factory<BASE, KEY, PARAM>::AddRecipe(const KEY& key, recipe_t function)
{
    std::pair<KEY, recipe_t> newPair(key, function);
    std::pair<typename recipeList_t::iterator, bool> ret = 
    m_recipeList.insert(newPair);

    if (false == ret.second)
    {
        m_recipeList[newPair.first] = function;
    }
}

/******************************************************************************/

template <class BASE, class KEY, class PARAM>
boost::shared_ptr<BASE> Factory<BASE, KEY, PARAM>::Fabricate(const KEY& key, PARAM param)
{
    assert(m_recipeList.find(key) != m_recipeList.end());
    
    return boost::shared_ptr<BASE>(m_recipeList[key](param));
}

} // namespace ilrd

#endif // ILRD_RD8081_FACTORY_HPP