#ifndef DA_PROJETO1_UTILS_H
#define DA_PROJETO1_UTILS_H

#include "DataParser.h"

/**
 * @file Utils.h
 * @brief Declaration if the class Utils.
 */

/**
 * @brief Utility functions for working with graphs and flow algorithms.
 */
class Utils {
public:

    /**
     * @brief Calculates the number of cities that did not receive enough supply.
     *
     * @param g The graph representing the network flow.
     * @param city_codes A map containing city codes mapped to corresponding City objects.
     * @param flows A map containing flow values for each vertex in the graph.
     * @return The number of cities that did not receive enough supply.
     */
    static int calculateReceivedSupply(Graph<string> &g, unordered_map<string, City> &city_codes,
                                       unordered_map<string, double> flows);
    /**
     * @brief Prints cities that are not fully supplied.
     *
     * @param g The graph representing the network.
     * @param city_codes A map of city codes to City objects.
     * @param flows A map of flows for each city.
     * @details This function runs in time O(V) where V is the number of vertexes in the graph.
     * */
    static void printNotFullySuppliedCities(Graph<string> &g, unordered_map<string, City> &city_codes,
                                            unordered_map<string, double> flows);
    /**
     * @brief Computes the maximum flow in the graph using the Edmonds-Karp algorithm.
     * @param g The graph.
     * @param reservoirs_codes A map of reservoirs' codes to their corresponding Reservoir objects.
     * @param cities_codes A map of cities' codes to their corresponding City objects.
     * @return A map containing the flow values for each city vertex.
     * @details This function has a time complexity of O(E^2 * V), where E is the number of edges
     *          and V is the number of vertices in the graph.
     */

    static unordered_map<string, double> maxFlow(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                                                 unordered_map<string, City> &cities_codes);
    /**
     * @brief Tests if a vertex has not been visited and the residual capacity of the edge is positive,
     *        then marks the vertex as visited, sets the path, and pushes it into the queue.
     * @param q The queue of vertices to be visited.
     * @param e The edge to be tested.
     * @param v The vertex to be visited.
     * @param r The residual capacity of the edge.
     * @details This function runs in constant time O(1).
     */
    static void testAndVisit(queue<Vertex<string> *> &q, Edge<string> *e, Vertex<string> *v, double r);

    /**
   * @brief Finds a path from source to destination in the graph using BFS.
   * @param g The graph.
   * @param s The source vertex.
   * @param d The destination vertex.
   * @return True if a path is found, false otherwise.
   * @details This function has a time complexity of O(V + E), where V is the number of vertices
   *          and E is the number of edges in the graph.
   */
    static bool findPath(Graph<string> &g, Vertex<string> *s, Vertex<string> *d);

    /**
     * @brief Finds the minimum residual capacity along the path from source to destination.
     * @param s The source vertex.
     * @param d The destination vertex.
     * @return The minimum residual capacity.
     * @details This function has a time complexity of O(V), where V is the number of vertices
     *          along the path from source to destination.
     */
    static double minResidual(Vertex<string> *s, Vertex<string> *d);

    /**
     * @brief Updates the flow along the path from source to destination.
     * @param s The source vertex.
     * @param d The destination vertex.
     * @param flow The flow to be added or subtracted.
     * @details This function has a time complexity of O(V), where V is the number of vertices
     *          along the path from source to destination.
     */
    static void setFlowPath(Vertex<string> *s, Vertex<string> *d, double flow);
        /**
     * @brief Chooses a city by name and displays its flow value or the flows of all cities if no city name is specified.
     *
     * @param g The graph representing the network flow.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     * @param city The name of the city to display the flow value for. If "none" is provided, flows for all cities are displayed.
     * @details This function runs in constant time O(1).
     */
    static void chooseCityByName(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes,
                                 unordered_map<string, City> &cities_codes, string city);

