#include "DataParser.h"

void ReservoirParser(string path, Graph<string> &g, unordered_map<string, Reservoir> &ht){
    ifstream csv(path);
    if(!csv.is_open()){
        cerr << "Error opening flights.csv" << endl;
        return;
    }
    string line;
    getline(csv, line, '\n');

    while(getline(csv, line, '\n')){
        string r, m, c, id, mdelivery;
        stringstream s(line);

        getline(s, r, ',');
        getline(s, m, ',');
        getline(s, id, ',');
        getline(s, c, ',');
        getline(s, mdelivery, ',');

        Reservoir R = Reservoir(r,m,c,stoi(id),stoi(mdelivery));
        g.addVertex(c);
        ht.emplace(c, R);
    }

}