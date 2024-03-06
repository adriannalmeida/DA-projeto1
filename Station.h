//
// Created by marta on 05/03/2024.
//

#ifndef DA_PROJETO1_STATION_H
#define DA_PROJETO1_STATION_H
#include <string>
using namespace std;

class Station {
    int id;
    string code;

public:
    Station();
    Station(int id_, string code_);
    int getId() const;
    string getCode() const;
};



#endif //DA_PROJETO1_STATION_H
