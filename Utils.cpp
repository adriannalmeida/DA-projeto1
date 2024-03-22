#include "Utils.h"
#include "data_structures/graph.h"
#include <iostream>
using namespace std;

int calculateReceivedSupply(Graph<string> &g,unordered_map<string, City> &city_codes){
    int notSupplied = 0;
    for(auto p:city_codes){
        p.second.setReceived(0);
    }
    for(auto p : city_codes){
        p.second.setReceived(0);
    }
    for (auto v : g.getVertexSet()) {
        if(v->getInfo()[0] == 'C'){
            double res = 0;
            for(auto e : v->getIncoming()){
                res += e->getFlow();
            }
            city_codes[v->getInfo()].setReceived(res);
            if(res < city_codes[v->getInfo()].getDemand()){
                notSupplied++;
            }
        }
    }
    return notSupplied;
}


void printNotFullySuppliedCities(Graph<string> &g, unordered_map<string, City> &city_codes){
    bool printColumnNames = 0;
    for (auto v : g.getVertexSet()) {
        string code = v->getInfo();
        if(code[0] == 'C'){
            auto c = city_codes[code];
            if (c.getReceived() < c.getDemand()) {
                if (!printColumnNames) {
                    cout << "City Code" << '\t' << "Deficit" << endl;
                    printColumnNames = 1;
                }
                cout << c.getCode() << "\t      " << (c.getDemand() - c.getReceived()) << "\tDemand is: \t      " << c.getDemand() << "\tReceived is: \t      " << c.getReceived() <<endl;
            }
        }
        else{
            if(code[0] == 'P') break;
        }
    }
    if (!printColumnNames) cout << "All cities receive full demand!"<<endl;
    cout << endl;
}


// Max Flow


void testAndVisit(queue<Vertex<string>*> &q, Edge<string>* e, Vertex<string>* v, double r ){
    if(!v->isVisited() && r > 0 ){
        v->setVisited(true);
        v->setPath(e);
        q.push(v);
    }
}

bool findPath(Graph<string>& g, Vertex<string>*s, Vertex<string>*d){
    for(auto v: g.getVertexSet()){
        v->setVisited(false);
    }

    s->setVisited(true);
    queue<Vertex<string>*> q;
    q.push(s);

    while(!q.empty() && !d->isVisited()){
        auto current= q.front();
        q.pop();

        for(auto edge: current->getAdj()){
            testAndVisit(q, edge, edge->getDest(), edge->getWeight() - edge->getFlow());
        }

        for(auto edge: current->getIncoming()){
            testAndVisit(q, edge, edge->getOrig(), edge->getFlow());
        }
    }

    return d->isVisited();
}

double minResidual(Vertex<string>* s, Vertex<string>* d){
    double minFlow=INF;
    auto current=d;

    while(current!=s){
        auto edge=current->getPath();

        if(edge->getDest()==current){
            minFlow=min(minFlow, edge->getWeight() - edge->getFlow());
            current=edge->getOrig();
        }

        else{
            minFlow=min(minFlow, edge->getFlow());
            current=edge->getDest();
        }
    }

    return minFlow;
}

void setFlowPath (Vertex<string>* s, Vertex<string>* d, double flow){
    auto current = d;

    while(current!=s){
        auto edge= current->getPath();

        if(edge->getDest()==current){
            edge->setFlow(edge->getFlow() + flow);
            current=edge->getOrig();
        }
        else{
            edge->setFlow(edge->getFlow() - flow);
            current=edge->getDest();
        }
    }
}

