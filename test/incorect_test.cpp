#include "main_test.h"


TEST_F(INCORRECT_TEST, TEST_STRUCT1) {
    ASSERT_THROW(S21Matrix mat(-1, -1), std::invalid_argument);
    ASSERT_THROW(S21Matrix mat(1, -1), std::invalid_argument);
    ASSERT_THROW(S21Matrix mat(-1, 1), std::invalid_argument);
}

TEST_F(INCORRECT_TEST, TEST_STRUCT2) {
 std::vector<double> values1 = {1};
    std::vector<double> values2 = {2,2,2,2};

    S21Matrix trueMat;
    S21Matrix mat1(1, 1);
    S21Matrix mat2(2, 2);
    mat1.setMatrixValue(values1);
    mat2.setMatrixValue(values2);
    ASSERT_THROW(mat1 + mat2, std::logic_error);
    ASSERT_THROW(mat1 - mat2, std::logic_error);
    ASSERT_THROW(mat1 * mat2, std::logic_error);
}


TEST_F(INCORRECT_TEST, TEST_STRUCT3) {
    std::vector<double> values1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> values2 = {1, 2, 2, 2, 5, 6, 7, 8, 9};
    S21Matrix mat1(3, 3);
    S21Matrix mat2(3, 3);
    mat1.setMatrixValue(values1);
    mat2.setMatrixValue(values2);
    EXPECT_FALSE(mat1.EqMatrix(mat2));
}

TEST_F(INCORRECT_TEST, TEST_STRUCT4) {
 std::vector<double> values1 = {1};
    std::vector<double> values2 = {2,2,2,2};

    S21Matrix mat1(1, 1);
    S21Matrix mat2(2, 2);
    mat1.setMatrixValue(values1);
    S21Matrix trueMat = mat1;
    mat2.setMatrixValue(values2);
    
    ASSERT_THROW(mat1.SumMatrix(mat2), std::logic_error);
    ASSERT_THROW(mat1.SubMatrix(mat2), std::logic_error);
    ASSERT_THROW(mat1.MulMatrix(mat2), std::logic_error);
}

TEST_F(INCORRECT_TEST, TEST_STRUCT5) {
    S21Matrix mat;

    EXPECT_TRUE((mat.getRows_() == 3));
    EXPECT_TRUE((mat.getCols_() == 3));
}


TEST_F(INCORRECT_TEST, TEST_STRUCT6) {
 std::vector<double> values1 = {1};
    std::vector<double> values2 = {2,2,2,2};

    S21Matrix trueMat;
    S21Matrix mat1(1, 1);
    S21Matrix mat2(2, 2);
    mat1.setMatrixValue(values1);
    mat2.setMatrixValue(values2);
    ASSERT_THROW(mat2 + mat1, std::logic_error);
    ASSERT_THROW(mat2 * mat1, std::logic_error);
    ASSERT_THROW(mat2 - mat1, std::logic_error);
}

TEST_F(INCORRECT_TEST, TEST_STRUCT7) {
 std::vector<double> values1 = {1,2};
    std::vector<double> values2 = {2,2,2,2};

    S21Matrix mat1(1, 2);
    S21Matrix mat2(2, 2);
    mat1.setMatrixValue(values1);
    mat2.setMatrixValue(values2);
    S21Matrix trueMat = mat2;

    ASSERT_THROW(mat2.SumMatrix(mat1), std::logic_error);
    ASSERT_THROW(mat2.SubMatrix(mat1), std::logic_error);
    ASSERT_THROW(mat2.MulMatrix(mat1), std::logic_error);
}
TEST_F(INCORRECT_TEST, TEST_STRUCT8) {
 std::vector<double> values1 = {1,2};
    std::vector<double> values2 = {2,2,2,2};

    S21Matrix mat1(2, 1);
    S21Matrix mat2(2, 2);
    mat1.setMatrixValue(values1);
    S21Matrix trueMat = mat1;
    mat2.setMatrixValue(values2);
    ASSERT_THROW(mat1.SumMatrix(mat2), std::logic_error);
    ASSERT_THROW(mat1.SubMatrix(mat2), std::logic_error);
    ASSERT_THROW(mat1.MulMatrix(mat2), std::logic_error);
    ASSERT_THROW(mat1.CalcComplements(), std::logic_error);
    ASSERT_THROW(mat1.Determinant(), std::logic_error);
    ASSERT_THROW(mat2.InverseMatrix(), std::logic_error);
    EXPECT_FALSE(mat1.EqMatrix(mat2));
}

