#if 0
#include <algorithm>
#include <astar.hpp>
#include <iterator>
#include <list>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace isp1 {
namespace {
decltype(auto) back(
    const graph_undirected<std::string, int, int>::search_path& p)
{
    return *std::rbegin(p);
}

class path_comparator {
public:
    explicit path_comparator(
        std::function<graph_undirected<std::string, int, int>::cost_type(
            graph_undirected<std::string, int, int>::const_iterator)> heuristic)
        : m_heuristic{std::move(heuristic)}
    {
    }

    bool operator()(
        const graph_undirected<std::string, int, int>::search_path& p1,
        const graph_undirected<std::string, int, int>::search_path& p2) const
    {
        return (p2.total_cost() + m_heuristic(back(p2).first))
               < (p1.total_cost() + m_heuristic(back(p1).first));
    }

private:
    std::function<graph_undirected<std::string, int, int>::cost_type(
        graph_undirected<std::string, int, int>::const_iterator)>
        m_heuristic;
};
} // anonymous namespace

graph_undirected<std::string, int, int>::search_path aStar(
    const graph_undirected<std::string, int, int>&          graph,
    graph_undirected<std::string, int, int>::const_iterator start,
    std::function<bool(graph_undirected<std::string, int, int>::const_iterator)>
                                                                  isGoal,
    std::function<graph_undirected<std::string, int, int>::cost_type(
        graph_undirected<std::string, int, int>::const_iterator)> heuristic)
{
    using Graph          = graph_undirected<std::string, int, int>;
    using cost_type      = Graph::cost_type;
    using const_iterator = Graph::const_iterator;
    using search_path    = Graph::search_path;
    using node           = Graph::node;

    if (start == std::end(graph)) {
        throw std::logic_error{"start was the end-iterator!"};
    }

    const cost_type nul_cost{cost_type()};

    // closed list of the {name, node}s already handled.
    std::list<const_iterator> expanded;

    // open list containing paths
    // a path consists of {{name, node}, gCost}
    std::priority_queue<search_path, std::vector<search_path>, path_comparator>
        frontier((path_comparator(heuristic)));

    {
        search_path p;
        p.push_back(
            {start,
             nul_cost}); // Add start node with 0 g to a newly created path
        frontier.push(std::move(p)); // Add the path
    }

    while (!frontier.empty()) {
        // Grab the highest priority (lowest f cost) path
        search_path p{frontier.top()};
        frontier.pop(); // Remove it from the open list

        // look in the closed list for the {name, node} of the path's last
        // element
        /// expanded does not contain path's last state
        if (std::find(expanded.cbegin(), expanded.cend(), back(p).first)
            == expanded.end()) { // It ain't in the closed list -> do shit.

            // Grab the {name, node}
            const_iterator last{back(p).first};

            // Put it in the closed list.
            expanded.push_back(last);

            if (isGoal(last)) { return p; }

            std::vector<node::edge> legalActions{graph.get_edges(last)};

            // Iterate over the edges.
            for (std::vector<node::edge>::const_iterator it{
                     legalActions.cbegin()};
                 it != legalActions.cend();
                 ++it) {
                //! Dijkstra's algorithm cannot be computed with negative
                //! weights.
                if (it->cost() < nul_cost) {
                    throw std::logic_error{"Negative costs are not allowed!"};
                }

                // Create a new path by copying the current one
                search_path newPath{p};

                // app the target with its g cost to the new path
                newPath.push_back({it->target(), it->cost()});

                // add the path to the open list
                frontier.push(newPath);
            }
        }
    }

    /// Could not find a solution
    search_path empty;
    return empty;
}
} // namespace isp1
#endif