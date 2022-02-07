/*
Simple calculator.

This program implements a simple calculator.

==========================GRAMMAR==========================
Expression:
    Term
    Term + Expression
    Term - Expression

Term:
    Primary
    Primary * Term
    Primary / Term

Primary:
    Number
    '('Expression')'
    
Number:
    Floating point literal
    Integer

Input comes from cin through the Token_stream called ts

*/

#include <iostream>
#include "Token.h"


using namespace std;

Token_stream ts;


int main() {

    // Welcome message
    cout << "WELCOME" << endl;
    cout << "This is a simple calculator program" << endl;
    cout << "Please enter the expression you want to calculate below" << endl;
    cout << "(NOTE: Enter q to quit and ; after the end of an expression)" << endl;

    while(true) {
    try {
        cout << prompt;
        Token token=ts.get();

        // check whether input is expression or quit command
        if(token.kind==quit)
            return 0;   // exit
        else if(token.kind==terminator)
            continue;   // read another expression
        else
            ts.unget(token);    // input is expression, unget and read expression()

        // calculate the expression
        double ans = expression();
        ts.flush();             // flush out remaining terminator(';')

        cout << result << ans << endl;  // print the result
    }
    catch(runtime_error &e) {
        cout << "Error! ";
        cout << e.what() << endl;

        cin.ignore(100,'\n');    // ignore until ; is reached
        ts.flush();             // flush buffer

        bool exit = ask();     // to continue or exit program?
        if(exit)
            break;
    }
}

    return 0;
}