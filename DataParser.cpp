#include "DataParser.h"

void ReservoirParser(string path, Graph<string> &g, unordered_map<string, Reservoir> &ht){
    ifstream csv(path);

    if(!csv.is_open()){
        cerr << "Error opening Reservoir.csv" << endl;
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

void StationParser(string path, Graph<string> &g, unordered_map<string, Station> &ht) {
    ifstream csv(path);
    if (!csv.is_open()) {
        cerr << "Error opening Stations.csv" << endl;
        return;
    }
    string line;
    getline(csv, line, '\n');

    while (getline(csv, line, '\n')) {
        string id, code;
        stringstream ss(line);

        getline(ss, id, ',');
        getline(ss, code, ',');

        Station S = Station(stoi(id), code);
        g.addVertex(code);
        ht.emplace(code, S);
    }
}

void CityParser(string path, Graph<string> &g, unordered_map<string, City> &ht) {
    ifstream csv(path);
    if (!csv.is_open()) {
        cerr << "Error opening Cities.csv" << endl;
        return;
    }
    string line;
    getline(csv, line, '\n');

    while (getline(csv, line, '\n')) {
        string city, id, code, demand, population;
        stringstream ss(line);

        getline(ss, city, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, demand, ',');
        getline(ss, population, ',');

        City C = City(city, stoi(id), code, stoi(demand), stol(population));
        g.addVertex(code);
        ht.emplace(code, C);
    }
}

//FALTA TESTAR PARSER DE CITY E DE STATION!!!

/*
    void PipesParser(string path, Graph<string> &g, unordered_map<string, Pipes> &ht){
        ifstream csv(path);
        if(!csv.is_open()){
            cerr << "Error opening Pipes.csv" << endl;
            return;
        }
        string line;
        getline(csv, line, '\n');

        while(getline(csv, line, '\n')){
            string A, B, cap, dir;
            stringstream ss(line);

            getline(ss, A, ',');
            getline(ss, B, ',');
            getline(ss, cap, ',');
            getline(ss, dir, ',');

            Pipes P = Pipes(A,B, cap, dir);
        }
*/
