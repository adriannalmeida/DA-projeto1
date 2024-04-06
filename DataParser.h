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
#include "Station.h"
#include "City.h"
using namespace std;
/**
 * @file DataParser.h
 * @brief Functions for parsing the given data from CSV Files.
 */

/**
 * @brief Parses the Reservoir data from a CSV file and populates a graph and a hash table.
 *
 * This function reads the Reservoir data from the specified CSV file and populates a graph
 * representing the network and a hash table mapping reservoir codes to Reservoir objects.
 * It adds vertices to the graph for each reservoir and stores corresponding Reservoir objects
 * in the hash table.
 *
 * @param path The file path of the CSV file containing the Reservoir data.
 * @param g The graph representing the network.
 * @param ht The hash table mapping reservoir codes to Reservoir objects.
 */
void ReservoirParser(string path, Graph<string> &g, unordered_map<string, Reservoir> &ht);

/**
 * @brief Parses the Station data from a CSV file and populates a graph and a hash table.
 *
 * This function reads the Station data from the specified CSV file and populates a graph
 * representing the network and a hash table mapping station codes to Station objects.
 * It adds vertices to the graph for each station and stores corresponding Station objects
 * in the hash table.
 *
 * @param path The file path of the CSV file containing the Station data.
 * @param g The graph representing the network.
 * @param ht The hash table mapping station codes to Station objects.
 */
void StationParser(string path, Graph<string> &g, unordered_map<string, Station> &ht);

/**
 * @brief Parses the City data from a CSV file and populates a graph and a hash table.
 *
 * This function reads the City data from the specified CSV file and populates a graph
 * representing the network and a hash table mapping city codes to City objects.
 * It adds vertices to the graph for each city and stores corresponding City objects
 * in the hash table.
 *
 * @param path The file path of the CSV file containing the City data.
 * @param g The graph representing the network.
 * @param ht The hash table mapping city codes to City objects.
 * @param s The region identifier, specifies the data to parse.
 */
void CityParser(string path, Graph<string> &g, unordered_map<string, City> &ht, string s);

/**
 * @brief Parses the Pipes data from a CSV file and populates a graph.
 *
 * This function reads the Pipes data from the specified CSV file and populates a graph
 * representing the network. It adds edges to the graph for each pipe, considering whether
 * the pipe is bidirectional or unidirectional.
 *
 * @param path The file path of the CSV file containing the Pipes data.
 * @param g The graph representing the network.
 */
void PipesParser(string path, Graph<string> &g);

#endif //PROJETO1_DATAPARSER_H
