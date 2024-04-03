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
            City c = cities_codes[maxiFlow[i].first];
            if((maxiFlow[i].second != currentFlow[i].second) && (c.getDemand() > currentFlow[i].second)){
                affected=true;
                int dif;
                if(maxiFlow[i].second > c.getDemand()){
                dif=c.getDemand() - currentFlow[i].second;}
                else{
                    dif=maxiFlow[i].second - currentFlow[i].second;
                }


                cout << maxiFlow[i].first << "---->" << dif <<endl;
            }

        }
        if(!affected){
            cout << "No cities affected"<< endl;
        }
    }

}


void pipeFailure(string city, Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
    vector<pair<string, string>> res; //src dest of the edges that can be removed

    vector<pair<string, double>> flows = maxFlow(g, reservoirs_codes, cities_codes);

    double initialValue;
    City c;
    for(auto x: flows){
        if(x.first == city){
            c = cities_codes[x.first];
            initialValue = x.second;}
    }

    for(auto src: g.getVertexSet()){
        for(auto e: src->getAdj()){
            string desti = e->getDest()->getInfo();

            g.removeEdge(src->getInfo(), e->getDest()->getInfo());
            vector<pair<string, double>> newFlows = maxFlow(g, reservoirs_codes, cities_codes);

            double newValue;
            for(auto x: newFlows){
                if(x.first == city)
                    newValue = x.second;
            }

            if((initialValue == newValue)||(newValue>=c.getDemand())){

                res.push_back(make_pair(src->getInfo(), desti));
            }

            g.addEdge(src->getInfo(), desti, e->getWeight());

        }
    }
    string orig, dest;
    cout << "The pipelines connecting the following places can be removed: "<<endl;

    for(auto x: res){
        if(x.first[0]=='C')
            orig = cities_codes[x.first].getCity();

        else if(x.first[0]=='P'){
            orig = x.first;
        }

        else{
            orig= reservoirs_codes[x.first].getReservoir();
        }

        if(x.second[0]=='C')
            dest = cities_codes[x.second].getCity();

        else if(x.second[0]=='P'){
            dest = x.second;
        }

        else{
            dest= reservoirs_codes[x.second].getReservoir();
        }
        cout<< orig << " to " << dest <<endl;
    }
}

void waterDeficit(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
    vector<pair<string, double>> initialFlows = maxFlow(g, reservoirs_codes, cities_codes);
    for(auto v: g.getVertexSet()){
        for(auto edge: v->getAdj()) {
            string orig = v->getInfo();
            string dest = edge->getDest()->getInfo();
            int weight = edge->getWeight();

            edge->setWeight(0);

            vector<pair<string, double>> newFlows = maxFlow(g, reservoirs_codes, cities_codes);
            edge->setWeight(weight);

            cout << "The pipeline connecting " << orig << " to " << dest << " affect the following cities: " << endl;
            bool flag=false;
            for (int i = 0; i < newFlows.size(); i++) {
                City c = cities_codes[initialFlows[i].first];
                if ((initialFlows[i].second != newFlows[i].second) && (newFlows[i].second < c.getDemand())) {
                    flag=true;
                    if (initialFlows[i].second < c.getDemand()) {
                        cout << initialFlows[i].first << " by deficit of "
                             << initialFlows[i].second - newFlows[i].second << endl;
                    } else {
                        cout << initialFlows[i].first << " by deficit of " << c.getDemand() - newFlows[i].second
                             << endl;
                    }
                }
            }
            if(!flag){
                cout<<"No cities affected"<<endl;
            }
        }
            }
        }



vector<pair<pair<string, string>, int>> computeDiffs(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
    vector<pair<pair<string, string>, int>> diffs;
    for(auto v: g.getVertexSet()){
        for(auto pipe: v->getAdj()){
            diffs.push_back(make_pair(make_pair(pipe->getOrig()->getInfo(), pipe->getDest()->getInfo()), pipe->getWeight()-pipe->getFlow()));
        }
    }
    return diffs;
}

vector<int> computeMetrics(Graph<string> g, vector<pair<pair<string, string>, int>> pipeDiffs){
    vector<int> res;
    int sum_diff=0;
    int sum_var=0;
    int maxDiff=0;
    for(auto d: pipeDiffs){
        sum_diff += d.second;
        if(d.second>maxDiff){
            maxDiff=d.second;
        }
    }
    int average = sum_diff / pipeDiffs.size();
    for(auto d: pipeDiffs){
        sum_var += ((d.second - average)^2);
    }
    int variance = sum_var/pipeDiffs.size();
    res.push_back(average);
    res.push_back(variance);
    res.push_back(maxDiff);
    return res;
}

bool sortBySecond(pair<pair<string, string>, int> &a, pair<pair<string, string>, int> &b) {
    return a.second > b.second;
}