TEST_F(INCORRECT_TEST, TEST_STRUCT9) {
    S21Matrix a(2,2);
    ASSERT_THROW(a.setCols_(-32), std::invalid_argument);
    ASSERT_THROW(a.setCols_(0), std::invalid_argument);
    ASSERT_THROW(a.setRows_(-32), std::invalid_argument);
    ASSERT_THROW(a.setRows_(0), std::invalid_argument);
    a.setCols_(32);
    a.setRows_(32);
    EXPECT_EQ(a.getCols_(), 32);
    EXPECT_EQ(a.getRows_(), 32);
    a.setCols_(9);
    a.setRows_(2);
    EXPECT_EQ(a.getCols_(), 9);
    EXPECT_EQ(a.getRows_(), 2);
}

TEST_F(INCORRECT_TEST, TEST_STRUCT10) {
    S21Matrix mat;
    S21Matrix mat2;
    mat = mat2;
    EXPECT_TRUE(mat.EqMatrix(mat2));
}
TEST_F(INCORRECT_TEST, TEST_STRUCT11) {
    ASSERT_THROW(S21Matrix a(__INT_MAX__, __INT_MAX__), std::bad_alloc);
}

TEST_F(INCORRECT_TEST, TEST_IN_SETVALUE_1) {
    S21Matrix matrix(5, 1);
    ASSERT_THROW(matrix.setMatrixValue(1, -1, 2), std::invalid_argument);
}
TEST_F(INCORRECT_TEST, TEST_IN_SETVALUE_2) {
    S21Matrix matrix(5, 1);
    ASSERT_THROW(matrix.setMatrixValue(-1, 1, 2), std::invalid_argument);
}

TEST_F(INCORRECT_TEST, TEST_IN_SETVALUE_3) {
    S21Matrix matrix(5, 1);
    ASSERT_THROW(matrix.setMatrixValue(1, 6, 2), std::invalid_argument);
}
TEST_F(INCORRECT_TEST, TEST_IN_SETVALUE_4) {
    S21Matrix matrix(5, 1);
    ASSERT_THROW(matrix.setMatrixValue(6, 2, 2), std::invalid_argument);
}


TEST_F(INCORRECT_TEST, TEST_IN_SETVALUE_6) {
    S21Matrix matrix(5, 1);
    ASSERT_THROW(matrix.setMatrixValue(-23, -23, 2), std::invalid_argument);
}

TEST_F (INCORRECT_TEST, EQ_MATRIX_TEST_1) {
    S21Matrix mat1(2, 2);
    S21Matrix mat2(2, 2);
    std::vector<double> values1 = {1, 2, 3, 4};
    std::vector<double> values2 = {1, 2, 4, 3};
    mat1.setMatrixValue(values1);
    mat2.setMatrixValue(values2);
    EXPECT_FALSE(mat1.EqMatrix(mat2));
}

// TEST_F (INCORRECT_TEST, EQ_MATRIX_TEST_2) {
//     std::cout << "_______" << std::endl;
//     S21Matrix mat1(2, -2);
//     int cols = mat1.getCols_();
//     (void)cols;
//     double values = mat1.getMatrixValue(1,1);
//     std::cout << cols << " " << values << std::endl;
//     std::cout << "_______" << std::endl;

// }

TEST_F(INCORRECT_TEST, MATRIX_DEL_TEST_1) {
    S21Matrix mat(3, 3);
}

TEST_F(INCORRECT_TEST, MATRIX_GETVALUE_TEST_1) {
    S21Matrix mat(3, 3);
    ASSERT_THROW(mat.getMatrixValue(-10, 2), std::invalid_argument);
    ASSERT_THROW(mat.getMatrixValue(1, -120), std::invalid_argument);
}