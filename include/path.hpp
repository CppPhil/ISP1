/*!
 * \file path.hpp
 * \brief Exports the path class template.
 **/
#pragma once
#include <cost.hpp>                 // isp1::cost
#include <cstddef>                  // std::size_t
#include <identifier_with_cost.hpp> // isp1::identifier_with_cost
#include <initializer_list>         // std::initializer_list
#include <ostream>                  // std::ostream
#include <stdexcept>                // std::out_of_range
#include <vector>                   // std::vector

namespace isp1 {
/*!
 * \brief Type for a path of nodes through a graph.
 * \tparam NodeIdentifier the type of the kind of object used to identify a
 *                        node.
 **/
template<typename NodeIdentifier>
class path {
public:
    // Type aliases
    // See https://www.youtube.com/watch?v=qGxuD9o4GDA for the usage of the
    // typename keyword in this context.
    typedef path                                              this_type;
    typedef std::vector<identifier_with_cost<NodeIdentifier>> container_type;
    typedef typename container_type::iterator                 iterator;
    typedef typename container_type::const_iterator           const_iterator;
    typedef typename container_type::reverse_iterator         reverse_iterator;
    typedef
        typename container_type::const_reverse_iterator const_reverse_iterator;

    /*!
     * \brief Creates an empty path.
     **/
    path() = default;

    /*!
     * \brief Initializer list constructor.
     * \param init_list The initializer_list to initialize with.
     **/
    path(std::initializer_list<identifier_with_cost<NodeIdentifier>> init_list)
        : m_vector(init_list.begin(), init_list.end())
    {
    }

    /*!
     * \brief Returns an iterator to the first element of the path.
     * \return Iterator to the first element.
     * \note Constant complexity
     * \warning If the path is empty, the returned iterator will be equal to
     *          end().
     **/
    iterator begin() { return m_vector.begin(); }

    /*!
     * \brief Returns an iterator to the first element of the path.
     * \return Iterator to the first element.
     * \note Constant complexity
     * \warning If the path is empty, the returned iterator will be equal to
     *          end().
     **/
    const_iterator begin() const { return m_vector.begin(); }

    /*!
     * \brief Returns an iterator to the first element of the path.
     * \return Iterator to the first element.
     * \note Constant complexity
     * \warning If the path is empty, the returned iterator will be equal to
     *          end().
     **/
    const_iterator cbegin() const { return m_vector.cbegin(); }

    /*!
     * \brief Returns an iterator to the element following the last element of
     *        the path.
     * \return Iterator to the element following the last element.
     * \note Constant complexity
     * \warning The element referred to by the iterator returned acts as a
     *          placeholder; attempting to access it results in
     *          undefined behavior.
     **/
    iterator end() { return m_vector.end(); }

    /*!
     * \brief Returns an iterator to the element following the last element of
     *        the path.
     * \return Iterator to the element following the last element.
     * \note Constant complexity
     * \warning The element referred to by the iterator returned acts as a
     *          placeholder; attempting to access it results in
     *          undefined behavior.
     **/
    const_iterator end() const { return m_vector.end(); }