vector<pair<pair<string, string>, int>> excessFlow(Graph<string> g){
    vector<pair<pair<string, string>, int>> excessFlowPipes;
    for (auto v: g.getVertexSet()){
        for (auto pipe: v->getAdj()){
            if(pipe->getFlow() > 0.9*pipe->getWeight()){
                excessFlowPipes.push_back(make_pair(make_pair(pipe->getOrig()->getInfo(), pipe->getDest()->getInfo()), pipe->getFlow()/pipe->getWeight()));
            }
        }
    }

    sort(excessFlowPipes.begin(), excessFlowPipes.end(), sortBySecond);
    return excessFlowPipes;
}

void Balance(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code){
    vector<pair<string, double>> flows = maxFlow(g, reservoirs_codes, cities_codes);
    vector<pair<pair<string, string>, int>> initialPipeDiffs = computeDiffs(g, reservoirs_codes, cities_codes);

    vector<int> initialMetrics = computeMetrics(g, initialPipeDiffs);

    vector<pair<pair<string, string>, int>> excessFlowPipes = excessFlow(g);

    cout<<excessFlowPipes.size()<<endl;
    int i=4;
    while(i>0) {
        for (auto p: excessFlowPipes) {
            string orig = p.first.first;
            string dest = p.first.second;
            Vertex<string> *vertexOrig;
            Vertex<string> *vertexDest;
            for (auto v: g.getVertexSet()) {
                if (v->getInfo() == orig) {
                    vertexOrig = v;
                } else if (v->getInfo() == dest) {
                    vertexDest = v;
                }
            }
            int minFlowExcess = p.second;
            pair<string, string> pipeMinFlowExcess;
            int pipeCap;
            int pipeFlow;
            for (auto pipe: vertexOrig->getAdj()) {
                if (pipe->getFlow() / pipe->getWeight() < minFlowExcess) {
                    minFlowExcess = pipe->getFlow() / pipe->getWeight();
                    pipeMinFlowExcess.first = pipe->getOrig()->getInfo();
                    pipeMinFlowExcess.second = pipe->getDest()->getInfo();
                    pipeCap = pipe->getWeight();
                    pipeFlow = pipe->getFlow();
                }
            }

            //identifiquei pipe com excesso de flow e identifiquei qual a pipe do vertice de origem com menos excessflow a seguir vou fazer a transferencia;
            int flow;
            for (auto edge: vertexOrig->getAdj()) {
                if (edge->getDest() == vertexDest) {
                    flow = edge->getFlow();
                }
            }
            int pCap = 0.9 * pipeCap;
            int amount_transfer = min(flow, pCap - pipeFlow);
            for (auto edge: vertexOrig->getAdj()) {
                if (edge->getDest() == vertexDest) {
                    edge->setFlow(edge->getFlow() - amount_transfer);
                } else if (edge->getDest()->getInfo() == pipeMinFlowExcess.second) {
                    edge->setFlow(edge->getFlow() + amount_transfer);
                }
            }
        }
        excessFlowPipes = excessFlow(g);
        cout<<excessFlowPipes.size()<<endl;
        i--;
    }


    vector<pair<pair<string, string>, int>> finalPipeDiffs = computeDiffs(g, reservoirs_codes, cities_codes);
    vector<int> finalMetrics= computeMetrics(g, finalPipeDiffs);
    cout<< "Initial: [Average]-->"<<initialMetrics[0]<<" [Variance]-->"<<initialMetrics[1]<<" [MaxDiff]-->"<<initialMetrics[2]<<endl;
    cout<< "Balanced: [Average]-->"<<finalMetrics[0]<<" [Variance]-->"<<finalMetrics[1]<<" [MaxDiff]-->"<<finalMetrics[2]<<endl;
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

    auto v = g.findVertex(code);

    vector<pair<Vertex<string>*, double>> out;
    vector<pair<Vertex<string>*, double>> inc;

    for(auto edge: v->getAdj()){
        out.push_back(make_pair(edge->getDest(), edge->getWeight()));
    }
    for(auto edge: v->getIncoming()){
        inc.push_back(make_pair(edge->getOrig(), edge->getWeight()));
    }

    g.removeVertex(code);

    maxFlow(g, reservoirs_codes, city_codes);

    after = calculateReceivedSupply(g, city_codes);
    cout << "Now, " << after - before << " more cities are not sufficiently supplied. \nAll of them are listed below." << endl <<endl;
    printNotFullySuppliedCities(g, city_codes);

    g.addVertex(code);

    for(auto edge: out){
        g.addEdge(code, edge.first->getInfo(), edge.second);
    }

    for(auto edge: inc){
        g.addEdge(edge.first->getInfo(), code, edge.second);
    }

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

