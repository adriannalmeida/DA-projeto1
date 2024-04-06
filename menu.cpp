#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "menu.h"
#include "Utils.h"



void Menu::openMenu(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations) {
    cout << setw(25) << "Welcome!" << endl;
    initialOptions(g, cities, reservoirs, stations);
}

int Menu::closeMenu() {
    return 0;
}
void Menu::initialOptions(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations) {
    cout << "What do you want to consult?" << endl;
    cout << "1. Basic Service Metrics\n" << "2. Reliability and Sensitivity to Failures\n" << "3. Quit\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3" )) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { metrics(g, cities, reservoirs, stations); }
    if (option == "2") {failures(g, cities, reservoirs, stations);}
        if (option == "3") { closeMenu(); }
    }

void Menu::failures(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations){
    cout << "What do you want to remove?" << endl;
    cout << "1. Reservoir\n" << "2. Pumping Station\n" << "3. Pipeline\n"<< "4. Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") {
        cout << "Reservoir Code: ";
        string option;
        cin >> option;
        Utils::chooseFailingReservoir(g, option, reservoirs, cities);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);}
    else if (option == "2") {
        pumpingStations(g, cities, reservoirs, stations);
    }
    else if(option == "3"){
        pipelines(g, cities, reservoirs, stations);
    }
    else if (option == "4") { closeMenu(); }
}

void Menu::pipelines(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations){
    cout << "1. Consult which pipelines can be removed without affecting a specific city\n" << "2. Remove pipelines one at a time and see affected cities\n" << "3. Choose which pipelines to remove\n" << "4. Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;
    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if(option=="1"){
        cout << "City code: ";
        string option;
        cin >> option;
        Utils::pipeFailure(option, g, reservoirs, cities);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);}
    else if(option=="2"){
        Utils::waterDeficit(g, reservoirs, cities);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);
    }
    else if(option == "3"){
        vector<pair<string, string>> pipes;
        bool flag=true;
        while(flag){
            cout << "Origin of Pipeline: ";
            string orig;
            cin >> orig;
            cout << "Destination of Pipeline: ";
            string dest;
            cin >> dest;
            pipes.push_back(make_pair(orig, dest));
            cout << "Do you want to remove more pipelines?"<<endl;
            cout << "1. Yes\n" << "2. No\n";
            cout << "Option: ";
            string option;
            cin >> option;

            while (!(option == "1" || option == "2")) {
                cout << "Invalid input. Option: ";
                cin >> option;
            }
            if(option=="2"){
                flag=false;
            }
        }
        Utils::waterDeficitChoosePipe(g, reservoirs, cities, pipes);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);
    }
    else{failures(g, cities, reservoirs, stations);}
}

void Menu::pumpingStations(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations){
    cout << "1. Remove one at a time\n" << "2. Choose Pumping Station\n" << "3. Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;
    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if(option=="1"){Utils::removePumpingStations(g, cities, stations, reservoirs);}
    else if(option=="2"){
        cout << "Pumping Station code: ";
        string option;
        cin >> option;
        Utils::chooseRemovePumpingStations(g, cities, stations, reservoirs, option);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);
    }
    else{failures(g, cities, reservoirs, stations);}
}


void Menu::metrics(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations) {
    cout << "What do you want to consult?" << endl;
    cout << "1.Max Flow\n" << "2.Water Needs\n" << "3. Balance Flow\n" << "4.Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;

    unordered_map<string, double> flows = Utils::maxFlow(g, reservoirs, cities);
    if (option == "1") {maxFlowMenu(g, cities, reservoirs, stations);}
    else if (option == "2") {Utils::printNotFullySuppliedCities(g, cities, flows);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);}
    else if (option == "3") { Utils::Balance(g, reservoirs, cities, stations);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);}
    else if (option == "4") {initialOptions(g, cities, reservoirs, stations);}
}

void Menu::maxFlowMenu(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations){
    cout << "Which max flow do you want to consult?" << endl;
    cout << "1.All cities\n" << "2.Specific city\n" << "3.Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    vector<pair<string, string>> pipes;

    if (option == "1") {Utils::chooseCityByName(g, reservoirs, cities, "none");
        cout<<endl;
        continueM(g, cities, reservoirs, stations);}
    else if (option == "2") {chooseCity(g, cities, reservoirs, stations);}
    else if (option == "3") { metrics(g, cities, reservoirs, stations); }

}

void Menu::chooseCity(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations){
    cout << "How do you want to specify the city?" << endl;
    cout << "1.Code\n" << "2.Name\n" << "3.Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    vector<pair<string, string>> pipes;

    if (option == "1") {
        cout << "City code: ";
        string option;
        cin >> option;

        Utils::chooseCityByCode(g, reservoirs, cities, option);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);
    }
    else if (option == "2") {
        cout << "City name: ";
        string option;
        cin >> option;

        Utils::chooseCityByName(g, reservoirs, cities, option);
        cout<<endl;
        continueM(g, cities, reservoirs, stations);
    }
    else if (option == "3") {maxFlowMenu(g, cities, reservoirs, stations);}

}

void Menu::continueM(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations){
    cout << "Want do you want to do now?" << endl;
    cout << "1. Go back to Menu\n" << "2.Quit\n" << endl;
    cout << "Option: "<<endl;
    string option;
    cin >> option;

    while (!(option == "1" || option == "2") ){
    cout << "Invalid input. Option: ";
    cin >> option;
    }
    if( option == "1"){initialOptions(g, cities, reservoirs, stations);}
    else{closeMenu();}
}
