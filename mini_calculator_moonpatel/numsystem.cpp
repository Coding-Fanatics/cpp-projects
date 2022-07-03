#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#include "Token.h"
#include "numsystem.h"
#include "utils.h"

void printNumConverterMainMenu() {
    // print the number converter menu
    std::cout << "1. Binary" << "\n";
    std::cout << "2. Octal" << "\n";
    std::cout << "3. Decimal" << "\n";
    std::cout << "4. Hexadecimal" << "\n";
}

// handles the number converting operation
void numberConverter() {
    char ch{0};
    char type1{0},type2{0};
    printNumConverterMainMenu();

    // Get first option
    std::cout << "Convert from: ";
    while(std::cin >> ch) {
        if(ch=='q')
            return;
        else {
            if(ch<BINARY || ch>HEXADECIMAL) {
                clearScreen();
                printNumConverterMainMenu();
                std::cout << "Convert from:";
            }
            else {
                type1 = ch;
                break;  // choice is correct, move ahead
            }
        }
    }

    // Get second option
    std::cout << "Convert to: ";
    while(std::cin >> ch) {
        if(ch=='q')
            return;
        else {
            if(ch<BINARY || ch>HEXADECIMAL) {
                clearScreen();
                printNumConverterMainMenu();
                std::cout << "Convert from: " << type1 << "\n";
                std::cout << "Convert to: ";
            }
            else {
                type2 = ch;
                break;  // choice is correct, move ahead
            }
        }
    }

    printline();

    // Input loop
    while(true) {
        std::cout << PROMPT << " ";
        std::string num{0};
        std::cin >> ch;

        // handle the quit operation
        if(ch=='q')
            return; // quit the program
        else if(ch==';')
            continue; // continue the next iteration
        // user entered a number
        else {
            std::cin.unget();
            std::cin >> num;
        }

    try {
        switch(type1) {
            case BINARY:
                std::cout << RESULT << convertBinTo(num,type2) << "\n";
                printline();
                break;
            case OCTAL:
                std::cout << RESULT << convertOctTo(num,type2) << "\n";
                printline();
                break;
            case DECIMAL:
                std::cout << RESULT << convertDecTo(num,type2) << "\n";
                printline();
                break;
            case HEXADECIMAL:
                std::cout << RESULT << convertHexTo(num,type2) << "\n";
                printline();
                break;
        }
    }
    // catch(std::runtime_error &e) {
    //     std::cout << e.what() << "\n";
    //     char choice{};

    //     while(true) {
    //         std::cout << "Do you want to exit? (y/n)" << "\n";
    //         std::cin >> choice;
    //         switch(choice) {
    //             case 'y': case 'Y':
    //                 return;
    //             case 'n': case 'N':
    //                 goto label1;
    //             default:
    //                 std::cout << "Invalid choice!" << "\n";
    //                 continue;
    //             }
    //         }
    //     }
    catch(...) {
        std::cout << "ERROR" << "\n";
        return;
    }
    }
}

// converts binary to the given base type
std::string convertBinTo(std::string num, char type) {
    std::string result{};
    if(!isBinary(num)) throw std::runtime_error("Entered number is not binary");
    switch(type) {
        case BINARY:
            result = formatBinary(num);
            break;

        case OCTAL:
        {
            for(int i=num.size()-1; i>=0;) {
                int count=0, number=0;
                while(count<3 && i>=0) {
                    number += pow(2,count)*stoi(std::string{num.at(i)});
                    count++;i--;
                }
                result = std::to_string(number) + result;
            }
            result = "0"+result;
        }
            break;

        case DECIMAL:
            result = binToDec(num);
            break;

        case HEXADECIMAL:
        {
            for(int i=num.size()-1; i>=0;) {
                int count=0, number=0;
                while(count<4 && i>=0) {
                    number += pow(2,count)*stoi(std::string{num.at(i)});
                    count++;i--;
                }
                if(number>9) {
                    char ch = number+55;
                    result = ch + result;
                }
                else
                    result = std::to_string(number) + result;
            }
            result = "0X" + result;
            break;
        }
    }
    return result;
}


