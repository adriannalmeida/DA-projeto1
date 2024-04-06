#ifndef PROJETO1_MENU_H
#define PROJETO1_MENU_H
#include <iostream>
#include "DataParser.h"
#include <vector>
#include <set>
#include <unordered_map>
#include <unistd.h>

#include <algorithm>
#include <unordered_set>
#include <cmath>
#include <cctype>
#include <iomanip>
#include "Utils.h"
using namespace std;
class Menu{
public:
    static void openMenu(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static void initialOptions(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static int closeMenu();
    static void metrics(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static void maxFlowMenu(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static void chooseCity(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static void failures(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static void pumpingStations(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static void pipelines(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
    static void continueM(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);



};
#endif //PROJETO1_MENU_H

