#ifndef INCG_ISP1_INSERT_HPP
#define INCG_ISP1_INSERT_HPP
#include <path.hpp>                      // isp1::Path
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::lower_bound
#include <vector>                        // std::vector

namespace isp1 {
template<typename Heuristic, typename NodeIdentifier>
void insert(
    Heuristic                          heuristic,
    std::vector<Path<NodeIdentifier>>& openList,
    Path<NodeIdentifier>               pathToInsert)
{
    typename std::vector<Path<NodeIdentifier>>::iterator insertionPoint{
        pl::algo::lower_bound(
            openList,
            pathToInsert,
            [&heuristic](
                const Path<NodeIdentifier>& lhs,
                const Path<NodeIdentifier>& rhs) {
                return (lhs.g() + heuristic(lhs.back().nodeIdentifier()))
                       < (rhs.g() + heuristic(rhs.back().nodeIdentifier()));
            })};

    openList.insert(insertionPoint, std::move(pathToInsert));
}
} // namespace isp1
#endif // INCG_ISP1_INSERT_HPP
