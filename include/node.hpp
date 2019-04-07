#ifndef INCG_ISP1_NODE_HPP
#define INCG_ISP1_NODE_HPP
#include <pl/noncopyable.hpp> // PL_NONCOPYABLE
#include <vector> // std::vector
#include <utility> // std::move
#include <memory> // std::unique_ptr

namespace isp1
{
template <typename NodeData>
class Node
{
public:
    using this_type = Node;

    PL_NONCOPYABLE(Node);

    Node(this_type&& other) noexcept = default;

    this_type& operator=(this_type&& other) noexcept = default;

    static this_type createRootNode(NodeData nodeData)
    {
        return Node{
            /* parent */ nullptr,
            /* children */ {},
            /* nodeData */ std::move(nodeData)
        };
    }

    this_type& addChild(NodeData nodeData)
    {
        m_children.push_back(
            std::make_unique<this_type>(
                /* parent */ this,
                /* children */ {},
                /* nodeData */ std::move(nodeData)
            )
        );

        return *children().back();
    }

    this_type* parent() noexcept
    {
        return m_parent;
    }

    const this_type* parent() const noexcept
    {
        return const_cast<this_type*>(this)->parent();
    }

    const std::vector<std::unique_ptr<this_type>>& children() const noexcept
    {
        return m_children;
    }

    NodeData& nodeData() noexcept
    {
        return m_nodeData;
    }

    const NodeData& nodeData() const noexcept
    {
        return const_cast<this_type*>(this)->nodeData();
    }

private:
    Node(this_type* parent, std::vector<std::unique_ptr<this_type>> children, NodeData nodeData)
        : m_parent{parent},
          m_children{std::move(children)},
          m_nodeData{std::move(nodeData)}
    {
    }

    this_type* m_parent;
    std::vector<std::unique_ptr<this_type>> m_children;
    NodeData m_nodeData;
};
} // namespace isp1
#endif // INCG_ISP1_NODE_HPP