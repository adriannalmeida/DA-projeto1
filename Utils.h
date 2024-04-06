//
// Created by saracortez on 08/03/24.
//

#ifndef DA_PROJETO1_UTILS_H
#define DA_PROJETO1_UTILS_H

#include "DataParser.h"

//void Edmonds-Karp()
//int calculateReceivedSupply(Graph<string>&g, unordered_map<string, City> &city_codes);
int calculateReceivedSupply(Graph<string> &g,unordered_map<string, City> &city_codes, unordered_map<string, double> flows);
void printNotFullySuppliedCities(Graph<string> &g, unordered_map<string, City> &city_codes, unordered_map<string, double> flows);

unordered_map<string, double> maxFlow(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes);

void testAndVisit(queue<Vertex<string>*> &q, Edge<string>* e, Vertex<string>* v, double r );
bool findPath(Graph<string>& g, Vertex<string>*s, Vertex<string>*d);
double minResidual(Vertex<string>* s, Vertex<string>* d);
void setFlowPath (Vertex<string>* s, Vertex<string>* d, double flow);
void chooseCityByName(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, string city);


void removePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code, unordered_map<string, Reservoir> &reservoirs_code);

void pipeFailure(string city, Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes);
void waterDeficit(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes);

vector<pair<pair<string, string>, int>> computeDiffs(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes);
void Balance(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code);
vector<int> computeMetrics(Graph<string> g, vector<pair<pair<string, string>, int>> pipeDiffs);
bool sortBySecond(pair<pair<string, string>, int> &a, pair<pair<string, string>, int> &b);
vector<pair<pair<string, string>, int>> excessFlow(Graph<string> g);


void chooseFailingReservoir(Graph<string> &g, string code, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &city_codes);
void noUnnecessaryMaxFlow(Graph<string> &g, string code, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &city_codes);
#endif //DA_PROJETO1_UTILS_H
