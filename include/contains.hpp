#ifndef INCG_ISP1_CONTAINS_HPP
#define INCG_ISP1_CONTAINS_HPP
#include <iterator>                      // std::end
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find

namespace isp1 {
template<typename Container, typename Type>
bool contains(const Container& container, const Type& value)
{
    return pl::algo::find(container, value) != std::end(container);
}
} // namspace isp1
#endif // INCG_ISP1_CONTAINS_HPP
