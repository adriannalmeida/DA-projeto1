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

void maxFlow(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes){
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


    for(auto dest: destinations){
        //cout << src->getInfo() << "---->" << v->getInfo()<<endl;
        for(auto v: g.getVertexSet()){
            for(auto edge: v->getAdj()){
                edge->setFlow(0);
            }
        }

        while(findPath(g, src, dest)){
            double f= minResidual(src, dest);
            setFlowPath(src, dest, f);
        }
        /*Vertex<string>* currentV=dest;
        double maxFlow=0;
        while (currentV->getInfo() != src->getInfo()){
            maxFlow+=currentV->getPath()->getFlow();
            currentV=currentV->getPath()->getOrig();
        }*/
        double maxFlow=0;
        for(auto v: g.getVertexSet()){
            for(auto edge: v->getAdj()){
                if(edge->getDest()==dest){
                    maxFlow+=edge->getFlow();
                }
            }
        }

        cout << dest->getInfo() <<": " << maxFlow<<endl;
    }

}