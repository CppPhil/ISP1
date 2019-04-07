#ifndef INCG_ISP1_PATH_HPP
#define INCG_ISP1_PATH_HPP
#include <node.hpp> // isp1::Node
#include <vector> // std::vector
#include <utility> // std::move
#include <iterator> // std::begin
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::reverse

namespace isp1
{
template <typename NodeData>
class Path
{
public:
    using this_type = Path;
    using node_type = Node<NodeData>;

    explicit Path(std::vector<node_type*> nodePath)
        : m_nodePath{std::move(nodePath)}
    {
    }

    node_type& first() noexcept
    {
        return *m_nodePath.front();
    }

    const node_type& first() const noexcept
    {
        return const_cast<this_type*>(this)->first();
    }

    node_type& prepend(node_type& node)
    {
        m_nodePath.insert(std::begin(m_nodePath), &node);
        return first();
    }

    this_type& reverse() noexcept
    {
        pl::algo::reverse(m_nodePath);
        return *this;
    }

private:
    std::vector<node_type*> m_nodePath;
};
} // namespace isp1
#endif // INCG_ISP1_PATH_HPP
