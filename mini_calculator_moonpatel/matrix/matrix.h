#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <iomanip>
#include <vector>

// class for a matrix
class matrix {
public:
    matrix();           // default constructor
    matrix(const std::vector<std::vector<int>> &v);     // constructor
    matrix(int row, int col);       // empty constructor
    matrix(const matrix &m);        // copy constructor
    matrix(matrix &&m);             // move constructor
    matrix &operator=(const matrix &mat);   // copy assignment
    matrix &operator=(matrix &&m);          // move assignment
    std::vector<int> &operator[](int row);  // subscript operator      
    int rowsize() const;      // get number of rows
    int colsize() const;      // get number of columns
    std::vector<std::vector<int>> &getmat();    // get matrix
private:
    std::vector<std::vector<int>> mat;
    int row;
    int col;
};

void matrixCalc();      // handles matrix calculations
void readMatrix(matrix &m);    // read a matrix from the input stream
std::vector<std::vector<int>> &multiplyMatrix();    // mulltiply two matrices

#endif