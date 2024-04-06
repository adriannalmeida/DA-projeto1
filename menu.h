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

/**
 * @brief Represents a menu for interacting with the network system.
 *
 * This class provides various menu options for interacting with the network system,
 * including options for displaying metrics, handling maximum flow, choosing cities,
 * managing failures, handling pumping stations, managing pipelines, and continuing operations.
 */
class Menu {
public:
    /**
     * @brief Opens the main menu.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void openMenu(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Displays initial menu options.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void initialOptions(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Closes the menu.
     *
     * @return An integer indicating the menu closure.
     */
    static int closeMenu();

    /**
     * @brief Displays metrics menu options.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void metrics(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Displays maximum flow menu options.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void maxFlowMenu(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Allows choosing a city from the network.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void chooseCity(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Information about flow changes due to failures in the network.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void failures(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Allows for the consultation of pumping stations in the network.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void pumpingStations(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Opens pipeline menu.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void pipelines(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);

    /**
     * @brief Resets menu state back to network operations.
     *
     * @param g The graph representing the network.
     * @param cities The map of city codes to City objects.
     * @param reservoirs The map of reservoir codes to Reservoir objects.
     * @param stations The map of station codes to Station objects.
     */
    static void continueM(Graph<string> g, unordered_map<string, City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations);
};

#endif //PROJETO1_MENU_H
