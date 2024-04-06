#include "Utils.h"
#include "data_structures/graph.h"
#include <iostream>
using namespace std;


void Utils::printNotFullySuppliedCities(Graph<string> &g, unordered_map<string, City> &city_codes, unordered_map<string, double> flows){
    bool printColumnNames = 0;
    for (auto v : g.getVertexSet()) {
        string code = v->getInfo();
        if(code[0] == 'C'){
            auto c = city_codes[code];
            if (flows[code] < c.getDemand()) {
                if (!printColumnNames) {
                    cout << "City Code" << '\t' << "Deficit" << endl;
                    printColumnNames = 1;
                }
                cout << c.getCode() << "\t      " << (c.getDemand() - flows[code]) << "\tDemand is: \t      " << c.getDemand() << "\tFlow is: \t      " << flows[code]<<endl;
            }
        } else{
            if(code[0] == 'P') break;
        }
    }
    if (!printColumnNames) cout << "All cities receive full demand!"<<endl;
    cout << endl;
}


// Max Flow


void Utils::testAndVisit(queue<Vertex<string>*> &q, Edge<string>* e, Vertex<string>* v, double r ){
    if(!v->isVisited() && r > 0 ){
        v->setVisited(true);
        v->setPath(e);
        q.push(v);
    }
}

bool Utils::findPath(Graph<string>& g, Vertex<string>*s, Vertex<string>*d){
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

double Utils::minResidual(Vertex<string>* s, Vertex<string>* d){
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

void Utils::setFlowPath (Vertex<string>* s, Vertex<string>* d, double flow){
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

unordered_map<string, double> Utils::maxFlow(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
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

    if(src==snk){cout<< "Invalid";}

    unordered_map<string, double> res;
        for(auto v: g.getVertexSet()){
        for(auto edge: v->getAdj()){
            edge->setFlow(0);
        }
    }
    while(findPath(g, src, snk)){
        double f= minResidual(src, snk);
        setFlowPath(src, snk, f);
    }

    for(auto v: g.getVertexSet()){
        int sumFlow=0;
        if(v->getInfo()[0]=='C'){
            for(auto edge: v->getIncoming()){
                sumFlow+=edge->getFlow();
            }
            res[v->getInfo()] = sumFlow;
        }
    }

    g.removeVertex("source");
    g.removeVertex("sink");
    return res;
}

void Utils::chooseCityByName(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, string city){
    unordered_map<string, double> flows = maxFlow(g, reservoirs_codes, cities_codes);
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
        else {
            for (auto ci: flows) {
                if (ci.first == code) {
                    cout << city << ": " << ci.second;
                }
            }
        }
    }

}

void Utils::chooseCityByCode(Graph<string> &g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, string code){
    unordered_map<string, double> flows = maxFlow(g, reservoirs_codes, cities_codes);
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

void Utils::chooseRemovePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code, unordered_map<string, Reservoir> &reservoirs_code, string station){

    Vertex<string>* ps;
    for(auto v: g.getVertexSet()){
        if(v->getInfo()==station){
            ps=v;
        }
    }

    unordered_map<string, double> maxiFlow = maxFlow(g, reservoirs_code, cities_codes);




        vector<pair<Vertex<string>*, double>> outcomingEdges;
        vector<pair<Vertex<string>*, double>> incomingEdges;
        for(auto edge: ps->getAdj()){
            outcomingEdges.push_back(make_pair(edge->getDest(), edge->getWeight()));
        }
        for(auto edge: ps->getIncoming()){
            incomingEdges.push_back(make_pair(edge->getOrig(), edge->getWeight()));
        }

        string info=ps->getInfo();
        g.removeVertex(ps->getInfo());

        unordered_map<string, double> currentFlow = maxFlow(g, reservoirs_code, cities_codes);

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
        for(auto p : maxiFlow){
            City c = cities_codes[p.first];
            if((p.second != currentFlow[p.first]) && (c.getDemand() > currentFlow[p.first])){
                affected=true;
                int dif;
                if(p.second > c.getDemand()){
                    dif=c.getDemand() - currentFlow[p.first];}
                else{
                    dif=p.second - currentFlow[p.first];
                }

                cout << p.first << "-> Demand: " << c.getDemand() <<" Old Flow: " << maxiFlow[p.first] << " New Flow: " << currentFlow[p.first] << " Deficit: " <<dif <<endl;
            }

        }
        if(!affected){
            cout << "No cities affected"<< endl;
        }


}


 void Utils::removePumpingStations(Graph<string> &g, unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code, unordered_map<string, Reservoir> &reservoirs_code){

    std::vector<Vertex<string>*> stations;
    for(auto v: g.getVertexSet()){
        if(v->getInfo()[0]=='P'){
            stations.push_back(v);
        }
    }

    unordered_map<string, double> maxiFlow = maxFlow(g, reservoirs_code, cities_codes);


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

        unordered_map<string, double> currentFlow = maxFlow(g, reservoirs_code, cities_codes);

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
        for(auto p : maxiFlow){
            City c = cities_codes[p.first];
            if((p.second != currentFlow[p.first]) && (c.getDemand() > currentFlow[p.first])){
                affected=true;
                int dif;
                if(p.second > c.getDemand()){
                dif=c.getDemand() - currentFlow[p.first];}
                else{
                    dif=p.second - currentFlow[p.first];
                }

                cout << p.first << "-> Demand: " << c.getDemand() <<" Old Flow: " << maxiFlow[p.first] << " New Flow: " << currentFlow[p.first] << " Deficit: " <<dif <<endl;
            }

        }
        if(!affected){
            cout << "No cities affected"<< endl;
        }
    }

}


void Utils::pipeFailure(string city, Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
    vector<pair<string, string>> res; //src dest of the edges that can be removed

    unordered_map<string, double> flows = maxFlow(g, reservoirs_codes, cities_codes);

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
            auto initialWeight = e->getWeight();
            e->setWeight(0);
            //g.removeEdge(src->getInfo(), e->getDest()->getInfo());
            unordered_map<string, double> newFlows = maxFlow(g, reservoirs_codes, cities_codes);

            double newValue;
            for(auto x: newFlows){
                if(x.first == city)
                    newValue = x.second;
            }

            if((initialValue == newValue)||(newValue>=c.getDemand())){

                res.push_back(make_pair(src->getInfo(), desti));
            }

            e->setWeight(initialWeight);

        }
    }
    cout << res.size() << endl;
    string orig, dest;
    cout << "The pipelines connecting the following places can be removed one at a time: "<<endl;

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

