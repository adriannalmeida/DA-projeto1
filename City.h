#ifndef PROJETO1_CITY_H
#define PROJETO1_CITY_H

#include <string>
using namespace std;
class City {
    string city;
    int id;
    string code;
    int demand;
    long int population;

public:
    City(string city, int id, string code, int demand, long int population);
    string getCity();
    int getId();
    string getCode();
    int getDemand();
    long int getPopulation();
};


#endif //PROJETO1_CITY_H
