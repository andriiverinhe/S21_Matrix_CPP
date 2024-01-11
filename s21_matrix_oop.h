#pragma once
#include <vector>

#define MATRIX_DOUBLE_LOOP(rows, cols)                                         \
  for (int i = 0; i < (rows); i++)                                             \
    for (int j = 0; j < (cols); j++)


double **createArray(const int rows, const int cols);

class S21Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        S21Matrix();                 
        S21Matrix(int rows, int cols); 
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other) noexcept;
        ~S21Matrix();             

        bool EqSizeMatrix(const S21Matrix& other) const;
        bool EqMatrix(const S21Matrix& other) const;
        void SumMatrix(const S21Matrix& other); 
        void SubMatrix(const S21Matrix& other);

        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant() const;
        S21Matrix InverseMatrix();

        S21Matrix operator+(const S21Matrix& other) const;
        S21Matrix operator-(const S21Matrix& other) const;
        S21Matrix operator*(const S21Matrix& other) const;
        S21Matrix operator*(const double &number) const;
        S21Matrix& operator=(const S21Matrix& other);

        bool operator==(const S21Matrix &other) const;
        S21Matrix& operator+=(const S21Matrix &other);
        S21Matrix& operator-=(const S21Matrix &other);
        S21Matrix& operator*=(const S21Matrix &other);
        S21Matrix& operator*=(const double &number);

        // void printMatrix() const;
        // void fillRandom();
        int getRows_();
        int getCols_();
        void setRows_(int newRows);
        void setCols_(int newCols);
        double getMatrixValue(int i, int j);
        void setMatrixValue(int i, int j, double value);
        void setMatrixValue(std::vector<double>& values);


    private:
        bool checkIndex(const int i,const int j) const;
        bool checkSize() const;
        S21Matrix getMatrixMinor(const int rows_del, const int cols_del);
        void createMatrix();
        void deleteMatrix();
        void initMatrixZero();
        void copyMatrix(const S21Matrix& other);
};