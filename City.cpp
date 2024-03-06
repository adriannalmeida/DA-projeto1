#include "City.h"

City::City(){}
City::City(string city, int id, string code, double demand, long population){
    this->city = city;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population= population;
};

string City::getCity() {
    return this->city;
}
int City::getId() {
    return this->id;
}
string City::getCode() {
    return this->code;
}
double City::getDemand() {
    return this->demand;
}
long City::getPopulation() {
    return this->population;
}
