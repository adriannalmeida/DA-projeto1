#include "DataParser.h"
#include "data_structures/graph.h"

int main(){
    unordered_map<string, Reservoir> reservoirs_code;
    unordered_map<string, City> cities_code;
    unordered_map<string, Station> stations_code;
    Graph<string> g;
    string path_reser = "../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv";
    string path_station = "../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv";
    string path_cities = "../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv";
    ReservoirParser(path_reser, g, reservoirs_code);
    CityParser(path_cities,g, cities_code);
    StationParser(path_station,g, stations_code);

    for(auto x : g.getVertexSet()){
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

    }

}