void Utils::waterDeficit(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
    unordered_map<string, double> initialFlows = maxFlow(g, reservoirs_codes, cities_codes);
    for(auto v: g.getVertexSet()){
        for(auto edge: v->getAdj()) {
            string orig = v->getInfo();
            string dest = edge->getDest()->getInfo();
            int weight = edge->getWeight();

            edge->setWeight(0);

            unordered_map<string, double> newFlows = maxFlow(g, reservoirs_codes, cities_codes);
            edge->setWeight(weight);

            cout << "The pipeline connecting " << orig << " to " << dest << " affects the following cities: " << endl;
            bool flag=false;
            for (auto p : initialFlows) {
                City c = cities_codes[p.first];
                if ((p.second != newFlows[p.first]) && (newFlows[p.first] < c.getDemand())) {
                    flag=true;
                    if (p.second < c.getDemand()) {
                        if(p.second - newFlows[p.first]>0){
                            cout << p.first << "-> Demand: " << c.getDemand() <<" Old Flow: " << initialFlows[p.first] << " New Flow: " << newFlows[p.first] << " Deficit: " <<p.second - newFlows[p.first] <<endl;
                        }
                        else{
                            cout << p.first << "-> Demand: " << c.getDemand() <<" Old Flow: " << initialFlows[p.first] << " New Flow: " << newFlows[p.first] << " Excess: " <<newFlows[p.first] -p.second <<endl;
                        }
                    } else {
                        cout << p.first << "-> Demand: " << c.getDemand() <<" Old Flow: " << initialFlows[p.first] << " New Flow: " << newFlows[p.first] << " Deficit: " <<c.getDemand() - newFlows[p.first] <<endl;
                    }
                }
            }
            if(!flag){
                cout<<"No cities affected!"<<endl;
            }
        }
            }
        }

