#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>

// constanst used in the program
const char NUM_KIND     = '~';      // Token with this kind represents a number
const char PROMPT       = '>';      // prompt the user to enter an expression
const char RESULT       = '=';      // followed by the result of the expression
const char QUIT         = 'q';      // Quit character for the program
const char TERMINATOR   = ';';      // represents the end of an expression
const char ADD          = '+';           
const char SUBTRACT     = '-';
const char MULTIPLY     = '*';
const char DIVIDE       = '/';
const char OPEN_PARA    = '(';
const char CLOSE_PARA   = ')';
const char PI_CHAR      = 'P';
const char EULER_CONSTANT_CHAR = 'E';
const std::string LINE  = "-------------------------------------------------------------------------------------------";

const int CALCULATE_EXPRESSION = 1;
const int NUMBER_SYSTEM = 2;
const int MATRIX_CALC = 3;

// Scientific constants
const double PI = 3.14159265359;            // pi
const double EULER_CONSTANT  = 2.71828;     // e

// codes for bases
const int BINARY_BASE = 2;
const int OCTAL_BASE = 8;
const int DECIMAL_BASE = 10;
const int HEXADECIMAL_BASE = 16;

// codes for choices
const char BINARY       = '1';
const char OCTAL        = '2';
const char DECIMAL      = '3';
const char HEXADECIMAL  = '4';

const char LET = 'L';
const char NAME = 'N';
const std::string declaration_keyword = "let";

// handle the processes of the main menu and return the choice entered
int mainMenu();

void printline();       // print a line
void printMainMenu();   // print the main menu

void clearScreen();     // clear all the contents on the screen

#endif