#ifndef INCG_ISP1_SEARCH_TREE_HPP
#define INCG_ISP1_SEARCH_TREE_HPP
#include <ciso646>  // not
#include <node.hpp> // isp1::Node
#include <optional> // std::optional
#include <utility>  // std::move

namespace isp1 {
template<typename NodeData>
class SearchTree {
public:
    using this_type = SearchTree;
    using node_type = Node<NodeData>;

    SearchTree() : m_rootNode{std::nullopt} {}

    explicit SearchTree(NodeData nodeData)
        : m_rootNode{node_type::createRootNode(std::move(nodeData))}
    {
    }

    std::optional<node_type>& rootNode() noexcept { return m_rootNode; }

    const std::optional<node_type>& rootNode() const noexcept
    {
        return const_cast<this_type*>(this)->rootNode();
    }

    bool isEmpty() const noexcept { return not m_rootNode.has_value(); }

private:
    std::optional<node_type> m_rootNode;
};
} // namespace isp1
#endif // INCG_ISP1_SEARCH_TREE_HPP
