#ifndef DA_PROJETO1_CITY_H
#define DA_PROJETO1_CITY_H

#include <string>
using namespace std;

/**
 * @brief Represents a City entity.
 *
 * This class provides a representation for a City, including attributes such as
 * name, unique identifier, code, demand, and population.
 */
class City {
    std::string city; /**< The name of the city. */
    int id; /**< The unique identifier of the city. */
    std::string code; /**< The code of the city. */
    double demand; /**< The demand of the city. */
    long int population; /**< The population of the city. */

public:
    /**
     * @brief Default constructor.
     */
    City();

    /**
     * @brief Parameterized constructor.
     *
     * @param city The name of the city.
     * @param id The unique identifier of the city.
     * @param code The code of the city.
     * @param demand The demand of the city.
     * @param population The population of the city.
     */
    City(std::string city, int id, std::string code, double demand, long population);

    /**
     * @brief Getter method for retrieving the name of the city.
     *
     * @return The name of the city.
     */
    std::string getCity() const;

    /**
     * @brief Getter method for retrieving the unique identifier of the city.
     *
     * @return The unique identifier of the city.
     */
    int getId() const;

    /**
     * @brief Getter method for retrieving the code of the city.
     *
     * @return The code of the city.
     */
    std::string getCode() const;

    /**
     * @brief Getter method for retrieving the demand of the city.
     *
     * @return The demand of the city.
     */
    double getDemand() const;

    /**
     * @brief Getter method for retrieving the population of the city.
     *
     * @return The population of the city.
     */
    long getPopulation() const;
};

#endif //DA_PROJETO1_CITY_H
