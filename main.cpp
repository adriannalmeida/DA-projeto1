#include "DataParser.h"
#include "data_structures/graph.h"
#include "Utils.h"

using namespace std;
int main() {
    unordered_map<string, Reservoir> reservoirs_code;
    unordered_map<string, City> cities_code;
    unordered_map<string, Station> stations_code;
    set<string> r_set, s_set, c_set;
    Graph<string> g;
/*
    string path_reser = "../Project1LargeDataSet/Project1LargeDataSet/Reservoir.csv";
    string path_station = "../Project1LargeDataSet/Project1LargeDataSet/Stations.csv";
    string path_cities = "../Project1LargeDataSet/Project1LargeDataSet/Cities.csv";
    string path_pipes = "../Project1LargeDataSet/Project1LargeDataSet/Pipes.csv";
    */
    string path_reser = "../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv";
    string path_station = "../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv";
    string path_cities = "../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv";
    string path_pipes = "../Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv";

    ReservoirParser(path_reser, g, reservoirs_code);
    CityParser(path_cities, g, cities_code);
    StationParser(path_station, g, stations_code);
    PipesParser(path_pipes, g);

    /*for(auto x : g.getVertexSet()){
        auto info = x->getInfo();
        switch (info[0]) {
            case 'R':{
                Reservoir r;
                r = reservoirs_code[info];
                cout << r.getReservoir() << endl;
                break;
            }
            case 'P':{
                Station s;
                s = stations_code[info];
                //wtf esta a a printar uma linha a mais ...?
                cout << s.getCode()<<endl;
            }
            case 'C':{
                City c;
                c = cities_code[info];
                cout << c.getCity()<< endl;
            }
        }

    }*/

    /*for (auto v: g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            cout << e->getOrig()->getInfo() << "----->" << e->getDest()->getInfo() << endl;
        }
    }*/
    //t2.2
/*
    auto res = maxFlow(g, reservoirs_code, cities_code);
    for(auto e : res){
        cout << '{'<< e.first << ", " << e.second<<'}'<<endl;
    }
    for(auto v: g.getVertexSet()){
        for(auto e:v->getAdj()){
            cout << "Edge flow: " << e->getFlow() <<endl;
        }
    }*/
/*
    cout << "Not supplied cities: "<< calculateReceivedSupply(g,cities_code) << endl;
    printNotFullySuppliedCities(g, cities_code);*/
    chooseFailingReservoir(g, "R_1", reservoirs_code, cities_code);
    //maxFlow
    //maxFlow(g, reservoirs_code);
    //chooseCityByName(g, reservoirs_code, cities_code, "Coimbra");

    //maxFlow(g, reservoirs_code, cities_code);
}

