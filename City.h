#ifndef PROJETO1_CITY_H
#define PROJETO1_CITY_H

#include <string>
using namespace std;
class City {
    string city;
    int id;
    string code;
    double demand;
    long int population;

public:
    City();
    City(string city, int id, string code, double demand, long population);
    string getCity();
    int getId();
    string getCode();
    double getDemand();
    long getPopulation();
};


#endif //PROJETO1_CITY_H
