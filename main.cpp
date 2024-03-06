#include "DataParser.h"
#include "data_structures/graph.h"

int main(){
    unordered_map<string, Reservoir> reservoirs_code;
    Graph<string> g;
    string path = "../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv";
    ReservoirParser(path, g, reservoirs_code);

    for(auto x: g.getVertexSet()){
        auto info = x->getInfo();
        Reservoir r;
        r = reservoirs_code[info];
        cout << r.getReservoir() << endl;
    }

}