void Utils::waterDeficitChoosePipe(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, vector<pair<string, string>> pipes) {
    unordered_map<string, double> initialFlows = maxFlow(g, reservoirs_codes, cities_codes);
    vector<pair<Edge<string> *, int>> weights;
    for (const auto& pipe: pipes) {

        for (auto v: g.getVertexSet()) {
            for (auto edge: v->getAdj()) {
                string orig = v->getInfo();
                string dest = edge->getDest()->getInfo();

                if (((orig == pipe.first) && (dest == pipe.second)) || ((orig == pipe.second) && (dest == pipe.first))) {

                    int weight = edge->getWeight();
                    edge->setWeight(0);

                    weights.push_back(make_pair(edge, weight));

                }

            }
        }
    }
    unordered_map<string, double> newFlows = maxFlow(g, reservoirs_codes, cities_codes);

    for(auto p: weights){

        p.first->setWeight(p.second);

    }

    cout <<endl << "The pipelines chosen affects the following cities: " << endl;
    bool flag=false;
    for (auto p : initialFlows) {
        City c = cities_codes[p.first];
        if ((p.second != newFlows[p.first]) && (newFlows[p.first] < c.getDemand())) {
            flag=true;
            if (p.second < c.getDemand()) {
                cout << p.first << "-> Demand: " << c.getDemand() <<" Old Flow: " << initialFlows[p.first] << " New Flow: " << newFlows[p.first] << " Deficit: " <<p.second - newFlows[p.first] <<endl;
            } else {
                cout << p.first << "-> Demand: " << c.getDemand() <<" Old Flow: " << initialFlows[p.first] << " New Flow: " << newFlows[p.first] << " Deficit: " <<c.getDemand() - newFlows[p.first] <<endl;
            }
        }
    }
    if(!flag){
        cout<<"No cities affected!"<<endl;
    }
}



vector<pair<pair<string, string>, int>> Utils::computeDiffs(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes){
    vector<pair<pair<string, string>, int>> diffs;
    for(auto v: g.getVertexSet()){
        for(auto pipe: v->getAdj()){
            diffs.push_back(make_pair(make_pair(pipe->getOrig()->getInfo(), pipe->getDest()->getInfo()), pipe->getWeight()-pipe->getFlow()));
        }
    }
    return diffs;
}

