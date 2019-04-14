#pragma once
#include <iterator>                      // std::end
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find

template<typename Container, typename Type>
bool contains(const Container& container, const Type& value)
{
    return pl::algo::find(container, value) != std::end(container);
}
