#include "../s21_matrix_oop.h"
#include <iostream>

void S21Matrix::createMatrix() {
  if(!checkSize())
    throw std::invalid_argument("Некорректные значения rows или cols");

  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) 
      matrix_[i] = new double[cols_];
}

void S21Matrix::deleteMatrix() {
  if(matrix_) {
    for (int i = 0; i < rows_; ++i) { 
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) {
  createMatrix();    
  initMatrixZero();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  createMatrix();
  initMatrixZero();
}

S21Matrix::S21Matrix(const S21Matrix &other): rows_(other.rows_), cols_(other.cols_) {
  createMatrix();
  copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  // Обнуляем указатель в объекте-источнике, чтобы избежать удаления одних и тех же данных
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { deleteMatrix(); }