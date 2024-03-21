#include "menu.h"
#include "Utils.h"

void nonBlockingEntrance() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void restoreEntrace() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void printMenu(vector<string> options, int size, int select, string menuName) {
    system("clear");
    int terminalWidth = 44;
    int menuIndentation = 22 - (menuName.size() / 2);
    std::cout << "_______________________________________________\n";
    std::cout << "" << std::setw(menuIndentation) << "" << menuName << std::setw(menuIndentation) << "" << "\n";
    std::cout << "|          Choose one of the options          |\n";
    std::cout << "|_____________________________________________|\n";

    int maxOptionLength = 0;
    for (const std::string& option : options) {
        maxOptionLength = std::max(maxOptionLength, static_cast<int>(option.length()));
    }
    for (int i = 0; i < size; ++i) {
        int indentation = (terminalWidth - maxOptionLength) / 2;
        if (i == select) {
            std::cout << setw(indentation) << "" << "\033[1;31m> " << options[i] << " <\033[0m\n"; // Set text to red
        } else {
            std::cout << setw(indentation) << "" << options[i] << "\n";
        }
    }
    std::cout << "|______________________________________________|\n";
}

void auxprintMenu(vector<string> options, int & size, int &select, string menuName){
    char keyStroke;
    do{
        printMenu(options, size, select, menuName);
        keyStroke = getchar();
        switch (keyStroke){
            case '\033':  // Tecla de esc
                getchar();  // Descarta o '[' que segue a tecla de esc
                switch (getchar()) {  // Lê a tecla real
                    case 'A':  // Tecla para cima
                        select = (select - 1 + size) % size;
                        break;
                    case 'B':  // Tecla para baixo
                        select = (select + 1) % size;
                        break;
                }
                break;
        }
    }while (keyStroke != '\n');  // Enter pressionado
}

void mainMenu(Graph<string> g, unordered_map<string ,City> cities, unordered_map<string, Reservoir> reservoirs){
    vector<string> opt = {"Max Flow", "Pipes can remove", "C"};
    int select = 0, size = 3;
    nonBlockingEntrance();
    auxprintMenu(opt, size, select,"Main Menu");
    restoreEntrace();
    switch (select){
        case 0:
            cout << "aaaa";
            //wait();
            break;
        case 1:
            pipeFailure("C_3", g, reservoirs, cities);
            //wait();
            break;
        case 2:
            cout << "ahahah" << endl;
        case 3:
            cout << "GOOD BYE ;)" << endl;
            return;
    }

}