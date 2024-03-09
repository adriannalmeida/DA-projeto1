#include "Utils.h"


void calculateReceivedSupply(Graph<string> &g,unordered_map<string, City> &city_codes){
    for (auto v : g.getVertexSet()) {
        if(v->getInfo()[0] == 'C'){
            double res = 0;
            for(auto e : v->getIncoming()){
                res += e->getFlow();
            }
            city_codes[v->getInfo()].setReceived(res);
        }
    }
}

void printNotFullySuppliedCities(unordered_map<string, City> &city_codes, set<string> &c_set){

        bool printColumnNames = 0;
        //imprime os pares ordered
        for (auto code : c_set) {
            auto c = city_codes[code];
            if (c.getReceived() < c.getDemand()) {
                if (!printColumnNames) {
                    cout << "City Code" << '\t' << "Deficit";
                    printColumnNames = 1;
                }
                cout << c.getCode() << '\t' << (c.getDemand() - c.getReceived());
            }
        }
        if (!printColumnNames) cout << "All cities receive full demand!";
}