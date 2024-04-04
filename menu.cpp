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
    cout << "1. Basic Service Metrics\n" << "2. Reliability and Sensitivity to Failures\n" << "4. Quit\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { metrics(g, cities, reservoirs, stations); }
    if (option == "2") {//failures();}
        if (option == "4") { closeMenu(); }
    }
}
void Menu::metrics(Graph<string> g, unordered_map<string ,City> &cities, unordered_map<string, Reservoir> &reservoirs, unordered_map<string, Station> &stations) {
    cout << "What do you want to consult?" << endl;
    cout << "1.Max Flow\n" << "2.Water Needs\n" << "3. Balance Flow" << "4.Go back\n";
    cout << "Option: ";
    string option;
    cin >> option;

    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    vector<pair<string, string>> pipes;
    //pipes.push_back(make_pair("PS_9", "PS_10"));
    pipes.push_back(make_pair("PS_4", "PS_5"));
    //pipes.push_back(make_pair("PS_12", "C_10"));
    if (option == "1") {Utils::waterDeficit(g, reservoirs, cities);}
    else if (option == "2") {Utils::waterDeficitChoosePipe(g, reservoirs, cities, pipes);}
    else if (option == "3") { Utils::Balance(g, reservoirs, cities, stations); }
    else if (option == "4") {/*initialOptions()*/;}
}