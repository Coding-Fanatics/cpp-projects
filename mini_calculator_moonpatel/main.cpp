/*
Calculator.

Calculator program
Includes the following facilities:
1. Expression calculator
2. Number system conversion

==================GRAMMAR FOR EXPRESSION CALCULATOR===============
Expression:
    Term
    Term + Expression
    Term - Expression

Term:
    Primary
    Primary * Term
    Primary / Term

Primary:
    -Number
    Number
    constants like pi, e and so on
    '('Expression')'
    -'('Expression')'

Number:
    Floating point literal
    Integer
    results of functions like log(a,b), rt(a)

Input comes from cin through the Token_stream called ts

*/

#include <iostream>
#include <iomanip>

#include "Token.h"
#include "numsystem.h"


using namespace std;

Token_stream ts;


int main() {
    // Welcome message
    cout << "WELCOME" << endl;
    printline();
    // Choice list
    cout << "1. Expression calculator" << endl;
    cout << "2. Number system converter" << endl;
    cout << "?. Bitwise arithmetic(COMING SOON)" << endl;
    cout << "?. Unit converter(COMING SOON)" << endl;
    cout << "?. Matrix mathematics(COMING SOON)" << endl;
    cout << "?. Vector mathematics(COMING SOON)" << endl;
    cout << "?. Complex Mathematics(COMING SOON))" << endl;
    printline();
    cout << "Please enter your choice: " << endl;

    // Take input from user
    char ch{0};
    int choice{0};
    cin >> ch;
    if(isalpha(ch)) {
        if(ch=='q')
            return 0;
        else
            throw runtime_error("Inappropriate choice");
    }
    else if(isdigit(ch)) {
        cin.unget();
        cin >> choice;
        if(choice<0||choice>2)
            throw runtime_error("Inappropriate choice");
    }

// do what the input says
try {
    switch(choice) {
        // handles calculation
        case 1:
            if(!calculate())
                return 0;
            break;
        
        case 2:
            numberConverter();
            break;

        default:
            break;
    }
}
catch(runtime_error& e) {
    cout << e.what() << endl;
    return 1;
}

    return 0;
}