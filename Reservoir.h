//
// Created by marta on 05/03/2024.
//

#ifndef DA_PROJETO1_RESERVOIR_H
#define DA_PROJETO1_RESERVOIR_H

#include <string>

using namespace std;
/**
 * @brief Represents a Reservoir entity.
 *
 * This class provides a representation for a Reservoir, including attributes such as
 * reservoir name, municipality, code, unique identifier, and maximum delivery capacity.
 */
class Reservoir {
public:
    /**
     * @brief Default constructor.
     */
    Reservoir();

    /**
     * @brief Parameterized constructor.
     *
     * @param reservoir_ The name of the reservoir.
     * @param municipality_ The municipality where the reservoir is located.
     * @param code The code of the reservoir.
     * @param id_ The unique identifier of the reservoir.
     * @param maxDelivery_ The maximum delivery capacity of the reservoir.
     */
    Reservoir(std::string reservoir_, std::string municipality_, std::string code, int id_, int maxDelivery_);

    /**
     * @brief Getter method for retrieving the reservoir name.
     *
     * @return The name of the reservoir.
     */
    std::string getReservoir() const;

    /**
     * @brief Getter method for retrieving the municipality where the reservoir is located.
     *
     * @return The municipality of the reservoir.
     */
    std::string getMunicipality() const;

    /**
     * @brief Getter method for retrieving the code of the reservoir.
     *
     * @return The code of the reservoir.
     */
    std::string getCode() const;

    /**
     * @brief Getter method for retrieving the unique identifier of the reservoir.
     *
     * @return The unique identifier of the reservoir.
     */
    int getId() const;

    /**
     * @brief Getter method for retrieving the maximum delivery capacity of the reservoir.
     *
     * @return The maximum delivery capacity of the reservoir.
     */
    int getMaxDelivery() const;

private:
    std::string reservoir; /**< The name of the reservoir. */
    std::string municipality; /**< The municipality where the reservoir is located. */
    std::string code; /**< The code of the reservoir. */
    int id; /**< The unique identifier of the reservoir. */
    int maxDelivery; /**< The maximum delivery capacity of the reservoir. */
};




#endif //DA_PROJETO1_RESERVOIR_H