vector<int> Utils::computeMetrics(Graph<string> g, vector<pair<pair<string, string>, int>> pipeDiffs){
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

bool Utils::sortBySecond(pair<pair<string, string>, int> &a, pair<pair<string, string>, int> &b) {
    return a.second > b.second;
}

vector<pair<pair<string, string>, int>> Utils::excessFlow(Graph<string> g){
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

void Utils::Balance(Graph<string> g, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &cities_codes, unordered_map<string, Station> &stations_code){
    unordered_map<string, double> flows = maxFlow(g, reservoirs_codes, cities_codes);
    vector<pair<pair<string, string>, int>> initialPipeDiffs = computeDiffs(g, reservoirs_codes, cities_codes);

    vector<int> initialMetrics = computeMetrics(g, initialPipeDiffs);

    vector<pair<pair<string, string>, int>> excessFlowPipes = excessFlow(g);


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

            int flow;
            for (auto edge: vertexOrig->getAdj()) {
                if (edge->getDest() == vertexDest) {
                    flow = edge->getFlow();
                }
            }
            int pCap = 0.80 * pipeCap;
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

        i--;
    }


    vector<pair<pair<string, string>, int>> finalPipeDiffs = computeDiffs(g, reservoirs_codes, cities_codes);
    vector<int> finalMetrics= computeMetrics(g, finalPipeDiffs);
    cout<< "Initial: [Average]-->"<<initialMetrics[0]<<" [Variance]-->"<<initialMetrics[1]<<" [MaxDiff]-->"<<initialMetrics[2]<<endl;
    cout<< "Balanced: [Average]-->"<<finalMetrics[0]<<" [Variance]-->"<<finalMetrics[1]<<" [MaxDiff]-->"<<finalMetrics[2]<<endl;
}

int Utils::calculateReceivedSupply(Graph<string> &g,unordered_map<string, City> &city_codes, unordered_map<string, double> flows){
    int notSupplied = 0;

    for (auto v : g.getVertexSet()) {
        if(v->getInfo()[0] == 'C'){
            if(flows[v->getInfo()] < city_codes[v->getInfo()].getDemand()){
                notSupplied++;
            }
        }
    }
    return notSupplied;
}

void Utils::chooseFailingReservoir(Graph<string> &g, string code, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &city_codes){

    int before, after;
    unordered_map<string, double> flows = maxFlow(g, reservoirs_codes, city_codes);
    before = calculateReceivedSupply(g, city_codes, flows);

    try {
        Reservoir R = reservoirs_codes.at(code);
    } catch (const std::out_of_range& e) {
        cout << "Reservoir does not exist!: " << endl;
        return;
    }

    cout << "When every Reservoir was functioning, " << before << " city(ies) were not receiving the needed supply." <<endl;
    printNotFullySuppliedCities(g, city_codes, flows);

    auto v = g.findVertex(code);

    queue<int> caps;

    for(auto edge: v->getAdj()){

        caps.push(edge->getWeight());
        edge->setWeight(0);
    }

    flows = maxFlow(g, reservoirs_codes, city_codes);

    after = calculateReceivedSupply(g, city_codes,  flows);
    cout << "When reservoir "<< code << " stopped functioning " << after - before  << " more cities are not sufficiently supplied.\nAll of them are listed below." << endl <<endl;
    printNotFullySuppliedCities(g, city_codes, flows);

    for(auto edge: v->getAdj()){
        edge->setWeight(caps.front());
        caps.pop();
    }


}

void Utils::noUnnecessaryMaxFlow(Graph<string> &g, string code, unordered_map<string, Reservoir> &reservoirs_codes, unordered_map<string, City> &city_codes){

    //início do inicio_________________________________________________________
    int before, after, outgF = 0;
    unordered_map<string, double> flows = maxFlow(g, reservoirs_codes, city_codes);
    before = calculateReceivedSupply(g, city_codes, flows);

    try {
        Reservoir R = reservoirs_codes.at(code);
    } catch (const std::out_of_range& e) {
        cout << "Reservoir does not exist!: " << endl;
        return;
    }

    cout << "When every Reservoir was functioning, " << before << " city(ies) were not receiving the needed supply." <<endl;
    printNotFullySuppliedCities(g, city_codes, flows);

    auto v = g.findVertex(code);
    queue<pair<Vertex<string>*, double>> out;

    for(auto edge: v->getAdj()){
        out.emplace(edge->getDest(), edge->getWeight());
        outgF += edge->getFlow();
    }

    vector<string> vAffectByReservoir;
    g.dfsVisit(v, vAffectByReservoir);
    for(auto el : vAffectByReservoir)
        cout << el <<endl;

    g.removeVertex(code);
    // fim do início_________________________________________________________________

    //inicio do fim ____________________________________________________________________________
    after = calculateReceivedSupply(g, city_codes,  flows);
    cout << "When reservoir "<< code << " stopped functioning " << after - before << " more cities are not sufficiently supplied.\nAll of them are listed below." << endl <<  endl;
    printNotFullySuppliedCities(g, city_codes, flows);

    g.addVertex(code);

    while(!out.empty()){
        g.addEdge(code, out.front().first->getInfo(), out.front().second);
        out.pop();
    }
    //fim do fim________________________________________________________________________
}


