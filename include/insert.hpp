/*!
 * \file insert.hpp
 * \brief Exports the insert function template.
 **/
#pragma once
#include <path.hpp>                      // isp1::path
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::lower_bound
#include <vector>                        // std::vector

namespace isp1 {
/*!
 * \brief Inserts a path into an open list in such a way that the open list
 *        remains sorted by the f values of the paths is ascending order.
 * \param heuristic The heuristic callable that returns the h value for any
 *                  given NodeIdentifier.
 * \param open_list The open list to insert into.
 * \param path_to_insert The path to insert into the open list
 * \tparam Heuristic The type of the heuristic callable.
 * \tparam NodeIdentifier The type of the object
 *                        that identifies a node.
 * \warning The open list given must be sorted by the f
 *          values of the paths in ascending order!
 **/
template<typename Heuristic, typename NodeIdentifier>
void insert(
    Heuristic                     heuristic,
    std::vector<path<NodeIdentifier>>& open_list,
    path<NodeIdentifier>          path_to_insert)
{
    // Find the insertion point.
    // For documentation of lower_bound see:
    // https://en.cppreference.com/w/cpp/algorithm/lower_bound lower_bound is
    // used to find the first position which has a greater f value than the path
    // we want to insert. That position will be the insertion point. Inserting
    // at that position will push the element currently located there (and all
    // the elements after it) to the back by 1 position after having enlarged
    // the vector appropriately. If there is no path in the open list which has
    // a greater f than the path to be inserted lower_bound will return the end
    // iterator, inserting at that position will simply append the path. This
    // also neatly handles the empty case. Note that the lower_bound actually
    // called here is from the <pl/algo/ranged_algorithms.hpp> header file. See:
    // https://github.com/CppPhil/philslib/blob/master/include/pl/algo/ranged_algorithms.hpp#L600
    // This really just adapts the interface to be more 'range based' until
    // proper ranges are available in C++20, somewhat shielding you from the
    // nastiness of C++ iterators.
    // Node that lower_bound requires the range to already be sorted
    // by the comparator otherwise the program is ill-formed!
    const typename std::vector<path<NodeIdentifier>>::const_iterator insertion_point
        = pl::algo::lower_bound(
            /* the range to search in */ open_list,
            /* the value to compare with */ path_to_insert,
            /* the comparator */
            [&heuristic](
                const path<NodeIdentifier>& lhs,
                const path<NodeIdentifier>& rhs) {
                // The g of a path + the h value of the paths last node = the f
                // of that path. less than comparison of the paths f values.
                return (lhs.g() + heuristic(lhs.back().node_identifier()))
                       < (rhs.g() + heuristic(rhs.back().node_identifier()));
            });

    // Insert the path at the insertion point.
    open_list.insert(insertion_point, path_to_insert);
}
} // namespace isp1