#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

#include "Token.h"
#include "numsystem.h"

// handles the number converting operation
void numberConverter() {
    char type1{0},type2{0};
    // Print options for the user
    std::cout << "1. Binary" << std::endl;
    std::cout << "2. Octal" << std::endl;
    std::cout << "3. Decimal" << std::endl;
    std::cout << "4. Hexadecimal" << std::endl;

    // Get first option
    std::cout << "Number system you want to convert from: ";
    while(std::cin >> type1) {
        if(type1<BINARY || type1>HEXADECIMAL){
            std::cout << "Please enter an appropriate option" << std::endl;
            printline();
            std::cout << "Number system you want to convert from: ";
        }
        else
            break;  // choice is correct move ahead
    }

    // Get second option
    std::cout << "Number system you want to convert to: ";
    while(std::cin >> type2) {
        if(type2<BINARY || type2>HEXADECIMAL) {
            std::cout << "Please enter an appropriate option" << std::endl;
            printline();
            std::cout << "Number system you want to convert to: ";
        }
        else
            break;  // choice is correct move ahead
    }

    std::cout << "Enter the number: " << std::endl;

    // Input loop
    while(true) {
label1:
        std::cout << PROMPT;
        std::string num{0};     char ch{0};
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
                std::cout << RESULT << convertBinTo(num,type2) << std::endl;
                printline();
                break;
            case OCTAL:
                std::cout << RESULT << convertOctTo(num,type2) << std::endl;
                printline();
                break;
            case DECIMAL:
                std::cout << RESULT << convertDecTo(num,type2) << std::endl;
                printline();
                break;
            case HEXADECIMAL:
                std::cout << RESULT << convertHexTo(num,type2) << std::endl;
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


// chaecking functions

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
    int size = num.size();

    for(int i=size-1; i>=0;) {
        int count = 4;
        while(i>=0 && count>0)  {
            result = num[i] + result;
            count--;
            i--;
        }
        if(i!=0)
            result = " " + result;
    }
    return result;
}