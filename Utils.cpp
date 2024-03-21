#include "Utils.h"
#include "data_structures/graph.h"
#include <iostream>
using namespace std;

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

vector<pair<string, double>> maxFlow(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
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
            g.addEdge(v->getInfo(), "sink", city.getDemand());
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
        int sumFlow=0;
        if(v->getInfo()[0]=='C'){
            for(auto edge: v->getIncoming()){
                sumFlow+=edge->getFlow();
                //if(edge->getDest()->getInfo()=="sink"){
                    //res.push_back(make_pair(v->getInfo(), edge->getFlow()));
                //}
            }
            res.push_back(make_pair(v->getInfo(), sumFlow));
        }
    }

        //res.push_back(make_pair(dest->getInfo(), maxFlow));

        //cout << dest->getInfo() <<": " << maxFlow<<endl;
    g.removeVertex("source");
    g.removeVertex("sink");
    return res;
}

void chooseCityByName(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, string city){
    vector<pair<string, double>> flows = maxFlow(g, reservoirs_codes, cities_codes);
    int sum=0;
    if(city=="none"){
        for(auto c: flows){
            cout << c.first << ": "<< c.second<<endl;
            sum+=c.second;
        }
        cout<<"max flow: "<<sum<<endl;
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

void removePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code, unordered_map<string, Reservoir> &reservoirs_code){

    std::vector<Vertex<string>*> stations;
    for(auto v: g.getVertexSet()){
        if(v->getInfo()[0]=='P'){
            stations.push_back(v);
        }
    }

    vector<pair<string, double>> maxiFlow = maxFlow(g, reservoirs_code, cities_codes);


    for(auto s: stations){

        vector<pair<Vertex<string>*, double>> outcomingEdges;
        vector<pair<Vertex<string>*, double>> incomingEdges;
        for(auto edge: s->getAdj()){
            outcomingEdges.push_back(make_pair(edge->getDest(), edge->getWeight()));
        }
        for(auto edge: s->getIncoming()){
            incomingEdges.push_back(make_pair(edge->getOrig(), edge->getWeight()));
        }

        string info=s->getInfo();
        g.removeVertex(s->getInfo());

        vector<pair<string, double>> currentFlow = maxFlow(g, reservoirs_code, cities_codes);

        //testar
        /*int n=currentFlow.size();
        int a=maxiFlow.size();
        cout <<n << endl;
        cout <<a <<endl;
        for(auto w: currentFlow){
            cout<< w.first<< "---->" <<w.second<<endl;
        }*/

        g.addVertex(info);

        for(auto edge: outcomingEdges){
            g.addEdge(info, edge.first->getInfo(), edge.second);
        }
        
        for(auto edge: incomingEdges){
            g.addEdge(edge.first->getInfo(), info, edge.second);
        }

        int n=maxiFlow.size();
        bool affected=false;

        cout << "Affected cities by " << info<<": "<<endl;
        for(int i=0; i<n; i++){

            if(maxiFlow[i].second != currentFlow[i].second){
                affected=true;
                int dif=maxiFlow[i].second - currentFlow[i].second;
                cout << maxiFlow[i].first << "---->" << dif <<endl;
            }

        }
        if(!affected){
            cout << "No cities affected"<< endl;
        }
    }

}