vector<pair<string, double>> maxFlow(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
    g.addVertex("source");
    g.addVertex("sink");
    Vertex<string>* src;
    Vertex<string>* snk;
    for (auto v : g.getVertexSet()) {
        if(v->getInfo()[0] == 'R'){
            auto reservoir=reservoirs_codes[v->getInfo()];
            g.addEdge("source", v->getInfo(), reservoir.getMaxDelivery());
        }
        if(v->getInfo()[0]=='C'){
            auto city = cities_codes[v->getInfo()];
            g.addEdge(v->getInfo(), "sink", INF);
        }
        if(v->getInfo() == "source"){
            src=v;
        }
        if(v->getInfo() == "sink"){
            snk=v;
        }
    }
    //testar
    /*for(auto v:g.getVertexSet()){
        if(v->getInfo()=="source"){
            for(auto edge: v->getAdj()){
                auto reservoir=reservoirs_codes[edge->getDest()->getInfo()];
                cout << v->getInfo() << "---->" << edge->getDest()->getInfo()<< "->" << edge->getWeight()<< "->" <<reservoir.getMaxDelivery()<<endl;
            }
        }
    }*/

    /*for(auto v:g.getVertexSet()){
        if(v->getInfo()[0]=='C'){
            for(auto edge: v->getAdj()){
                auto city=cities_codes[v->getInfo()];
                cout << v->getInfo() << "---->" << edge->getDest()->getInfo();
            }
        }
    }*/
    // acabou testar


    /*vector<Vertex<string>*> destinations;
    for(auto v: g.getVertexSet()){
        if(v->getInfo()[0] == 'C'){
            destinations.push_back(v);
        }
    }*/

    if(src==snk){cout<< "Invalid";}

    vector<pair<string, double>> res;
    //for(auto dest: destinations){
    //cout << src->getInfo() << "---->" << v->getInfo()<<endl;
    for(auto v: g.getVertexSet()){
        for(auto edge: v->getAdj()){
            edge->setFlow(0);
        }
    }

    //double maxFlow=0;
    while(findPath(g, src, snk)){
        double f= minResidual(src, snk);
        setFlowPath(src, snk, f);
        //maxFlow+=f;
    }
    /*Vertex<string>* currentV=dest;
    double maxFlow=0;
    while (currentV->getInfo() != src->getInfo()){
        maxFlow+=currentV->getPath()->getFlow();
        currentV=currentV->getPath()->getOrig();
    }*/
    /*double maxFlow=0;
    for(auto v: g.getVertexSet()){
        for(auto edge: v->getAdj()){
            if(edge->getDest()==dest){
                maxFlow+=edge->getFlow();
            }
        }
    }*/

    for(auto v: g.getVertexSet()){
        if(v->getInfo()[0]=='C'){
            for(auto edge: v->getAdj()){
                if(edge->getDest()->getInfo()=="sink"){
                    res.push_back(make_pair(v->getInfo(), edge->getFlow()));
                }
            }
        }
    }

    //res.push_back(make_pair(dest->getInfo(), maxFlow));

    //cout << dest->getInfo() <<": " << maxFlow<<endl;

    return res;
}

void chooseCityByName(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, string city){
    vector<pair<string, double>> flows = maxFlow(g, reservoirs_codes, cities_codes);
    if(city=="none"){
        for(auto c: flows){
            cout << c.first << ": "<< c.second<<endl;
        }
    }
    else {
        string code="";
        for (auto c: cities_codes) {
            if (c.second.getCity() == city) {
                code = c.first;
            }
        }
        if(code==""){
            cout<< "City doesn´t exist"<<endl;
        }
            //cout << code;
        else {
            for (auto ci: flows) {
                if (ci.first == code) {
                    cout << city << ": " << ci.second;
                }
            }
        }
    }

}

void chooseCityByCode(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, string code){
    vector<pair<string, double>> flows = maxFlow(g, reservoirs_codes, cities_codes);
    if(code=="none"){
        for(auto c: flows){
            cout << c.first << ": "<< c.second<<endl;
        }
    }
    else {
        bool c=false;
        for (auto co: flows) {
            if (co.first == code) {
                cout << code << ": " << co.second;
                c=true;
            }
        }
        if(!c){
            cout<< "City doesn´t exist"<<endl;
        }

    }

}

void chooseFailingReservoir(Graph<string> g, string code, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &city_codes){


    int before, after;
    maxFlow(g, reservoirs_codes, city_codes);
    before = calculateReceivedSupply(g, city_codes);

    try {
        Reservoir R = reservoirs_codes.at(code);
    } catch (const std::out_of_range& e) {
        cout << "Reservoir does not exist!: " << endl;
        return;
    }
    cout << "When every Reservoir was functioning, " << before << " city(ies) were not receiving the needed supply." <<endl;
    printNotFullySuppliedCities(g, city_codes);
    g.removeVertex(code);

    maxFlow(g, reservoirs_codes, city_codes);

    after = calculateReceivedSupply(g, city_codes);
    cout << "Now, " << after - before << " more cities are not sufficiently supplied. \nAll of them are listed below." << endl <<endl;
    printNotFullySuppliedCities(g, city_codes);
}

//3.2
void chooseFailingPumpingStation(Graph<string> g, string code, unordered_map<string, Station> &ps_codes, unordered_map<string, City> &city_codes){
    try {
        Station S = ps_codes.at(code);
    } catch (const std::out_of_range& e) {
        cout << "Station does not exist!: " << endl;
        return;
        //OU cout << "Do you want to try again?\nYes\nNo";´
        //ver como funciona o menu aqui. ver se ter os set faz sentido
        //pus g passado por valor por referencia nas funcoes que ela chama.
        //medir a complexidade para ver se é melhor só readicionar o vértice no fim.
    }

}