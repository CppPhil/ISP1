/*!
 * \file run_graph_example.hpp
 * \brief Exports a function template to run a graph example.
 **/
#pragma once
#include <a_star.hpp> // a_star
#include <iostream>   // cout
#include <namespaces.hpp>
#include <path.hpp>     // path
#include <pl/timer.hpp> // timer
#include <vector>       // vector

/*!
 * \brief Runs a graph example using the A* algorithm.
 *        Also prints timing information along with some other information.
 * \param graph The graph to use.
 * \param start_nodes The start nodes in the graph.
 * \param is_goal Predicate to check whether some node is a goal node.
 * \param heuristic The heuristic to use for the A* algorithm.
 * \param output_stream The ostream to print the information to.
 * \tparam Graph Type of the graph to use.
 * \tparam NodeIdentifier The type used to identify nodes within the graph.
 * \tparam IsGoal The type of the predicate that checks if a node is a target
 *                node.
 * \tparam Heuristic The type of the heuristic callable.
 **/
template<
    typename Graph,
    typename NodeIdentifier,
    typename IsGoal,
    typename Heuristic>
void run_graph_example(
    const Graph&           graph,
    vector<NodeIdentifier> start_nodes,
    IsGoal                 is_goal,
    Heuristic              heuristic,
    ostream&               output_stream = cout)
{
    timer timer;

    timer.reset();
    const path<NodeIdentifier> a_star_path
        = a_star(graph, start_nodes, is_goal, heuristic);
    const steady_clock::duration a_star_time_taken = timer.elapsed_time();

    output_stream << "A* total cost: " << a_star_path.g() << '\n'
                  << "path:\n"
                  << a_star_path << '\n'
                  << "time taken: "
                  << duration_cast<nanoseconds>(a_star_time_taken).count()
                  << "ns\n\n";
}
