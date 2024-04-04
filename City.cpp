#include "City.h"

City::City(){}
City::City(string city, int id, string code, double demand, long population){
    this->city = city;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population= population;
};

string City::getCity() const{
    return this->city;
}
int City::getId() const{
    return this->id;
}
string City::getCode() const{
    return this->code;
}
double City::getDemand() const{
    return this->demand;
}
long City::getPopulation() const{
    return this->population;
}