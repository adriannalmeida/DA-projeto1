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

vector<pair<string, double>> maxFlow(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes){
    g.addVertex("source");
    Vertex<string>* src;
    for (auto v : g.getVertexSet()) {
        if(v->getInfo()[0] == 'R'){
            auto reservoir=reservoirs_codes[v->getInfo()];
            g.addEdge("source", v->getInfo(), reservoir.getMaxDelivery());
        }
        if(v->getInfo() == "source"){
            src=v;
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
    vector<Vertex<string>*> destinations;
    for(auto v: g.getVertexSet()){
        if(v->getInfo()[0] == 'C'){
            destinations.push_back(v);
        }
    }


    vector<pair<string, double>> res;
    for(auto dest: destinations){
        //cout << src->getInfo() << "---->" << v->getInfo()<<endl;
        for(auto v: g.getVertexSet()){
            for(auto edge: v->getAdj()){
                edge->setFlow(0);
            }
        }

        double maxFlow=0;
        while(findPath(g, src, dest)){
            double f= minResidual(src, dest);
            setFlowPath(src, dest, f);
            maxFlow+=f;
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
        res.push_back(make_pair(dest->getInfo(), maxFlow));

        //cout << dest->getInfo() <<": " << maxFlow<<endl;
    }
    return res;
}

void chooseCity(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, string city){
    vector<pair<string, double>> flows = maxFlow(g, reservoirs_codes);
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


// minimize the differences of flow to capacity

void minDiffFlowCapacity(Graph<string> &g){
    // metrics
    // esta função tem de chamar o max flow ou só ser chamda depois do max flow

    double maxDiff = 0,average;
    double sum = 0, totaledges = 0, squareDdiffSum, variance;
    set<pair<pair<string, string>, double>> srcDestDiff; //src dest diff
    for(auto v: g.getVertexSet()){
        for (auto e: v->getAdj()){
            if(e->getFlow() > maxDiff)
                maxDiff = e->getWeight() - e->getFlow();
            srcDestDiff.insert(make_pair(make_pair(v->getInfo(), e->getDest()->getInfo()), e->getWeight()- e->getFlow()));
            sum+= e->getWeight() - e->getFlow();
            //squareDdiffSum = pow(e->getWeight() - e->getFlow(), 2);
            totaledges+=1;
        }
    }
    average = sum / totaledges;
    for(auto x: srcDestDiff){
        squareDdiffSum += pow(x.second - average, 2);
    }
    variance = squareDdiffSum / totaledges;
    // variance esta bem ??
    cout << endl << "max difference  " << maxDiff << "    averge  " << average << "   variance  " << variance << endl;




}