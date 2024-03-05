#include "Pipes.h"
Pipes:: Pipes(string A, string B, int capacity,int direction){
    this->sPointA = A;
    this->sPointB = B;
    this->capacity = capacity;
    this->direction = direction;
}

string Pipes::getPointA(){
    return this->sPointA;
}

string Pipes::getPointB() {
    return this->sPointB;
}

int Pipes::getCapacity(){
    return this->capacity;
}

int Pipes::getDirection(){
    return this->direction;
}
