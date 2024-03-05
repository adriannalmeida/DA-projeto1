#include "City.h"


City::City(string city, int id, string code, int demand, long int population){
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
int City::getDemand() {
    return this->demand;
}
long int City::getPopulation() {
    return this->population;
}
