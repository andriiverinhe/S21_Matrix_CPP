#include "../s21_matrix_oop.h"
#include <iostream>
bool S21Matrix::checkSize() const { return (rows_ > 0 && cols_ > 0); }

bool S21Matrix::checkIndex(const int i,const int j) const {
  bool i_ = (i >= 0 && i < rows_);  
  bool j_ = (j >= 0 && j < cols_);  
  return (i_ && j_);
}

void S21Matrix::initMatrixZero() {
  MATRIX_DOUBLE_LOOP(rows_, cols_)
    matrix_[i][j] = 0;
}

// void S21Matrix::printMatrix() const {
//   std::cout << std::fixed;
//   std::cout.precision(7);
//   std::cout << "Matrix: " << std::endl;
//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       std::cout << "'" << matrix_[i][j] << "'"
//                 << "\t";
//     }
//     std::cout << std::endl;
//   }
//   std::cout << "_____________" << std::endl;
//   std::cout.precision(2);
// }

void S21Matrix::copyMatrix(const S21Matrix &other) {
  MATRIX_DOUBLE_LOOP(other.rows_, other.cols_)
    this->matrix_[i][j] = other.matrix_[i][j];
}

// void S21Matrix::fillRandom() {
//   // Инициализируем генератор случайных чисел текущим временем
//   srand(static_cast<unsigned>(time(nullptr)));

//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       matrix_[i][j] = rand() % 100; // Заполняем случайными числами от 0 до 99
//                                     // (можете изменить диапазон)
//     }
//   }
// }

void S21Matrix::setMatrixValue(std::vector<double> &values) {
  if((rows_ * cols_) != (int)values.size())
    throw std::invalid_argument("size vector != size matrix_");
  int count = 0;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] = values[count++];
}

bool S21Matrix::EqSizeMatrix(const S21Matrix &other) const {
  return (other.cols_ == this->cols_ && other.rows_ == this->rows_);
}


S21Matrix S21Matrix::getMatrixMinor(const int rows_del, const int cols_del) {
  int res_rows = 0;
  int res_cols = 0;
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    if (i == rows_del)
      continue;
    res_cols = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == cols_del)
        continue;
      result.matrix_[res_rows][res_cols] = matrix_[i][j];
      res_cols++;
    }
    res_rows++;
  }
  return result;
}

int S21Matrix::getRows_() {
  return this->rows_;
}
int S21Matrix::getCols_() {
  return this->cols_;
}

double **createArray(const int rows, const int cols) {
  double** newMatrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        newMatrix[i] = new double[cols];
    }
    return newMatrix;
}

void S21Matrix::setRows_(int newRows){
  if (newRows <= 0){
    throw std::invalid_argument("Number of rows must be positive");
  }

  // Создаем новую матрицу с новыми размерами
  double** newMatrix = createArray(newRows, this->cols_);

  // Копируем значения из старой матрицы в новую
  MATRIX_DOUBLE_LOOP(std::min(rows_, newRows), cols_)
    newMatrix[i][j] = matrix_[i][j];

  // Заполняем новые строки нулями
  for (int i = rows_; i < newRows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      newMatrix[i][j] = 0.0;
    }
  }

  deleteMatrix();
  // Указываем на новую матрицу
  matrix_ = newMatrix;
  rows_ = newRows;
}

void S21Matrix::setCols_(int newCols) {
    if (newCols <= 0) 
      throw std::invalid_argument("Number of rows must be positive");
    

    // Создаем новую матрицу с новыми размерами
    double** newMatrix = createArray(this->rows_, newCols);

    // Копируем значения из старой матрицы в новую
    MATRIX_DOUBLE_LOOP(rows_, std::min(cols_, newCols))
      newMatrix[i][j] = matrix_[i][j];


     // Заполняем новые строки нулями
    for (int i = 0; i < rows_; ++i) {
        for (int j = cols_; j < newCols; ++j) {
            newMatrix[i][j] = 0.0;
        }
    }

    // Освобождаем память, занимаемую старой матрицей
    deleteMatrix();

    // Указываем на новую матрицу
    matrix_ = newMatrix;
    cols_ = newCols;
}


double S21Matrix::getMatrixValue(int i, int j) {
  if(!checkIndex(i, j))
    throw std::invalid_argument("Некорректные значения rows или cols");

  double value = 0.0;
  value = matrix_[i][j]; 
  
  return value;
}
void S21Matrix::setMatrixValue(int i, int j, double value){
  if(!checkIndex(i, j))
    throw std::invalid_argument("Некорректные значения rows или cols");
  matrix_[i][j] = value; 
}