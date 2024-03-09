#ifndef PROJETO1_DATAPARSER_H
#define PROJETO1_DATAPARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "Reservoir.h"
#include "data_structures/graph.h"
#include <unordered_map>
#include <set>
#include "Station.h"
#include "City.h"
using namespace std;

void ReservoirParser(string path, Graph<string> &g, unordered_map<string, Reservoir> &ht, set<string> r_set);
void StationParser(string path, Graph<string> &g, unordered_map<string, Station> &ht, set<string> s_set);
void CityParser(string path, Graph<string> &g, unordered_map<string, City> &ht, set<string> c_set);
void PipesParser(string path, Graph<string> &g);

#endif //PROJETO1_DATAPARSER_H
