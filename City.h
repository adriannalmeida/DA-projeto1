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
    double received;

public:
    City();
    City(string city, int id, string code, double demand, long population);
    string getCity() const;
    int getId() const;
    string getCode() const;
    double getDemand() const;
    long getPopulation() const;
    double getReceived() const;
    void setReceived(double amount);
};


#endif //PROJETO1_CITY_H
