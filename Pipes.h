#ifndef PROJETO1_PIPES_H
#define PROJETO1_PIPES_H

#include <string>
using namespace std;
class Pipes {
    string sPointA;
    string sPointB;
    int capacity;
    //direction = 1 é unidirecional; se direction = 0 é bidirecional
    int direction;

public:
    Pipes(string A, string B, int capacity,int direction);
    string getPointA();
    string getPointB();
    int getCapacity();
    int getDirection();
};


#endif //PROJETO1_PIPES_H
