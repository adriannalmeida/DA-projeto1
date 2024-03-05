//
// Created by marta on 05/03/2024.
//

#include "Station.h"

Station::Station(int id_, string code_):
    id(id_), code(code_) {}

int Station::getId() const {return id;}

string Station::getCode() const {return code;}