/*!
 * \file run_graph_example.hpp
 * \brief Exports a function template to run a graph example.
 **/
#pragma once
#include <a_star.hpp>   // isp1::a_star
#include <iostream>     // std::cout
#include <path.hpp>     // isp1::path
#include <pl/os.hpp>    // PL_OS, PL_OS_WINDOWS, PL_OS_LINUX
#include <pl/timer.hpp> // pl::timer
#include <vector>       // std::vector
#if PL_OS == PL_OS_WINDOWS
#include <Windows.h> // LARGE_INTEGER, QueryPerformanceFrequency, QueryPerformanceCounter
#endif               // PL_OS == PL_OS_WINDOWS

namespace isp1 {
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
 * \return The path found by A*.
 **/
template<
    typename Graph,
    typename NodeIdentifier,
    typename IsGoal,
    typename Heuristic>
path<NodeIdentifier> run_graph_example(
    const Graph&                graph,
    std::vector<NodeIdentifier> start_nodes,
    IsGoal                      is_goal,
    Heuristic                   heuristic,
    std::ostream&               output_stream = std::cout)
{
    // For Windows see:
    // https://docs.microsoft.com/en-gb/windows/desktop/SysInfo/acquiring-high-resolution-time-stamps#using-qpc-in-native-code

#if PL_OS == PL_OS_LINUX
    pl::timer timer;
#elif PL_OS == PL_OS_WINDOWS
    LARGE_INTEGER starting_time;
    LARGE_INTEGER ending_time;
    LARGE_INTEGER elapsed_microseconds;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&starting_time);
#else
#error "Unsupported operating system"
#endif

    const path<NodeIdentifier> a_star_path
        = a_star(graph, start_nodes, is_goal, heuristic);

#if PL_OS == PL_OS_LINUX
    const std::chrono::steady_clock::duration a_star_time_taken
        = timer.elapsed_time();
#elif PL_OS == PL_OS_WINDOWS
    QueryPerformanceCounter(&ending_time);
    elapsed_microseconds.QuadPart
        = ending_time.QuadPart - starting_time.QuadPart;

    // We now have the elapsed number of ticks, along with the
    // number of ticks-per-second. We use these values
    // to convert to the number of elapsed microseconds.
    // To guard against loss-of-precision, we convert
    // to microseconds *before* dividing by ticks-per-second.

    elapsed_microseconds.QuadPart *= 1000000;
    elapsed_microseconds.QuadPart /= frequency.QuadPart;
#endif

    output_stream << "A* total cost: " << a_star_path.g() << '\n'
                  << "path:\n"
                  << a_star_path << '\n'
                  << "time taken: "
#if PL_OS == PL_OS_LINUX
                  << std::chrono::duration_cast<std::chrono::microseconds>(
                         a_star_time_taken)
                         .count()
#elif PL_OS == PL_OS_WINDOWS
                  << elapsed_microseconds.QuadPart
#endif
                  << " microseconds\n\n";

    return a_star_path;
}
} // namespace isp1