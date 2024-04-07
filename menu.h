#ifndef PROJETO1_MENU_H
#define PROJETO1_MENU_H

#include "Utils.h"
#include "DataParser.h"

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
    * @brief Unordered map storing information about reservoirs.
    *
    * This unordered map stores the object of class Reservoir. Each reservoir is associated with its unique code.
    */
    unordered_map<string, Reservoir> reservoirs;

    /**
    * @brief Unordered map storing information about cities.
    *
    * This unordered map stores the object of class City. Each city is associated with its unique code.
    */
    unordered_map<string, City> cities;

    /**
    * @brief Unordered map storing information about stations.
    *
    * This unordered map stores the object of class Station. Each station is associated with its unique code.
    */
    unordered_map<string, Station> stations;

    /**
    * @brief Graph representing the network infrastructure.
    */
    Graph<string> g;


    /**
    * @brief Default constructor for the Menu class.
    */
    Menu();

    /**
    * @brief Allows user to choose a region and performs corresponding actions.
    *
    * This function displays a menu where the a network is chosen. Validates the
    * input and performs actions based on the selected option.
    */
    void chooseRegion();

    /**
    * @brief Builds the graph based on the specified region.
    *
    * This function Idetermines the file paths for reservoirs,
    * stations, cities, and pipes data based on the input region.
    * Then, it calls the corresponding parser functions to populate the graph with data.
    *
    * @param s A string representing the region for which the graph is to be built.
    *          Valid values are 'Portugal' or 'Madeira'.
    */
    void buildGraph(string s);

    /**
    * @brief Opens the menu and displays a welcome message.
    *
    * This function also calls the `chooseRegion()` function
    */
    void openMenu();

    /**
    * @brief Waits for user input before continuing.
    *
    * This function clears the input buffer to prevent any remaining
    * input from affecting it. After receiving the
    * ENTER key press, it calls the `continueM()` function.
    */
    void wait();

    /**
    * @brief Presents initial menu options and performs corresponding actions.
    *
    * This function displays a menu with initial options for consultation.
    * Validates the input and performs actions based on the selected option.
    */
    void initialOptions();

    /**
    * @brief Closes the menu.
    * @return An integer value indicating the success of closing the menu.
    */
    int closeMenu();

    /**
    * @brief Provides options for consulting different metrics related to the network.
    *
    * This function presents a menu with options to consult various metrics.
    * Validates the input and performs actions based on the selected option.
    */
    void metrics();

    /**
    * @brief Provides options for consulting maximum flow information.
    *
    * This function presents a menu with options to consult different information about the maxflow.
    * Validates the input and performs actions based on the selected option.
    */
    void maxFlowMenu();

    /**
    * @brief Provides options for specifying a city and consults maximum flow information.
    *
    * This function presents a menu with options to specify a city in order to consult maximum flow information for that city.
    *  Validates  the input and performs actions based on the selected option.
    */
    void chooseCity();

    /**
    * @brief Provides options for simulating failures in the network components.
    *
    * This function presents a menu with options to simulate failures in different network components.
    * Validates the input and performs actions based on the selected option.
    */
    void failures();

    /**
    * @brief Provides options for the removal of pumping Stations in the network.
    *
    * This function presents a menu with options to remove different number of pumping stations.
    * Validates the input and performs actions based on the selected option.
     */
    void pumpingStations();

    /**
    * @brief Provides options for failures in pipelines and its relevance in the network flow.
    *
    * This function presents a menu with options to determined failures in pipelines
    * and presents the impact of those failures
    * Validates the input and performs actions based on the selected option.
    */
    void pipelines();

    /**
    * @brief Provides options to continue searching or quit the menu.
    *
    * This function presents a menu with options to either go back to the main menu or quit the program.
    * Validates the input and performs actions based on the selected option.
    */
    void continueM();
};

#endif //PROJETO1_MENU_H
