#ifndef DA_PROJETO1_STATION_H
#define DA_PROJETO1_STATION_H

#include <string>

using namespace std;

/**
 * @brief Represents a Station entity.
 *
 * This class provides a representation for a Station, including attributes such as
 * unique identifier and code.
 */
class Station {
public:
    /**
     * @brief Default constructor.
     */
    Station();

    /**
     * @brief Parameterized constructor.
     *
     * @param id The unique identifier of the station.
     * @param code The code of the station.
     */
    Station(int id, std::string code);

    /**
     * @brief Getter method for retrieving the unique identifier of the station.
     *
     * @return The unique identifier of the station.
     */
    int getId() const;

    /**
     * @brief Getter method for retrieving the code of the station.
     *
     * @return The code of the station.
     */
    std::string getCode() const;

private:
    int id; /**< The unique identifier of the station. */
    std::string code; /**< The code of the station. */
};


#endif //DA_PROJETO1_STATION_H
