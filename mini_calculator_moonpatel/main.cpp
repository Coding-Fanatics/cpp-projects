/*
Calculator program
Includes the following facilities:
1. Expression calculator
2. Number system conversion
(More features coming soon)

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
#include "utils.h"


using namespace std;

Token_stream ts;


int main() {
    // welcome message
    cout << "WELCOME" << "\n";

    while(true) {
        // print main menu and get user choice
        int choice = mainMenu();
    // do what the input says
    try {
        switch(choice) {
            // handles calculation
            case CALCULATE_EXPRESSION:
                if(!calculate())
                    return 0;
                break;

            // handles number conversion
            case NUMBER_SYSTEM:
                numberConverter();
                break;

            // quit the program
            case 0:
                return 0;

            default:
            // to be done later
                break;
            }
        }
    catch(runtime_error& e) {
        cout << e.what() << endl;
        return 1;
        }
    }

    return 0;
}