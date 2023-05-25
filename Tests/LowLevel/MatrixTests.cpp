#include "gtest/gtest.h"

#include "../../LowLevel/Matrix.h"
#include "../../Exceptions/MatrixError.h"


//  region constructs
TEST(MatrixConstructsTests, MatrixConstructsDiffType) {
    Matrix<long long> mat_ll(10, 10);
    Matrix<int> mat_int(10, 10);
    ASSERT_TRUE(mat_ll == mat_int);
}

TEST(MatrixConstructsTests, MatrixConstructsDiffSize) {
    Matrix<long long> mat_ll(12, 10);
    Matrix<int> mat_int(10, 12);
    ASSERT_FALSE(mat_ll == mat_int);
}

TEST(MatrixConstructsTests, MatrixConstructsFill) {
    Matrix<long long> mat_ll(12, 10, 1);
    Matrix<int> mat_int(12, 10, 1);
    bool flag = false;
    for (size_t i = 0; i < 12; ++i){
        for (size_t j = 0; j < 10; ++j){
            flag = (mat_ll[i][j] != mat_int[i][j] || mat_ll[i][j] != 1 || mat_int[i][j]!= 1);
            if (flag) break;
        }
    }
    ASSERT_FALSE(flag);
}
//  endregion

//  region operators
//  region equal
TEST(MatrixOperatorsTests, MatrixEqqDiffWidth) {
    Matrix<int> mat = Matrix<int>({{1, 2, 2}, {3, 4, 4}, {5, 6, 6}}),
                mat1 = Matrix<int>({{1, 2}, {3, 4}, {5, 6}});
    ASSERT_FALSE(mat == mat1);
}

TEST(MatrixOperatorsTests, MatrixEqqDiffHeight){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}, {5, 6}}),
                mat1 = Matrix<int>({{1, 2}, {3, 4}});
    ASSERT_FALSE(mat == mat1);
}

TEST(MatrixOperatorsTests, MatrixEqqDiffElem){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}, {5, 6}}),
                mat1 = Matrix<int>({{1, 2}, {3, 4}, {5, 7}});
    ASSERT_FALSE(mat == mat1);
}

TEST(MatrixOperatorsTests, MatrixEqqEqualElem){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}, {5, 6}}),
                mat1 = Matrix<int>({{1, 2}, {3, 4}, {5, 6}});
    ASSERT_TRUE(mat == mat1);
}
//  endregion

// region addition
TEST(MatrixOperatorsTests, MatrixSuccessAddSameSize){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}, {5, 6}}),
                mat1 = Matrix<int>({{1, 1}, {2, 2}, {3, 3}});
    Matrix<int> res_mat = Matrix<int>({{2, 3}, {5, 6}, {8, 9}});
    ASSERT_TRUE((mat + mat1) == res_mat);
}

TEST(MatrixOperatorsTests, MatrixAddDiffSizeHeight){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}}),
                mat1 = Matrix<int>({{1, 1}, {2, 2}, {3, 3}});
    ASSERT_THROW(mat + mat1, MatrixSizeError);
}

TEST(MatrixOperatorsTests, MatrixAddDiffSizeWidth){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}}),
            mat1 = Matrix<int>({{1, 1, 3}, {2, 2, 3}});
    ASSERT_THROW(mat + mat1, MatrixSizeError);
}

TEST(MatrixOperatorsTests, MatrixAddDiffSizeHeightAndWidth){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}, {5, 6}}),
            mat1 = Matrix<int>({{1, 1, 3}, {2, 2, 3}});
    ASSERT_THROW(mat + mat1, MatrixSizeError);
}
//  endregion

//  region subtraction
TEST(MatrixOperatorsTests,  MatrixSuccessSubSameSize){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}, {5, 6}}),
                mat1 = Matrix<int>({{1, 1}, {2, 2}, {3, 3}});
    Matrix<int> res_mat = Matrix<int>({{0, 1}, {1, 2}, {2, 3}});

    ASSERT_TRUE(mat - mat1 == res_mat);
}

TEST(MatrixOperatorsTests, MatrixSubDiffSizeHeight){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}}),
            mat1 = Matrix<int>({{1, 1}, {2, 2}, {3, 3}});
    ASSERT_THROW(mat - mat1, MatrixSizeError);
}

