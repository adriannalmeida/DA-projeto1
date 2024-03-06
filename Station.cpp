#include "Station.h"

Station::Station(){}
Station::Station(int id_, string code_):
    id(id_), code(code_) {}

int Station::getId() const {return id;}

string Station::getCode() const {return code;}