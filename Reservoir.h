//
// Created by marta on 05/03/2024.
//

#ifndef DA_PROJETO1_RESERVOIR_H
#define DA_PROJETO1_RESERVOIR_H
#include <string>
using namespace std;

class Reservoir {
    string reservoir;
    string municipality;
    string code;
    int id;
    int maxDelivery;

public:
    Reservoir(string reservoir_, string municipality_, string code, int id_, int maxDelivery_ );
    Reservoir();
    string getReservoir() const;
    string getMunicipality() const;
    string getCode()const;
    int getId() const;
    int getMaxDelivery() const;
};


#endif //DA_PROJETO1_RESERVOIR_H
