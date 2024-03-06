//
// Created by marta on 05/03/2024.
//

#include "Reservoir.h"

Reservoir::Reservoir(string reservoir_, string municipality_, string code, int id_, int maxDelivery_):
    reservoir(reservoir_), municipality(municipality_), code(code),id(id_), maxDelivery(maxDelivery_){}

string Reservoir::getReservoir() const {return reservoir;}
string Reservoir::getMunicipality() const {return municipality;}
string Reservoir::getCode()const{return code;}
int Reservoir::getId() const {return id;}
int Reservoir::getMaxDelivery() const {return maxDelivery;}