TEST(MatrixOperatorsTests, MatrixSubDiffSizeWidth){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}}),
            mat1 = Matrix<int>({{1, 1, 3}, {2, 2, 3}});
    ASSERT_THROW(mat - mat1, MatrixSizeError);
}

TEST(MatrixOperatorsTests, MatrixSubDiffSizeHeightAndWidth){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}, {5, 6}}),
            mat1 = Matrix<int>({{1, 1, 3}, {2, 2, 3}});
    ASSERT_THROW(mat - mat1, MatrixSizeError);
}
//  endregion

//  region multiplication_by_matrix
TEST(MatrixOperatorsTests, MatrixSuccessMul){
    Matrix<int> mat = Matrix<int>({{1, 2, 1}, {3, 4, 2}}),
                mat1 = Matrix<int>({{1, 1}, {2, 2}, {3, 3}});
    Matrix<int> res_mat = Matrix<int>({{8, 8}, {17, 17}});

    ASSERT_TRUE(mat * mat1 == res_mat);
}

TEST(MatrixOperatorsTests, MatrixSuccessMulIntFloat){
    Matrix<int> mat = Matrix<int>({{1, 2, 1}, {3, 4, 2}});
    Matrix<float> mat1 = Matrix<float>({{1, 1}, {2, 2}, {3, 3}});
    Matrix<int> res_mat = Matrix<int>({{8, 8}, {17, 17}});
    ASSERT_TRUE(mat * mat1 == res_mat);
}

TEST(MatrixOperatorsTests, MatrixIncrorrectMul){
    Matrix<int> mat = Matrix<int>({{1, 2, 1}, {3, 4, 2}}),
            mat1 = Matrix<int>({{1, 1, 3}, {2, 2, 3}});
    ASSERT_THROW(mat * mat1, MatrixSizeError);
}
//  endregion

//  region multiplication_by_scalar
TEST(MatrixOperatorsTests, MatrixIntMulInt){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}});
    int a = 10;
    Matrix<int> res_mat = Matrix<int>({{10, 20}, {30, 40}});
    ASSERT_TRUE(mat * a == res_mat);
}

TEST(MatrixOperatorsTests, MatrixIntMulFloat){
    Matrix<int> mat = Matrix<int>({{1, 2}, {3, 4}});
    float a = 10.2;
    Matrix<int> res_mat = Matrix<int>({{10, 20}, {30, 40}});
    ASSERT_TRUE(mat * a == res_mat);
}

TEST(MatrixOperatorsTests, MatrixFloatMulInt){
    Matrix<float> mat = Matrix<float>({{1.0, 2.0}, {3.0, 4.0}});
    int a = 10;
    Matrix<float> res_mat = Matrix<float>({{10.0, 20.0}, {30.0, 40.0}});
    ASSERT_TRUE(mat * a == res_mat);
}

TEST(MatrixOperatorsTests, MatrixFloatMulFloat){
    Matrix<float> mat = Matrix<float>({{1.0, 2.0}, {3.0, 4.0}});
    float a = 10.2;
    Matrix<float> res_mat = Matrix<float>({{10.2, 20.4}, {30.6, 40.8}});
    ASSERT_TRUE(res_mat.equalPrecision(mat * a, 10e-3));
}
//  endregion

//  region div by matrix
TEST(MatrixOperatorsTests, MatrixDivSuccess){
    Matrix<int> mat = Matrix<int>({
                                          {1, 2, 7},
                                          {3, 4, 3}
                                  }),
            mat1 = Matrix<int>({
                                       {1, 2, -1},
                                       {-2, 0, 1},
                                       {1, -1, 0}
                               });
    Matrix<int> res_mat = Matrix<int>({
                                              {17, 24, 32},
                                              {13, 16, 22},
                                      });
    Matrix<long double> inv_mat1 = mat1.inverse();
    Matrix<int> calc_mat = mat / mat1;
    ASSERT_TRUE(calc_mat == res_mat);
}