    /*!
     * \brief Returns an iterator to the element following the last element of
     *        the path.
     * \return Iterator to the element following the last element.
     * \note Constant complexity
     * \warning The element referred to by the iterator returned acts as a
     *          placeholder; attempting to access it results in
     *          undefined behavior.
     **/
    const_iterator cend() const { return m_vector.cend(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     *        path.
     * \return Reverse iterator to the first element. \note Constant
     *         complexity
     *
     * Returns a reverse iterator to the first element of the reversed path.
     * It corresponds to the last element of the non-reversed path.
     * If the path is empty, the returned iterator is equal to rend().
     **/
    reverse_iterator rbegin() { return m_vector.rbegin(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     *        path.
     * \return Reverse iterator to the first element. \note Constant
     *         complexity
     *
     * Returns a reverse iterator to the first element of the reversed path.
     * It corresponds to the last element of the non-reversed path.
     * If the path is empty, the returned iterator is equal to rend().
     **/
    const_reverse_iterator rbegin() const { return m_vector.rbegin(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     *        path.
     * \return Reverse iterator to the first element. \note Constant
     *         complexity
     *
     * Returns a reverse iterator to the first element of the reversed path.
     * It corresponds to the last element of the non-reversed path.
     * If the path is empty, the returned iterator is equal to rend().
     **/
    const_reverse_iterator crbegin() const { return m_vector.crbegin(); }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed path.
     * \return Reverse iterator to the element
     *         following the last element.
     * \note Constant complexity
     * \warning Dereferencing the iterator returned results in
     *          undefined behavior.
     *
     * Returns a reverse iterator to the element following the last element of
     * the reversed path. It corresponds to the element preceding the first
     * element of the non-reversed path.
     **/
    reverse_iterator rend() { return m_vector.rend(); }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed path.
     * \return Reverse iterator to the element
     *         following the last element.
     * \note Constant complexity
     * \warning Dereferencing the iterator returned results in
     *          undefined behavior.
     *
     * Returns a reverse iterator to the element following the last element of
     * the reversed path. It corresponds to the element preceding the first
     * element of the non-reversed path.
     **/
    const_reverse_iterator rend() const { return m_vector.rend(); }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed path.
     * \return Reverse iterator to the element
     *         following the last element.
     * \note Constant complexity
     * \warning Dereferencing the iterator returned results in
     *          undefined behavior.
     *
     * Returns a reverse iterator to the element following the last element of
     * the reversed path. It corresponds to the element preceding the first
     * element of the non-reversed path.
     **/
    const_reverse_iterator crend() const { return m_vector.crend(); }

    /*!
     * \brief Appends a new NodeIdentifier along with its g value to this path.
     * \param identifier The NodeIdentifier to append.
     * \param g The g value associated with identifier.
     **/
    void append(NodeIdentifier identifier, cost g)
    {
        m_vector.emplace_back(identifier, g);
    }

    /*!
     * \brief Appends an identifier_with_cost to this path.
     * \param identifier The identifier_with_cost to append.
     **/
    void append(identifier_with_cost<NodeIdentifier> identifier)
    {
        m_vector.push_back(identifier);
    }

    /*!
     * \brief Queries for the size of this path.
     * \return The amount of nodes in this path.
     **/
    std::size_t size() const { return m_vector.size(); }

    /*!
     * \brief Queries this path for emptiness.
     * \return true if this path contains no nodes; otherwise false.
     **/
    bool is_empty() const { return m_vector.empty(); }

    /*!
     * \brief Returns a reference to the first element.
     * \throws out_of_range if this path is empty.
     **/
    identifier_with_cost<NodeIdentifier>& front()
    {
        if (is_empty()) {
            throw std::out_of_range(
                "front may not be called on an empty path.");
        }

        return m_vector.front();
    }

    /*!
     * \brief Returns a const reference to the first element.
     * \throws out_of_range if this path is empty.
     * \note This is the const overload.
     **/
    const identifier_with_cost<NodeIdentifier>& front() const
    {
        return const_cast<this_type*>(this)->front();
    }

    /*!
     * \brief Returns a reference to the last element.
     * \throws out_of_range if this path is empty.
     **/
    identifier_with_cost<NodeIdentifier>& back()
    {
        if (is_empty()) {
            throw std::out_of_range("back may not be called on an empty path.");
        }

        return m_vector.back();
    }

    /*!
     * \brief Returns a const reference to the last element.
     * \throws out_of_range if this path is empty.
     * \note This is the const overload.
     **/
    const identifier_with_cost<NodeIdentifier>& back() const
    {
        return const_cast<this_type*>(this)->back();
    }

    /*!
     * \brief Calculates the g cost of this entire path.
     * \return The g value for this path.
     **/
    cost g() const
    {
        // Start out as 0.
        cost the_cost = 0;

        // Iterate over all the elements.
        for (const identifier_with_cost<NodeIdentifier>& identifier :
             m_vector) {
            // Accumulate the g value of the current element
            the_cost += identifier.g();
        }

        return the_cost;
    }

private:
    std::vector<identifier_with_cost<NodeIdentifier>>
        m_vector; /*!< The underlying container */
};

/*!
 * \brief Prints a path.
 * \param os The ostream to print to.
 * \param the_path The path to print.
 * \tparam NodeIdentifier The type used to identify a node.
 * \return A reference to os.
 **/
template<typename NodeIdentifier>
std::ostream& operator<<(std::ostream& os, const path<NodeIdentifier>& the_path)
{
    os << '[';

    for (typename path<NodeIdentifier>::const_iterator it  = the_path.begin(),
                                                       end = the_path.end();
         it != end;
         ++it) {
        os << *it;

        if (it != end - 1) { os << ",\n"; }
    }

    os << ']';
    return os;
}
} // namespace isp1