    /**
     * @brief Removes pumping stations from the network and checks for affected cities.
     *
     * This function removes pumping stations from the network graph and checks for affected cities
     * in terms of changes in flow after the removal. It then prints the affected cities along with
     * the difference in flow. If no cities are affected, it prints a message indicating so.
     *
     * @param g The graph representing the network flow.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     * @param stations_code A map containing station codes mapped to corresponding Station objects.
     * @param reservoirs_code A map containing reservoir codes mapped to corresponding Reservoir objects.
     *
     * @details The complexity of this function primarily depends on the number of pumping stations
     *             (P) in the network. Let n be the number of vertices and e be the number of edges
     *             in the graph. Finding affected cities involves computing the maximum flow twice:
     *             once before and once after the removal of each pumping station. Therefore, the
     *             time complexity of this function can be expressed as O(P * (e^2 * n)), where e^2
     *             represents the maximum flow computation complexity using the Edmonds-Karp algorithm.
     */
    static void removePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes,
                                      unordered_map<string, Station> &stations_code,
                                      unordered_map<string, Reservoir> &reservoirs_code);

        /**
     * @brief Simulates a pipe failure in a specific city and identifies potentially disconnected edges.
     *
     * This function simulates a pipe failure in the specified city of the network graph and identifies
     * the edges that can be removed without disconnecting the network. It then prints the connections
     * that can be removed one at a time.
     *
     * @param city The city where the pipe failure occurs.
     * @param g The graph representing the network flow.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     *
     * @details The time complexity of this function primarily depends on the number of edges in the graph.
     *          Let n be the number of vertices and e be the number of edges. The function computes the
     *          maximum flow twice for each edge, resulting in a time complexity of O(e^2 * n).
     */
    static void pipeFailure(string city, Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                            unordered_map<string, City> &cities_codes);

        /**
     * @brief Identifies cities affected by water deficit due to the removal of a pipeline and prints the deficits.
     *
     * This function identifies cities affected by water deficit due to the removal of a pipeline
     * in the network graph. It then prints the affected cities along with the deficit in water flow.
     *
     * @param g The graph representing the network flow.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     *
     * @details The time complexity of this function primarily depends on the number of edges in the graph.
     *          Let n be the number of vertices and e be the number of edges. The function computes the
     *          maximum flow twice for each edge, resulting in a time complexity of O(e^2 * n).
     */
    static void waterDeficit(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                             unordered_map<string, City> &cities_codes);

        /**
     * @brief Computes the differences between pipe weights and flow values for each pipe in the graph.
     *
     * This function computes the differences between pipe weights and flow values for each pipe in the
     * given graph and returns a vector of pairs, where each pair contains the source-destination vertex
     * pair and the corresponding difference.
     *
     * @param g The graph representing the network flow.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     * @return A vector of pairs, where each pair contains the source-destination vertex pair and the
     *         corresponding difference between pipe weight and flow.
     *
     * @details The time complexity of this function is O(e), where e is the number of edges in the graph.
     */
    static vector<pair<pair<string, string>, int>> computeDiffs(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                 unordered_map<string, City> &cities_codes);

        /**
     * @brief Balances the network flow by transferring excess flow from pipes to other pipes.
     *
     * This function balances the network flow by transferring excess flow from pipes with excess flow
     * to other pipes. It iteratively performs flow transfers to minimize flow imbalances in the network.
     *
     * @param g The graph representing the network flow.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     * @param stations_code A map containing station codes mapped to corresponding Station objects.
     *
     * @details The time complexity of this function primarily depends on the number of iterations performed
     *          to balance the flow. Let n be the number of vertices and e be the number of edges. In each
     *          iteration, excess flow pipes are identified (O(e log e)), and flow transfers are performed,
     *          resulting in a total time complexity of O(k * e log e), where k is the number of iterations.
     */
    static void Balance(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                        unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code);
        /**
     * @brief Computes metrics such as average, variance, and maximum difference from a vector of pipe differences.
     *
     * This function computes metrics such as average, variance, and maximum difference from the vector
     * of pipe differences and returns them in a vector.
     *
     * @param g The graph representing the network flow.
     * @param pipeDiffs A vector of pairs containing pipe differences.
     * @return A vector containing the computed metrics (average, variance, maximum difference).
     *
     * @details The time complexity of this function is O(n), where n is the size of the pipe differences vector.
     */
    static vector<int> computeMetrics(Graph<string> g, vector<pair<pair<string, string>, int>> pipeDiffs);
        /**
     * @brief Comparator function to sort pairs based on the second element in descending order.
     *
     * @param a First pair to compare.
     * @param b Second pair to compare.
     * @return True if the second element of pair 'a' is greater than that of pair 'b', otherwise false.
     *
     * @details The time complexity of this function is O(1).
     */

    static bool sortBySecond(pair<pair<string, string>, int> &a, pair<pair<string, string>, int> &b);

    /**
     * @brief Identifies pipes with excess flow and sorts them based on the excess flow ratio.
     *
     * This function identifies pipes with excess flow (flow > 90% of weight) and sorts them based on
     * the excess flow ratio (flow/weight). It returns a vector of pairs containing the source-destination
     * vertex pair and the excess flow ratio.
     *
     * @param g The graph representing the network flow.
     * @return A vector of pairs containing the source-destination vertex pair and the excess flow ratio.
     *
     * @details The time complexity of this function is O(e log e), where e is the number of edges in the graph.
     */
    static vector<pair<pair<string, string>, int>> excessFlow(Graph<string> g);


    static void noUnnecessaryMaxFlow(Graph<string> &g, string code, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &city_codes);

    /**
     * @brief Simulates the scenario where a reservoir fails and evaluates the impact on the water supply to cities.
     *
     * This function simulates the scenario where a reservoir with the specified code fails and evaluates
     * the impact on the water supply to cities. It calculates the number of cities not receiving sufficient
     * supply before and after the reservoir failure and prints the affected cities.
     *
     * @param g The graph representing the network flow.
     * @param code The code of the reservoir to simulate the failure.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param city_codes A map containing city codes mapped to corresponding City objects.
     *
     * @details The time complexity of this function is O(e^2 * v), where e is the number of edges and
     *          v is the number of vertices in the graph.
     */
    static void chooseFailingReservoir(Graph<string> &g, string code, unordered_map<string, Reservoir> &reservoirs_codes,
                           unordered_map<string, City> &city_codes);

        /**
     * @brief Selects a city by its code and displays its flow or lists all cities and their flows if code is "none".
     *
     * This function selects a city by its code and displays its flow. If the code is "none", it lists all cities
     * and their corresponding flows. If the provided code does not match any city code, it prints a message stating
     * that the city does not exist.
     *
     * @param g The graph representing the network flow.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     * @param code The code of the city to select. If "none", all cities and their flows are listed.
     *
     * @details The time complexity of this function depends on the size of the graph and the maxFlow function.
     *          Let e be the number of edges and v be the number of vertices in the graph, the time complexity
     *          is O(e^2 * v) for the maxFlow function.
     */
    static void chooseCityByCode(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes,
                                 unordered_map<string, City> &cities_codes, string code);

    /**
     * @brief Identifies the impact of chosen pipes on cities' water deficit.
     *
     * This function calculates the impact of selected pipes on cities' water deficit.
     * It takes a vector of pairs representing the pipes to be analyzed, and for each pipe, it temporarily
     * sets its weight to 0, recalculates the flow, and determines the changes in the water deficit
     * for each affected city. After analyzing all pipes, it restores their original weights and displays
     * the cities affected by the chosen pipes and their respective water deficit changes.
     *
     * @param g The graph representing the network.
     * @param reservoirs_codes A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     * @param pipes A vector of pairs representing the pipes to be analyzed, where each pair contains
     *              the origin and destination codes of a pipe.
     *
     * @details The time complexity of this function depends on the size of the graph, the number of pipes
     *          to be analyzed, and the maxFlow function. Let e be the number of edges, v be the number
     *          of vertices, and p be the number of pipes, the time complexity is O(p * (e^2 * v)).
     */
    static void waterDeficitChoosePipe(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                                       unordered_map<string, City> &cities_codes, vector<pair<string, string>> pipes);
    /**
     * @brief Chooses and removes a pumping station from the network and displays affected cities and their supply changes.
     *
     * This function selects a pumping station from the network specified by its station code,
     * removes it from the graph, recalculates the flow, and displays the affected cities along with the changes in their supply.
     *
     * @param g The graph representing the network.
     * @param cities_codes A map containing city codes mapped to corresponding City objects.
     * @param stations_code A map containing station codes mapped to corresponding Station objects.
     * @param reservoirs_code A map containing reservoir codes mapped to corresponding Reservoir objects.
     * @param station The code of the pumping station to be removed.
     *
     * @details The time complexity of this function depends on the size of the graph and the maxFlow(O(e^2 * v)).
     *
     * */
    static void chooseRemovePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes,
                                            unordered_map<string, Station> &stations_code,
                                            unordered_map<string, Reservoir> &reservoirs_code, string station);

    };

#endif //DA_PROJETO1_UTILS_H
