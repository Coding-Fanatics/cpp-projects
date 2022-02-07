#include <iostream>
#include "Token.h"

//=====================================================================================
// Token class member functions
//=====================================================================================

Token::Token(char kind_val='0', double value_val=0)
    : kind{kind_val}, value{value_val} {}



//=====================================================================================
// Token_stream class member functions
//=====================================================================================

// Default constructor
Token_stream::Token_stream()
    : buffer{}, isFull{false} {}

// Get a token from the input stream
// Actually behind the scenes what happens is get()
// checks the buffer Token defined in Token_stream class and returns
// the buffer Token if it is not empty else it reads a Token from the standard input
Token Token_stream::get() {
    if(isFull) {
        isFull = false;         // set isFull to false indicating buffer is now empty
        Token temp = buffer;
        buffer = Token();       // clear the buffer value
        return temp;            // return  a copy of buffer
    }

    // if the buffer is empty
    char ch=0;
    std::cin >> ch;

    switch(ch) {
        case '+':   case '-':   case '*':   case '/':   case ';':
        case 'q':   case '(':   case ')':
            return Token{ch,0};         // return a Token 
        
        // the token is a number
        case '0':   case '1':   case '2':   case '3':   case '4':
        case '5':   case '6':   case '7':   case '8':   case '9':
            {
                std::cin.unget();    // the character was not an operator
                double d;       
                std::cin >> d;       // read a double
                return Token{'~',d};
            }

        default:
            throw std::runtime_error("Bad token");   // some bad token obtained in input stream
            return Token{};
    }
}


// putback a character in the input stream
// The character is stored in the buffer member of the Token_stream class
void Token_stream::unget(Token token) {
    if(!isFull) {
        buffer = Token{token.kind,token.value};     // store the token in buffer
        isFull = true;                               
        return;
    }
    else {
        throw std::runtime_error("Buffer is already full");     // the buffer is already full
        return;
    }
}

// clear buffer
void Token_stream::flush() {
    isFull = false;
    buffer = Token{};
}


//=====================================================================================
// Parsing functions for our calculator
//=====================================================================================

// read an Expression
//
// Grammar for expression
// Expression:
//     Term
//     Term + Expression
//     Term - Expression
double expression() {
    double d = term();          // get a term first

    Token token = ts.get();     // get a token
    switch(token.kind) {
        case '+':
            return (d + expression());

        case '-':
            return (d - expression());

        default:                // no expression after term
            ts.unget(token);
            return d;
    }
}


// read a Term
//
// Grammar for Term:
//     Primary
//     Primary * Term
//     Primary / Term
double term() {
    double d = primary();        // read a primary first

    Token token = ts.get();           // read next token
    switch(token.kind) {
        case '*':
            return d*term();

        case '/':
        {
            double den = term();
            if(den==0) throw std::runtime_error("cannot divide by zero");
            return d/den;
        }

        default:                // if there is no term after current primary
            ts.unget(token);
            return d;
    }
}

// read a Primary
//
// Grammar for Primary:
//     Number
//     '('Expression')'
double primary() {
    Token token = ts.get();     // receive a token from the input stream

    // the primary is '('Expression')'
    if(token.kind=='(') {       
        double d = expression();                // this is an expression
        Token t = ts.get();
        if(t.kind!=')')
            throw std::runtime_error("bad format");      // there is a format error in input
        else
            return d;               // everything is fine return d
        }
    else if(token.kind=='-') {
        return -primary();
    }
    else
        return token.value;
}

// ask whether to continue or exit when an error occurs
bool ask() {
    while(true) {
    std::cout << "Do you want to continue(y/n)?" << std::endl;
    char choice;
    std::cout << prompt;
    std::cin >> choice;
    std::cin.ignore(10,'\n');
    switch(choice) {
        case 'y':
        case 'Y':
            return 0;

        case 'n':
        case 'N':
            return 1;

        default:
            std::cout << "Incorrect choice" << std::endl;
            break;
        }
    }
}
