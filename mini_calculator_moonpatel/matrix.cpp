#include "matrix.h"

//====================================================================
// MATRIX CLASS MEMBER FUNCTIONS
//====================================================================
// default constructor
matrix::matrix()
    : mat{std::vector<std::vector<int>>{0,std::vector<int>{0}}},
        row{0}, col{0}  {}

// constructor
matrix::matrix(const std::vector<std::vector<int>> &v)
    : mat{v}, row{int(v.size())},col{int(v[0].size())} {}

// empty contructor
matrix::matrix(int row, int col) {
    this->mat={row,std::vector<int>{col,0}};
}

// copy constructor
matrix::matrix(const matrix &m) {
    this->row = m.rowsize();
    this->col = m.colsize();
    this->mat = m.mat;
}

// move constructor
matrix::matrix(matrix &&m) {
    this->mat = m.mat;
    this->row = m.row;
    this->col = m.col;
    m.mat = std::vector<std::vector<int>>{};
    m.row=0;
    m.col=0;
}


// copy assignment operator
matrix &matrix::operator=(const matrix &m) {
    this->row = m.rowsize();
    this->col = m.colsize();
    return *this;
}

// move assignment operator
matrix &matrix::operator=(matrix &&m) {
    this->mat = m.mat;
    this->row = m.row;
    this->col = m.col;
    m.mat = std::vector<std::vector<int>>{};
    m.row=0;
    m.col=0;
}

// subscript operator
std::vector<int> &matrix::operator[](int row) {
    return this->mat[row];
}

// get number of rows
int matrix::rowsize() const {
    return this->row;
}

// get number of colums
int matrix::colsize() const {
    return this->col;
}


//================================================================
// MATRIX CALCULATION FUNCTIONS
//================================================================
// handle matrix calculations
void matrixCalc() {
    int row1=0,row2=0,col1=0,col2=0;

    // input for matrix1
    matrix mat1;
    readMatrix(mat1);
    // // input for matrix1
    // std::cout << "Matrix 1:\n";
    // std::cout << "Row: ";
    // std::cin >> row1;
    // std::cout << "Column: ";
    // std::cin >> col1;
    // std::vector<std::vector<int>> mat1(row1,std::vector<int>(row1,0));
    // std::cout << "Matrix:\n";
    // for(int i=0; i<row1; i++)
    //     for(int j=0; j<col1; j++)
    //         std::cin >> mat1[i][j];

    // input for matrix2
    matrix mat2;
    readMatrix(mat2);

    // input for matrix2
    // std::cout << "Matrix 2: \n";
    // std::cout << "Row: ";
    // std::cin >> row2;
    // std::cout << "Column: ";
    // std::cin >> col2;
    // std::vector<std::vector<int>> mat2(row2,std::vector<int>(row2,0));
    // std::cout << "Matrix:\n";
    // for(int i=0; i<row2; i++)
    //     for(int j=0; j<col2; j++)
    //         std::cin >> mat2[i][j];

    row1 = mat1.rowsize();
    col1 = mat1.colsize();
    row2 = mat2.rowsize();
    col2 = mat2.colsize();

    // if matrices do not satisfy condition for multiplication
    if(mat1.colsize()!=mat2.rowsize()) {
        std::cout << "Cannot multiply given matrices\n";
        std::cout << "Quitting\n";
        return;
    }

    // resultant matrix
    matrix result(row1,col2);

    // calculate the matrix - simple matrix multiplication algorithm
    for(int i=0; i<col1; i++) {
        for(int j=0; j<row2; j++) {
            for(int k=0; k<col1; k++) {
                result[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }

    // print the matrix
    for(int i=0; i<row1; i++) {
        for(int j=0; j<col2; j++) {
            std::cout << std::setw(3) << result[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void readMatrix(matrix &m) {
    int i=0,j=0;
    std::vector<std::vector<int>> v;
    std::vector<int> subv;

    while(true) {
        char ch;
        std::cin.get(ch);
        if(ch=='\n') {
            v.push_back(subv);
            continue;
        }
        else if(ch==';') {
            break;
        }
        else {
            int num=0;
            std::cin >> num;
            subv.push_back(num);
        }
    }
    m = matrix(v);
}