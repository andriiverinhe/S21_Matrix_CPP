#include "../s21_matrix_oop.h"
#include <cmath>
#include <iostream>

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool code = true;
  if (EqSizeMatrix(other)) {
    for (int i = 0; (i < this->rows_) && code; i++)
      for (int j = 0; (j < this->cols_) && code; j++)
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 0.0000001)
          code = false;
  } else code = false;
  return code;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!EqSizeMatrix(other))
    throw std::logic_error("Different matrix dimensions");

  MATRIX_DOUBLE_LOOP(this->rows_, this->cols_)
    this->matrix_[i][j] += other.matrix_[i][j];
}
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!EqSizeMatrix(other))
    throw std::logic_error("Different matrix dimensions");

  MATRIX_DOUBLE_LOOP(this->rows_, this->cols_)
    this->matrix_[i][j] -= other.matrix_[i][j];
}
void S21Matrix::MulNumber(const double num) {
  MATRIX_DOUBLE_LOOP(this->rows_, this->cols_)
    this->matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ == other.rows_) {
    S21Matrix resultMatrix(this->rows_, other.cols_);
    MATRIX_DOUBLE_LOOP(this->rows_, other.cols_) {
      for (int k = 0; k < this->cols_; ++k) {
        resultMatrix.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
    // Освобождаем ресурсы текущей матрицы перед перемещением
    this->deleteMatrix();
    // Перемещаем ресурсы из временной матрицы в текущую
    *this = std::move(resultMatrix);
  } else 
    throw std::logic_error("The number of columns of the first matrix is not equal to the number of rows of the second matrix");

}

S21Matrix S21Matrix::Transpose() {
  S21Matrix resultMatrix(cols_, rows_);
  MATRIX_DOUBLE_LOOP(this->rows_, this->cols_)
    resultMatrix.matrix_[j][i] = matrix_[i][j];
  return resultMatrix;
}


S21Matrix S21Matrix::CalcComplements() {
  S21Matrix resultMatrix(cols_, rows_);
  if (rows_ == cols_ && rows_ >= 2) {
    MATRIX_DOUBLE_LOOP(rows_, cols_) {
      S21Matrix minor = this->getMatrixMinor(i, j);
      double determinant = 0.0;
      determinant = minor.Determinant();
      resultMatrix.matrix_[i][j] = pow(-1, (i + j)) * determinant;
    }
  } else 
    throw std::logic_error("The matrix is not square");
  return resultMatrix;
}

// Рекурсивный метод для расчета детерминанта
double S21Matrix::Determinant() const {
  if (rows_ != cols_)
    throw std::logic_error("The matrix is not square");

  // Базовый случай: если матрица 1x1, то ее детерминант равен элементу матрицы
  if (rows_ == 1) 
    return matrix_[0][0];

  double det = 0.0;
  int sign = 1;

  for (int i = 0; i < cols_; ++i) {
    // Раскладываем матрицу по первой строке
    S21Matrix subMatrix(rows_ - 1, cols_ - 1);

    for (int j = 1; j < rows_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        if (k < i) {
          subMatrix.matrix_[j - 1][k] = matrix_[j][k];
        } else if (k > i) {
          subMatrix.matrix_[j - 1][k - 1] = matrix_[j][k];
        }
      }
    }
    // Рекурсивно вычисляем детерминант подматрицы
    det += sign * matrix_[0][i] * subMatrix.Determinant();
    sign = -sign; // Меняем знак для следующей итерации
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  S21Matrix resultMatrix = *this;
  if(fabs(determinant) > 1e-7) {
    if(rows_ == 1) {
      resultMatrix.matrix_[0][0] = 1 / determinant;
    } else {
      resultMatrix = this->Transpose().CalcComplements();
      resultMatrix.MulNumber(1.0 / determinant);
    }
  } else 
   throw std::logic_error("Determinant must be non-zero to calculate Inverse");
  return resultMatrix;
}