TEST(MatrixOperatorsTests, MatrixDivIncorrectSize){
    Matrix<int> mat = Matrix<int>({
                                          {1, 2, 7},
                                          {3, 4, 3}
                                  }),
            mat1 = Matrix<int>({
                                       {1, 2, -1},
                                       {-2, 0, 1},
                                       {1, -1, 0}
                               });

    ASSERT_THROW(mat1 / mat, MatrixSizeError);
}

TEST(MatrixOperatorsTests, MatrixDivIncorrectNotSquare){
    Matrix<int> mat = Matrix<int>({
                                          {1, 2},
                                          {3, 4}
                                  }),
            mat1 = Matrix<int>({
                                       {3, 1, 2},
                                       {3, 2, 3},
                               });

    ASSERT_THROW(mat / mat1, MatrixSizeError);
}

TEST(MatrixOperatorsTests, MatrixDivIncorrectDegenerate){
    Matrix<int> mat = Matrix<int>({
                                          {1, 2, 7},
                                          {3, 4, 3}
                                  }),
            mat1 = Matrix<int>({
                                       {1, 2, 3},
                                       {4, 5, 6},
                                       {7, 8, 9}
                               });

    ASSERT_THROW(mat / mat1, MatrixClassificationError);
}
//  endregion

//  region div by scalar
TEST(MatrixOperatorsTests, MatrixIntDivInt){
    Matrix<int> mat = Matrix<int>({{10, 20}, {30, 40}});
    int a = 10;
    Matrix<int> res_mat = Matrix<int>({{1, 2}, {3, 4}});
    ASSERT_TRUE(mat / a == res_mat);
}

TEST(MatrixOperatorsTests, MatrixIntDivFloat){
    Matrix<int> mat = Matrix<int>({{10, 20}, {30, 40}});
    float a = 10.2;
    Matrix<int> res_mat = Matrix<int>({{1, 2}, {3, 4}});
    ASSERT_TRUE(mat / a == res_mat);
}

TEST(MatrixOperatorsTests, MatrixFloatDivInt){
    Matrix<float> mat = Matrix<float>({{10.0, 20.0}, {30.0, 40.0}});
    int a = 10;
    Matrix<float> res_mat = Matrix<float>({{1.0, 2.0}, {3.0, 4.0}});
    ASSERT_TRUE(mat / a == res_mat);
}

TEST(MatrixOperatorsTests, MatrixFloatDivFloat){
    Matrix<float> mat = Matrix<float>({{10.2, 20.4}, {30.6, 40.8}});
    float a = 10.2;
    Matrix<float> res_mat = Matrix<float>({{1.0, 2.0}, {3.0, 4.0}});
    ASSERT_TRUE(mat / a == res_mat);
}
//  endregion
//  endregion

//  region methods
//  region transpose
TEST(MatrixMethodsTests, MatrixTSquare){
    Matrix<int> mat({
                            {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9}
                    }),
            res_mat({
                            {1, 4, 7},
                            {2, 5, 8},
                            {3, 6, 9}
                    });

    mat.transpose();
    ASSERT_EQ(mat, res_mat);
}

TEST(MatrixMethodsTests, MatrixTNotSquare){
    Matrix<int> mat({
                            {1, 2, 3},
                            {4, 5, 6},
                    }),
            res_mat({
                            {1, 4},
                            {2, 5},
                            {3, 6}
                    });
    mat.transpose();
    ASSERT_EQ(mat, res_mat);
}

TEST(MatrixMethodsTests, MatrixTOne){
    Matrix<int> mat({
                            {2},
                    }),
            res_mat({
                            {2}
                    });

    ASSERT_TRUE(mat == res_mat);
}
//  endregion

//  region equal_with_precision
TEST(MatrixMethodsTests, MatrixEqPreCorrectFalse){
    Matrix<float> mat({{1, 2}, {3, 4}}),
            mat1({{1.003, 2.002}, {3.001, 4}});
    float precision = 10e-5;
    ASSERT_FALSE(mat.equalPrecision(mat1, precision));
}
TEST(MatrixMethodsTests, MatrixEqPreCorrectTrue){
    Matrix<float> mat({{1, 2}, {3, 4}}),
            mat1({{1.003, 2.002}, {3.001, 4}});
    float precision = 0.01;
    ASSERT_TRUE(mat.equalPrecision(mat1, precision));
}

