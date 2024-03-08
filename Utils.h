//
// Created by saracortez on 08/03/24.
//

#ifndef DA_PROJETO1_UTILS_H
#define DA_PROJETO1_UTILS_H

#include "DataParser.h"

//void Edmonds-Karp()
void calculateReceivedSupply(unordered_map<string, City> &city_codes);
void printNotFullySuppliedCities(unordered_map<string, City> &city_codes);

#endif //DA_PROJETO1_UTILS_H
