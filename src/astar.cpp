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

    std::list<const_iterator> expanded;
    std::priority_queue<search_path, std::vector<search_path>, path_comparator>
        frontier((path_comparator(heuristic)));

    {
        search_path p;
        p.push_back({start, nul_cost});
        frontier.push(std::move(p));
    }

    while (!frontier.empty()) {
        search_path p{frontier.top()};
        frontier.pop();

        /// expanded does not contain path's last state
        if (std::find(expanded.cbegin(), expanded.cend(), back(p).first)
            == expanded.end()) {
            const_iterator last{back(p).first};
            expanded.push_back(last);

            if (isGoal(last)) { return p; }

            std::vector<node::edge> legalActions{graph.get_edges(last)};

            for (std::vector<node::edge>::const_iterator it{
                     legalActions.cbegin()};
                 it != legalActions.cend();
                 ++it) {
                //! Dijkstra's algorithm cannot be computed with negative
                //! weights.
                if (it->cost() < nul_cost) {
                    throw std::logic_error{"Negative costs are not allowed!"};
                }

                search_path newPath{p};
                newPath.push_back({it->target(), it->cost()});
                frontier.push(newPath);
            }
        }
    }

    /// Could not find a solution
    search_path empty;
    return empty;
}
} // namespace isp1