TEST(MatrixMethodsTests, MatrixEqPreDiffWidth){
    Matrix<float> mat({{1, 2}, {3, 4}}),
            mat1({{1.003, 2.002}, {3.001, 4}, {0, 0}});
    float precision = 10e-5;
    ASSERT_FALSE(mat.equalPrecision(mat1, precision));
}

TEST(MatrixMethodsTests, MatrixEqPreDiffHeight){
    Matrix<float> mat({{1, 2}, {3, 4}}),
            mat1({{1.003, 2.002, 0}, {3.001, 4, 0}});
    float precision = 10e-5;
    ASSERT_FALSE(mat.equalPrecision(mat1, precision));
}
//  endregion

//  region determinant
TEST(MatrixMethodsTests, MatrixDetZero){
    Matrix<int> mat = Matrix<int>({{5, 5, 5, 5},
                                   {25, 25, 25, 25},
                                   {50, 50, 50, 50},
                                   {10, 10, 10, 10}});
    ASSERT_TRUE(mat.det() == 0);
}

TEST(MatrixMethodsTests, MatrixDetPositive){
    Matrix<int> mat = Matrix<int>({{10, 2, 3},
                                   {7, 9, 8},
                                   {12, 11, 14}});
    ASSERT_TRUE(mat.det() == 283);
}

TEST(MatrixMethodsTests, MatrixDetNegative){
    Matrix<int> mat = Matrix<int>({{1, 2, 3},
                                   {7, 9, 8},
                                   {12, 11, 14}});
    ASSERT_TRUE(mat.det() == -59);
}

TEST(MatrixMethodsTests, MatrixDetNotSquare){
    Matrix<int> mat = Matrix<int>({{1, 2, 3},
                                   {7, 9, 8}});
    ASSERT_THROW(mat.det(), MatrixSizeError);
}
//  endregion

//region invert matrix
TEST(MatrixMethodsTests, MatrixInvertThreeByThree){
    Matrix<int> mat = Matrix<int>({
                                          {1, 2, -1},
                                          {-2, 0, 1},
                                          {1, -1, 0}
    });
    Matrix<int> res_mat = Matrix<int>({
                                                  {1, 1, 2},
                                                  {2, 3, 4}
    });
    ASSERT_EQ(mat.inverse(), res_mat);
}

TEST(MatrixMethodsTests, MatrixInvertTwoByTwo){
    Matrix<int> mat = Matrix<int>({
                                          {2, 3},
                                          {2, 2}
                                  });
    Matrix<float> res_mat = Matrix<float>({
                                                  {-1, 1.5},
                                                  {1, -1}
                                          });
    ASSERT_TRUE(mat.inverse().equalPrecision(res_mat, 1e-9));
}

TEST(MatrixMethodsTests, MatrixInvertDegenerate){
    Matrix<int> mat = Matrix<int>({
                                          {1, 1},
                                          {2, 2}
                                  });

    ASSERT_THROW(mat.inverse(), MatrixClassificationError);
}

TEST(MatrixMethodsTests, MatrixInvertNonSquare){
    Matrix<int> mat = Matrix<int>({
                                          {1, 1, 1},
                                          {2, 2, 2}
                                  });

    ASSERT_THROW(mat.inverse(), MatrixSizeError);
}
//  endregion
//  endregion

//  region static methods
//  region identity
TEST(MatrixStaticMethodsTests, MatrixIdentityZero){
    Matrix<int> mat = Matrix<int>::identity<int>(0),
            mat1(0);
    ASSERT_TRUE(mat == mat1);
}

TEST(MatrixStaticMethodsTests, MatrixIdentityOne){
    Matrix<int> mat = Matrix<int>::identity<int>(1),
            mat1({{1}});
    ASSERT_TRUE(mat == mat1);
}
TEST(MatrixStaticMethodsTests, MatrixIdentityPositive){
    Matrix<int> mat = Matrix<int>::identity<int>(3),
            mat1({
                         {1, 0, 0},
                         {0, 1, 0},
                         {0, 0, 1}
                 });
    ASSERT_TRUE(mat == mat1);
}
//  endregion

//  region
TEST(MatrixStaticMethodsTests, MatrixGramOneVector){

}
//  endregion
//  endregion