// converts octal to given base type
std::string convertOctTo(std::string num, char type) {
    if(!isOctal(num)) throw std::runtime_error("Entered number is not octal");
    std::string result{};
    switch(type) {
        case BINARY:
        {
            std::string temp{};
            for(int i=num.size()-1; i>=0; i--) {
                temp = decToBin(std::string{num.at(i)});
                int count = 3-temp.size();
                if(i>0)
                    while(count--)
                        temp = "0" + temp;
                    result = temp+result;
            }
        }
            result = formatBinary(result);
            break;

        case OCTAL:
            result = num;
            break;

        case DECIMAL:
            result = convertOctTo(num,BINARY);
            result = binToDec(result);
            break;

        case HEXADECIMAL:
            result = convertOctTo(num,BINARY);
            result = convertBinTo(result,HEXADECIMAL);
            break;
    }
    return result;
}


// converts decimal to given base type
std::string convertDecTo(std::string num, char type) {
    if(!isDecimal(num)) throw std::runtime_error("Entered number is not decimal");
    std::string result{};
    switch(type) {
        case BINARY:
            result = formatBinary(decToBin(num));
            break;
            
        case OCTAL:
            result = decToBin(num);
            result = convertBinTo(result,OCTAL);
            break;

        case DECIMAL:
            result = num;
            break;

        case HEXADECIMAL:
            result = decToBin(num);
            result = convertBinTo(result,HEXADECIMAL);
            break;
    }
    return result;
}


// convert hexadecimal to the given base type
std::string convertHexTo(std::string num, char type) {
    if(!isHexadecimal(num)) throw std::runtime_error("Entered number is not hexadecimal");
    std::string result;
    switch(type) {
        case BINARY:
        {
            std::string temp{};
            for(int i=num.size()-1; i>=0; i--) {
                char c = toupper(num.at(i));
                std::string temp{};
                if((c<'A' || c>'F') && isalpha(c))
                    throw std::runtime_error("invalid hexadecimal number");
                
                if(isalpha(c))
                    temp = decToBin(std::to_string(int(c)-55));
                else
                    temp = decToBin(std::string{c});
                int count = 4-temp.size();
                while(count--)
                    temp = "0" + temp;

                result = temp + result;
            }
        }
            result = formatBinary(result);
            break;

        case OCTAL:
            result = convertHexTo(num,BINARY);
            result = convertBinTo(result,OCTAL);
            break;

        case DECIMAL:
            result = convertHexTo(num,BINARY);
            result = binToDec(result);
            break;

        case HEXADECIMAL:
            result = num;
            break;
    }
    return result;
}


// converts decimal to binary
std::string decToBin(std::string num) {
    std::string result;
    int number = stoi(num);
    int temp{0};
    while(number>0) {
        temp = number%2;
        number/=2;
        result = std::to_string(temp) + result;
    }
    return result;
}


// converts binary to decimal
std::string binToDec(std::string num) {
    int result{};
    for(int i=num.size()-1, j=0; i>=0; i--,j++)
        result += std::stoi(std::string{num.at(i)})*pow(2,j);
    return std::to_string(result);
}


// checking functions

// check if num is binary
bool isBinary(std::string num) {
    int size=num.size();
    for(int i=0; i<size; i++)
        if(num[i]!='0' && num[i]!='1') return false;
    return true;
}
// check if num is octal
bool isOctal(std::string num) {
    int size = num.size();
    for(int i=0; i<size; i++)
        if(num[i]<'0' || num[i] > '7') return false;
    return true;
}
// check if num is decimal
bool isDecimal(std::string num) {
    int size = num.size();
    for(int i=0; i<size; i++)
        if(num[i]<'0' || num[i]>'9') return false;
    return true;
}
// check if num is hexadecimal
bool isHexadecimal(std::string num) {
    int size = num.size();
    for(int i=0; i<size; i++) {
        char ch=toupper(num[i]);
        if(!((ch>='0' && ch<='9') || (ch>='A' && ch<='F'))) return false;
    }
    return true;
}


// format the binary number
std::string formatBinary(std::string num) {
    std::string result{};

    while(num.size()%4!=0)
        num = "0" + num;

    for(int i=num.size()-1; i>=0;) {
        int count = 4;
        while(i>=0 && count>0)  {
            result = num[i] + result;
            count--;
            i--;
        }
        if(i!=0)
            result = "," + result;
    }
    return result;
}