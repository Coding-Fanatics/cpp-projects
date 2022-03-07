#include <iostream>
#include <iomanip>
#include <cmath>
#include "Token.h"

//=====================================================================================
// Token class member functions
//=====================================================================================

Token::Token(char kind_val, double value_val)
    : kind{kind_val}, value{value_val} {}

Token::Token()
    : Token{0,0} {}


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

        // pi 
        case 'p':
            {
                std::cin >> ch;
                if(ch=='i')
                    return Token{PI_CHAR,0};
                else
                    throw std::runtime_error("bad format");
            }

        // eulers constant
        case 'e':
            return Token{EULER_CONSTANT_CHAR,0};
        
        // a log function
        case 'l':
            return Token{ch,0};

        // a square root function
        case 'r':
            return Token{ch,0};

        default :
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
//     -Number
//     Number
//     constants like pi, e and so on
//     '('Expression')'
//     -'('Expression')'
double primary() {
    Token token = ts.get();     // receive a token from the input stream

    switch(token.kind) {
        // primary is '('Expression')'
        case '(':
            {
                double d = expression();      // read an expression
                Token t = ts.get();
                if(t.kind!=')')
                    throw std::runtime_error("bad format");
                else
                    return d;
            }

        // primary is -(some number)
        case SUBTRACT:
            return -primary();

        // primary is a number
        case NUM_KIND:
            return token.value;

        // primary id pi
        case PI_CHAR:
            return PI;

        // primary is euler's constant
        case EULER_CONSTANT_CHAR:
            return EULER_CONSTANT;

        // primary is a log function
        case 'l':
            {
                std::string log{};
                std::cin.unget();
                char ch;
                for(int i=0; i<3; i++) {
                    std::cin >> ch;
                    log+=ch;
                }
                if(log=="log")
                    return std::log(primary());
                else
                    throw std::runtime_error("bad format in log function");
            }

        case 'r':
            {
                char c;
                std::cin >>c;
                if(c=='t') {
                    double d = primary();
                    if(d<0)
                        throw std::runtime_error("root function cannot have negative argument");
                    else
                        return std::sqrt(d);
                }
                else
                    throw std::runtime_error("bad format");
            }

        // some error occured
        default:
            throw std::runtime_error("bad format");
    }
}


// handles the number converting operation
void numberConverter() {
    int choice1{0},choice2{0};
    // Print options for the user
    std::cout << "1. Binary" << std::endl;
    std::cout << "2. Octal" << std::endl;
    std::cout << "3. Decimal" << std::endl;
    std::cout << "4. Hexadecimal" << std::endl;

    // Get first option
    std::cout << "Number system you want to convert from: ";
    while(std::cin >> choice1) {
        if(choice1<1 || choice1>4)
            std::cout << "Please enter an appropriate option" << std::endl;
        else
            break;
    }

    // Get second option
    std::cout << "Number system you want to convert to: ";
    while(std::cin >> choice2) {
        if(choice2<1 || choice2>4)
            std::cout << "Please enter an appropriate option" << std::endl;
        else
            break;
    }

    std::cout << "Enter the number: " << std::endl;
    
    // Input loop
    while(true) {
        std::cout << PROMPT;
        int num{0};     char ch{0};
        std::cin >> ch;

        // handle the quit operation
        if(isalpha(ch)) {
            if(ch=='q')
                return;
            else
                throw std::runtime_error("Invalid input");
        }
        // user entered a number
        else {
            std::cin.unget();
            std::cin >> num;
        }

        std::cout << RESULT << convertNumTo(num,choice1,choice2) << std::endl;
    }
}

// number converter
std::string convertNumTo(int num, int choice1, int choice2) {
    if(choice1==3) {
        if(choice2==3)
            return std::to_string(num);
        else {
            int base{0};
            switch(choice2) {
                case 1:
                    base = 2;
                    break;
                case 2:
                    base = 8;
                    break;
                case 4:
                    base = 16;
                    break;
                default:
                    throw std::runtime_error("unknown base of number system");
            }
            return fromDecimalTo(num,base);
        }
    }
    else {
        if(choice2==3) {
            int base{0};
            switch(choice1) {
                case 1:
                    base = 2;
                    break;
                case 2:
                    base = 8;
                    break;
                case 4:
                    base = 16;
                    break;
                default:
                    throw std::runtime_error("unknown base of number system");
            }
            return toDecimalFrom(num,base);
        }
        else {
            int base1{0},base2{0};
            switch(choice1) {
                case 1:
                    base1 = 2;
                    break;
                case 2:
                    base1 = 8;
                    break;
                case 4:
                    base1 = 16;
                    break;
                default:
                    throw std::runtime_error("unknown base of number system");
            }
            switch(choice2) {
                case 1:
                    base2 = 2;
                    break;
                case 2:
                    base2 = 8;
                    break;
                case 4:
                    base2 = 16;
                    break;
                default:
                    throw std::runtime_error("unknown base of number system");
            }
            std::string numstr = toDecimalFrom(num,base1);
            return fromDecimalTo(std::stoi(numstr),base2);
        }
    }
}

std::string fromDecimalTo(int num, int base) {
    int i{1},temp{0};
    std::string numstr{0};
    if(num==0) return std::string{"0"};
    while(num>0) {
        temp = num%base;
        num = num/base;
        numstr = std::to_string(temp) + numstr;
        if(i%4==0) numstr = " " + numstr;
        i++;
    }
    return numstr;
}

std::string toDecimalFrom(int num, int base) {
    int temp{0},newnum{0},i{0};
    while(num>0) {
        temp = num%base;
        num = num/base;
        newnum = newnum + pow(base,i);
        i++;
    }

    return std::to_string(newnum);
}


// ask whether to continue or exit when an error occurs
bool ask() {
    while(true) {

    std::cout << "Do you want to continue(y/n)?" << std::endl;
    printline();
    char choice;
    std::cout << PROMPT;
    std::cin >> choice;

    std::cin.ignore(10,'\n');   // ignore the remaining data

    switch(choice) {
        case 'y':
        case 'Y':
            return 0;

        case 'n':
        case 'N':
            return 1;

        default:
            printline();
            std::cout << "Incorrect choice" << std::endl;
            break;
        }
    }
}

// print a line
void printline() {
    std::cout << LINE << std::endl;
}

// handle the expression calculation part
bool calculate() {
    std::cout << "Expression calculator program" << std::endl;
    std::cout << "Please enter the expression you want to calculate below" << std::endl;
    std::cout << "(NOTE: Enter q to QUIT and ; after the end of an expression)" << std::endl;

    while(true) {
    try {
        printline();
        std::cout << PROMPT;
        Token token=ts.get();

        // check whether input is expression or QUIT command
        if(token.kind==QUIT)
            return false;   // exit
        else if(token.kind==TERMINATOR)
            continue;   // read another expression
        else
            ts.unget(token);    // input is expression, unget and read expression()

        // calculate the expression
        double ans = expression();
        ts.flush();             // flush out remaining TERMINATOR(';')

        std::cout << RESULT << std::fixed << std::setprecision(5) << ans << std::endl;  // print the RESULT
    }
    catch(std::runtime_error &e) {
        printline();
        std::cout << "Error! ";
        std::cout << e.what() << std::endl;
        printline();

        std::cin.ignore(100,'\n');    // ignore until ; is reached
        ts.flush();             // flush buffer

        bool exit = ask();     // to continue or exit program?
        if(exit)
            break;
        }
    }
    return true;
}