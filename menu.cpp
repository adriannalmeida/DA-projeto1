#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "menu.h"
#include "Utils.h"



void Menu::openMenu() {
    cout << setw(25) << "Welcome!" << endl;
    chooseRegion();
}

Menu::Menu() {}


void Menu::wait() {
    cout << endl << "Press ENTER to continue ..." << endl;
    cin.ignore(); // Clear the input buffer

    string enter;
    getline(cin, enter); // Read the entire line including Enter key

    while (!enter.empty()) { // Keep reading lines until Enter key is pressed
        getline(cin, enter); // Get the next line of input
    }

    continueM();
}
int Menu::closeMenu() {
    return 0;
}

void Menu:: buildGraph(string s){
    string path_reser, path_station,path_cities,path_pipes;
    if (s == "Portugal"){
        path_reser = "../Project1LargeDataSet/Project1LargeDataSet/Reservoir.csv";
        path_station = "../Project1LargeDataSet/Project1LargeDataSet/Stations.csv";
        path_cities = "../Project1LargeDataSet/Project1LargeDataSet/Cities.csv";
        path_pipes = "../Project1LargeDataSet/Project1LargeDataSet/Pipes.csv";
    }

    else{
        path_reser = "../Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv";
        path_station = "../Project1DataSetSmall/Project1DataSetSmall/Stations_Madeira.csv";
        path_cities = "../Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv";
        path_pipes = "../Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv";}

    ReservoirParser(path_reser, g, reservoirs);
    CityParser(path_cities, g, cities, s);
    StationParser(path_station, g, stations);
    PipesParser(path_pipes, g);
}

void Menu::chooseRegion(){
    cout << "Choose the network of one of the following region" << endl;
    cout << "1. Portugal (mainland)\n" << "2. Madeira\n" << "3. Quit\n";
    string option;
    cout << "Option: "; cin >> option; cout << endl;
    while (!(option == "1" || option == "2" || option == "3" )) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    if(option == "1"){
            buildGraph("Portugal");
            initialOptions();
    }
    if(option == "2"){
            buildGraph("Madeira");
            initialOptions();
    }
    else {closeMenu();}
}


void Menu::initialOptions() {
    cout << "What do you want to consult?" << endl;
    cout << "1. Basic Service Metrics\n" << "2. Reliability and Sensitivity to Failures\n" << "3. Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3" )) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { metrics(); }
    if (option == "2") {failures();}
        if (option == "3") { chooseRegion(); }
}

void Menu::failures(){
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
        wait();}
    else if (option == "2") {
        pumpingStations();
    }
    else if(option == "3"){
        pipelines();
    }
    else if (option == "4") { initialOptions(); }
}

void Menu::pipelines(){
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
        wait();}
    else if(option=="2"){
        Utils::waterDeficit(g, reservoirs, cities);
        cout<<endl;
        wait();
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
        wait();
    }
    else{failures();}
}

void Menu::pumpingStations(){
    cout << "1. Remove one at a time\n" << "2. Choose Pumping Station\n" << "3. Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;
    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if(option=="1"){Utils::removePumpingStations(g, cities, stations, reservoirs);
        cout<<endl;
        wait();}
    else if(option=="2"){
        cout << "Pumping Station code: ";
        string option;
        cin >> option;
        Utils::chooseRemovePumpingStations(g, cities, stations, reservoirs, option);
        cout<<endl;
        wait();
    }
    else{failures();}
}


void Menu::metrics() {
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
    if (option == "1") {maxFlowMenu();}
    else if (option == "2") {Utils::printNotFullySuppliedCities(g, cities, flows);
        cout<<endl;
        wait();}
    else if (option == "3") { Utils::Balance(g, reservoirs, cities, stations);
        cout<<endl;
        wait();}
    else if (option == "4") {initialOptions();}
}

void Menu::maxFlowMenu(){
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
        wait();}
    else if (option == "2") {chooseCity();}
    else if (option == "3") { metrics(); }

}

void Menu::chooseCity(){
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
        wait();
    }
    else if (option == "2") {
        cout << "City name: ";
        string option;
        cin >> option;

        Utils::chooseCityByName(g, reservoirs, cities, option);
        cout<<endl;
        wait();
    }
    else if (option == "3") {maxFlowMenu();}
}

void Menu::continueM(){
    cout << "Choose one option" << endl;
    cout << "1. Go back to Menu\n" << "2.Quit\n" << endl;
    cout << "Option: "<<endl;
    string option;
    cin >> option;

    while (!(option == "1" || option == "2") ){
    cout << "Invalid input. Option: ";
    cin >> option;
    }
    if( option == "1"){chooseRegion();}
    else{closeMenu();}
}
