//
// Created by saracortez on 08/03/24.
//

#ifndef DA_PROJETO1_UTILS_H
#define DA_PROJETO1_UTILS_H

#include "DataParser.h"
class Utils {
public:

//void Edmonds-Karp()
//int calculateReceivedSupply(Graph<string>&g, unordered_map<string, City> &city_codes);
    static int calculateReceivedSupply(Graph<string> &g, unordered_map<string, City> &city_codes,
                                       unordered_map<string, double> flows);

    static void printNotFullySuppliedCities(Graph<string> &g, unordered_map<string, City> &city_codes,
                                            unordered_map<string, double> flows);

    static unordered_map<string, double> maxFlow(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                                                 unordered_map<string, City> &cities_codes);

    static void testAndVisit(queue<Vertex<string> *> &q, Edge<string> *e, Vertex<string> *v, double r);

    static bool findPath(Graph<string> &g, Vertex<string> *s, Vertex<string> *d);

    static double minResidual(Vertex<string> *s, Vertex<string> *d);

    static void setFlowPath(Vertex<string> *s, Vertex<string> *d, double flow);

    static void chooseCityByName(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes,
                                 unordered_map<string, City> &cities_codes, string city);


    static void removePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes,
                                      unordered_map<string, Station> &stations_code,
                                      unordered_map<string, Reservoir> &reservoirs_code);

    static void pipeFailure(string city, Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                            unordered_map<string, City> &cities_codes);

    static void waterDeficit(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                             unordered_map<string, City> &cities_codes);

    static vector<pair<pair<string, string>, int>>
    computeDiffs(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                 unordered_map<string, City> &cities_codes);

    static void Balance(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                        unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code);

    static vector<int> computeMetrics(Graph<string> g, vector<pair<pair<string, string>, int>> pipeDiffs);

    static bool sortBySecond(pair<pair<string, string>, int> &a, pair<pair<string, string>, int> &b);

    static vector<pair<pair<string, string>, int>> excessFlow(Graph<string> g);


    static void
    chooseFailingReservoir(Graph<string> &g, string code, unordered_map<string, Reservoir> &reservoirs_codes,
                           unordered_map<string, City> &city_codes);

    static void chooseFailingPumpingStation(Graph<string> g, string code, unordered_map<string, Station> &ps_codes,
                                            unordered_map<string, City> &city_codes);

    static void chooseCityByCode(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes,
                                 unordered_map<string, City> &cities_codes, string code);

    static void calculateReceivedSupply(Graph<string> &g, unordered_map<string, City> &city_codes);

    static void waterDeficitChoosePipe(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes,
                                       unordered_map<string, City> &cities_codes, vector<pair<string, string>> pipes);

    static void chooseRemovePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes,
                                            unordered_map<string, Station> &stations_code,
                                            unordered_map<string, Reservoir> &reservoirs_code, string station);

    };

#endif //DA_PROJETO1_UTILS_H
