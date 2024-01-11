#include "../s21_matrix_oop.h"
#include <iostream>

// Перегрузка оператора +
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  if (!EqSizeMatrix(other)) 
    throw std::logic_error("Incorrect matrix size for Sum");
  
  S21Matrix resultMatrix(this->rows_, this->cols_);

  MATRIX_DOUBLE_LOOP(this->rows_, this->cols_)
      resultMatrix.matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
  
  return resultMatrix;
}
// Перегрузка оператора -
S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
    if (!EqSizeMatrix(other)) 
      throw std::logic_error("Incorrect matrix size for Sub");

    S21Matrix resultMatrix(this->rows_, this->cols_);
    MATRIX_DOUBLE_LOOP(this->rows_, this->cols_)
      resultMatrix.matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    return resultMatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  if (this->cols_ != other.rows_)
    throw std::logic_error("Incorrect matrix size for Multiplication Matrix");

  S21Matrix resultMatrix(this->rows_, other.cols_);

  MATRIX_DOUBLE_LOOP(this->rows_, other.cols_)
    for (int k = 0; k < this->cols_; ++k) 
        resultMatrix.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      
  return resultMatrix;
}

S21Matrix S21Matrix::operator*(const double &number) const {
  S21Matrix resultMatrix(*this); // Создаем копию текущей матрицы
  MATRIX_DOUBLE_LOOP(this->rows_, this->cols_)
      resultMatrix.matrix_[i][j] *= number;
  return resultMatrix;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &number) {
  MulNumber(number);
  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    // Освобождаем ресурсы текущей матрицы

    this->deleteMatrix();

    // Копируем размеры
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;

    // Выделяем память под новую матрицу
    this->createMatrix();
    // Копируем данные
    this->copyMatrix(other);
    

  }
  return *this;
}