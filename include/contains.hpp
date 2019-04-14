#pragma once
#include <iterator> // end
#include <namespaces.hpp>
#include <pl/algo/ranged_algorithms.hpp> // find

template<typename Container, typename Type>
bool contains(const Container& container, const Type& value)
{
    return find(container, value) != end(container);
}
