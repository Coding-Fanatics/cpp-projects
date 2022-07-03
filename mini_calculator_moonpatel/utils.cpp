#include <iostream>

#include "utils.h"
#include "Token.h"

using std::cout;
using std::cin;


int mainMenu() {
    // clear the previous content on the screen
    clearScreen();
    // print the main menu
    printline();
    printMainMenu();
    printline();

    // ask for choice
    cout << "-> ";

    // Take input from user
    char ch{0};
    int choice{0};
    cin >> ch;
    if(isalpha(ch)) {
        if(ch=='q')
            return 0;
        else
            throw std::runtime_error("Inappropriate choice");
    }
    else if(isdigit(ch)) {
        cin.unget();
        cin >> choice;
        if(choice<0||choice>3)
            throw std::runtime_error("Inappropriate choice");
    }

    clearScreen();

    return choice;
}

// print a line
void printline() {
    std::cout << LINE << "\n";
}

// print the main menu
void printMainMenu() {
    // Choice list
    cout << "1. Expression calculator" << "\n";
    cout << "2. Number system converter" << "\n";
    cout << "3. Matrix calculator(IN PRODUCTION)" << "\n";
    cout << "?. Bitwise arithmetic(COMING SOON)" << "\n";
    cout << "?. Unit converter(COMING SOON)" << "\n";
    cout << "?. Vector mathematics(COMING SOON)" << "\n";
    cout << "?. Complex Mathematics(COMING SOON))" << "\n";
}

// clears all the content on the screen
void clearScreen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system("clear");
    #endif
}