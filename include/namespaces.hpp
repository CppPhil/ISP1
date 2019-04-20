/*!
 * \file namespaces.hpp
 * \brief Header file to 'get rid off' namespaces in a desperate attempt to try
 *        to 'simplity' C++.
 **/
#pragma once
#include <chrono>

using namespace std;
using namespace chrono;

namespace pl {
namespace algo {
} // namespace algo
} // namespace pl

using namespace pl;
using namespace algo;
