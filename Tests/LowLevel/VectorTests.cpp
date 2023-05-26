#include "gtest/gtest.h"

#include "../../LowLevel/Vector.h"
#include "../../Exceptions/VectorError.h"


//  region constructs
TEST(VectorConstructorsTests, VectorConstructsDiffType) {
    Vector<long long> vec_ll(10);
    Vector<int> vec_int(10);
    Vector<int> vec_row({10, 2, 3});
    std::vector<std::vector<int>> tmp = {{23}, {31}, {12}};
    Vector<int> vec_col(tmp);

    ASSERT_TRUE(vec_ll == vec_int &&
                (vec_ll.size() == 10));
    ASSERT_TRUE(vec_row.isTransposed);
    ASSERT_FALSE(vec_col.isTransposed);
}

TEST(VectorConstructorsTests, VectorConstructsFilled) {
    Vector<long long> mat_ll(10, 1);
    std::vector<std::vector<long long>> tmp = {{1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}};
    ASSERT_EQ(mat_ll, Vector<long long>(tmp));
}
//  endregion

//  region operators
//  region equal
TEST(VectorOperatorsTests, VectorColumnEqqRow) {
    std::vector<std::vector<int>> tmp = {{1,}, {2,}, {3,}, {4,}, {5,}, {6,}};
    Vector<int> vec = Vector<int>({1, 2, 3, 4, 5, 6}),
            vec1 = Vector<int>(tmp);
    ASSERT_FALSE(vec == vec1);
}

TEST(VectorOperatorsTests, VectorColumnNotEqqRow) {
    std::vector<std::vector<int>> tmp = {{1,}, {2,}, {3,}, {4,}, {5,}, {6,}};
    Vector<int> vec = Vector<int>({1, 2, 3, 4, 5, 6}),
            vec1 = Vector<int>(tmp);
    ASSERT_TRUE(vec != vec1);
}

TEST(VectorOperatorsTests, VectorColumnEqqDiffHeight){
    std::vector<std::vector<int>> tmp = {{1,}, {2,}, {3,}, {4,}},
            tmp1 = {{1}, {2}, {3}, {4}, {5}};

    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);
    ASSERT_FALSE(vec == vec1);
}

TEST(VectorOperatorsTests, VectorRowEqqDiffWidth){
    std::vector<int> tmp = {1, 2, 3, 4},
            tmp1 = {1, 2, 3, 4, 5};

    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);
    ASSERT_FALSE(vec == vec1);
}

TEST(VectorOperatorsTests, VectorColumnEqqDiffElem){
    std::vector<std::vector<int>> tmp = {{1,}, {2,}, {3,}, {4,}},
            tmp1 = {{1}, {2}, {3}, {5}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);
    ASSERT_FALSE(vec == vec1);
}

TEST(VectorOperatorsTests, VectorRowEqqDiffElem){
    Vector<int> vec = Vector<int>({1, 2, 3, 4, 5, 6}),
            vec1 = Vector<int>({1, 2, 3, 4, 5, 7});
    ASSERT_FALSE(vec == vec1);
}

TEST(VectorOperatorsTests, VectorColumnEqqEqualElem){
    std::vector<std::vector<int>> tmp = {{1,}, {2,}, {3,}, {4,}},
            tmp1 = {{1}, {2}, {3}, {4}};

    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);
    ASSERT_TRUE(vec == vec1);
}

TEST(VectorOperatorsTests, VectorRowEqqEqualElem){
    Vector<int> vec = Vector<int>({1, 2, 3, 4}),
            vec1 = Vector<int>( {1, 2, 3, 4});
    ASSERT_TRUE(vec == vec1);
}

//  region per_equal
TEST(VectorOperatorsTests, VectorColumnPerEqqRow) {
    std::vector<std::vector<float>> tmp = {{1.01,}, {2.01,}, {3.02,}, {4.05,}, {5.07,}, {6.04,}};
    Vector<float> vec = Vector<float>({1, 2, 3, 4, 5, 6}),
            vec1 = Vector<float>(tmp);
    ASSERT_TRUE(vec.equalPrecision(vec1, 0.1));
}

TEST(VectorOperatorsTests, VectorColumnPerNotEqqRow) {
    std::vector<std::vector<float>> tmp = {{1,}, {2,}, {3,}, {4,}, {5,}, {6,}};
    Vector<float> vec = Vector<float>({1.1, 2.2, 3.1, 4.01, 5.1, 6.2}),
            vec1 = Vector<float>(tmp);
    ASSERT_FALSE(vec.equalPrecision(vec1, 0.1));
}

TEST(VectorOperatorsTests, VectorColumnPerEqqDiffHeight){
    std::vector<std::vector<float>> tmp = {{1,}, {2,}, {3,}, {4,}},
            tmp1 = {{1.1}, {2.1}, {3.0}, {4.1}, {5.1}};

    Vector<float> vec = Vector<float>(tmp),
            vec1 = Vector<float>(tmp1);
    ASSERT_FALSE(vec.equalPrecision(vec1, 0.1));
}

TEST(VectorOperatorsTests, VectorRowPerEqqDiffWidth){
    std::vector<float> tmp = {1, 2, 3, 4},
            tmp1 = {1, 2, 3, 4, 5};

    Vector<float> vec = Vector<float>(tmp),
            vec1 = Vector<float>(tmp1);
    ASSERT_FALSE(vec.equalPrecision(vec1));
}

TEST(VectorOperatorsTests, VectorColumnPerEqqDiffElem){
    std::vector<std::vector<float>> tmp = {{1,}, {2,}, {3,}, {4,}},
            tmp1 = {{1}, {2}, {3}, {5}};
    Vector<float> vec = Vector<float>(tmp),
            vec1 = Vector<float>(tmp1);
    ASSERT_FALSE(vec.equalPrecision(vec1));
}

TEST(VectorOperatorsTests, VectorRowPerEqqDiffElem){
    Vector<float> vec = Vector<float>({1, 2, 3, 4, 5, 6}),
            vec1 = Vector<float>({1, 2, 3, 4, 5, 7});
    bool res = vec.equalPrecision(vec1);
    ASSERT_FALSE(res);
}

TEST(VectorOperatorsTests, VectorColumnPerEqqEqualElem){
    std::vector<std::vector<float>> tmp = {{1.2,}, {2.1,}, {3.01,}, {4.2,}},
            tmp1 = {{1.1}, {2.0}, {3.09}, {4.3}};

    Vector<float> vec = Vector<float>(tmp),
            vec1 = Vector<float>(tmp1);
    ASSERT_TRUE(vec.equalPrecision(vec1, 0.5));
}

TEST(VectorOperatorsTests, VectorRowPerEqqEqualElem){
    Vector<float> vec = Vector<float>({1.1, 2.2, 3.0, 4.9}),
            vec1 = Vector<float>({1.2, 2.3, 3.05, 5.0});
    ASSERT_TRUE(vec.equalPrecision(vec1, 0.2));
}
//  endregion
//  endregion

// region addition
TEST(VectorOperatorsTests, VectorColumnAddSameSize){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}},
            tmp1 = {{1}, {2}, {3}},
            tmp_res = {{2}, {5}, {8}};

    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);
    Vector<int> res_vec = Vector<int>(tmp_res);
    ASSERT_EQ(vec + vec1, res_vec);
}

TEST(VectorOperatorsTests, VectorRowAddSameSize){
    Vector<int> vec = Vector<int>({1, 3, 5}),
            vec1 = Vector<int>({1, 2, 3});
    Vector<int> res_vec = Vector<int>({2, 5, 8});
    ASSERT_EQ(vec + vec1, res_vec);
}

TEST(VectorOperatorsTests, VectorColumnAddGrSizeHeight){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}},
            tmp1 = {{1}, {2}, {3}, {4}},
            tmp_res = {{2}, {5}, {8}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1),
            vec_res = Vector<int>(tmp_res);
    ASSERT_EQ(vec + vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorColumnAddLessSizeHeight){
    std::vector<std::vector<int>> tmp = {{1}, {2}, {3}, {4}},
            tmp1 = {{1}, {3}, {5}},
            tmp_res = {{2}, {5}, {8}, {4}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1),
            vec_res = Vector<int>(tmp_res);
    ASSERT_EQ(vec + vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorRowAddGrSizeWidth){
    Vector<int> vec = Vector<int>({1, 2, 3, 4}),
            vec1 = Vector<int>({1, 2, 3, 2, 2}),
            vec_res = Vector<int>({2, 4, 6, 6});
    ASSERT_EQ(vec + vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorRowAddLessSizeWidth){
    Vector<int> vec = Vector<int>({1, 2, 3, 2, 2}),
            vec1 = Vector<int>({1, 2, 3, 4}),
            vec_res = Vector<int>({2, 4, 6, 6, 2});
    ASSERT_EQ(vec + vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorColumAddRow){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}},
            tmp_res = {{2}, {6}, {10}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1,3, 5}),
            vec_res = Vector<int>(tmp_res);
    ASSERT_EQ(vec + vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorRowAddColum){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({2, 4, 5}),
            vec1 = Vector<int>(tmp1),
            vec_res = Vector<int>({3, 7, 10});
    ASSERT_EQ(vec + vec1, vec_res);
}
//  endregion

//  region subtraction
TEST(VectorOperatorsTests,  VectorColumnSubSameSize){
    std::vector<std::vector<int>> tmp = {{1}, {2}, {3}, {6}},
            tmp1 = {{1}, {1}, {4}, {2}},
            tmp_res =  {{0}, {1}, {-1}, {4}};

    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);
    Vector<int> vec_res = Vector<int>(tmp_res);

    ASSERT_EQ(vec - vec1, vec_res);
}

TEST(VectorOperatorsTests,  VectorRowSubSameSize){
    Vector<int> vec = Vector<int>({1, 2, 3, 6}),
            vec1 = Vector<int>({1, 1, 4, 2});
    Vector<int> vec_res = Vector<int>({0, 1, -1, 4});

    ASSERT_EQ(vec - vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorColumnSubGrSizeHeight){
    std::vector<std::vector<int>> tmp = {{1}, {2}, {3}, {6}},
            tmp1 = {{1}, {1}, {4}, {2}, {1}},
            tmp_res = {{0}, {1}, {-1}, {4}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1),
            vec_res = Vector<int>(tmp_res);

    ASSERT_EQ(vec - vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorRowSubGrSizeWidth){
    Vector<int> vec = Vector<int>({1, 2, 3, 6}),
            vec1 = Vector<int>({1, 1, 4, 2, 1}),
            vec_res = Vector<int>({0, 1, -1, 4});

    ASSERT_EQ(vec - vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorColumnSubLessSizeHeight){
    std::vector<std::vector<int>> tmp = {{1}, {1}, {4}, {2}, {1}},
            tmp1 = {{1}, {2}, {3}, {6}},
            tmp_res = {{0}, {-1}, {1}, {-4}, {1}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1),
            vec_res = Vector<int>(tmp_res);
    ASSERT_EQ(vec - vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorRowSubLessSizeWidth){
    Vector<int> vec = Vector<int>({1, 1, 4, 2, 1}),
            vec1 = Vector<int>({1, 2, 3, 6}),
            vec_res = Vector<int>({0, -1, 1, -4, 1});
    ASSERT_EQ(vec - vec1, vec_res);
}
//  endregion

//  region multiplication
//  region multiplication_vector_by_vector
TEST(VectorOperatorsTests, VectorColumnMulRow){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}, {6}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7, 8});
    Matrix<int> res_mat = Matrix<int>({{1, 2, 7, 8},
                                       {3, 6, 21, 24},
                                       {5, 10, 35, 40},
                                       {6, 12, 42, 48}});

    auto calc_res = vec * vec1;

    ASSERT_THROW(std::get<int>(calc_res), std::bad_variant_access);
    ASSERT_EQ(std::get<Matrix<int>>(calc_res), res_mat);
}

TEST(VectorOperatorsTests, VectorColumnMulGrHeight){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}, {7}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7});
    Matrix<int> res_mat = Matrix<int>({{1, 2, 7},
                                       {3, 6, 21},
                                       {5, 10, 35},
                                       {7, 14, 49}});

    auto calc_res = vec * vec1;

    ASSERT_THROW(std::get<int>(calc_res), std::bad_variant_access);
    ASSERT_EQ(std::get<Matrix<int>>(calc_res), res_mat);
}

TEST(VectorOperatorsTests, VectorColumnMulLessHeight){
    std::vector<std::vector<int>> tmp = {{1}, {3}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7});
    Matrix<int> res_mat = Matrix<int>({
                                              {1, 2, 7},
                                              {3, 6, 21}});

    auto calc_res = vec * vec1;

    ASSERT_THROW(std::get<int>(calc_res), std::bad_variant_access);
    ASSERT_EQ(std::get<Matrix<int>>(calc_res), res_mat);
}

TEST(VectorOperatorsTests, VectorRowMulColumn){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2, 7}),
            vec1 = Vector<int>(tmp1);
    int res_scal = 42;

    auto calc_res = vec * vec1;

    ASSERT_THROW(std::get<Matrix<int>>(calc_res), std::bad_variant_access);
    ASSERT_EQ(std::get<int>(calc_res), res_scal);
}

TEST(VectorOperatorsTests, VectorRowMulColumnGrWidth){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2, 7, 8}),
            vec1 = Vector<int>(tmp1);

    ASSERT_THROW(vec * vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowMulColumnLessWidth){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2}),
            vec1 = Vector<int>(tmp1);

    ASSERT_THROW(vec * vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowMulRow){
    std::vector<std::vector<int>> tmp = {{2} , {6}, {3}},
            tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);

    ASSERT_THROW(vec * vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorColumnMulColumn){
    Vector<int> vec = Vector<int>({2 , 6, 3}),
            vec1 = Vector<int>({1, 3, 5});

    ASSERT_THROW(vec * vec1, VectorSizeError);
}
//  endregion

//  region multiplication by matrix
TEST(VectorOperatorsTests, VectorRowMulMatrix){
    Vector<int> vec = Vector<int>({1, 3, 5, 6});
    Matrix<int> mat = Matrix<int>(4, 3, 1);
    Vector<int> res_vec = Vector<int>({15, 15, 15});

    ASSERT_EQ(vec * mat, res_vec);
}

TEST(VectorOperatorsTests, VectorRowMulMatrixDiffHeight){
    Vector<int> vec = Vector<int>({1, 3, 5, 6});
    Matrix<int> mat = Matrix<int>(3, 3, 1);

    ASSERT_THROW(vec * mat, MatrixSizeError);
}

TEST(VectorOperatorsTests, VectorColumnMulMatrix){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>(tmp);
    Matrix<int> mat = Matrix<int>(3, 3, 1);

    ASSERT_THROW(vec * mat, MatrixSizeError);
}
//  endregion

//  region multiplication by scalar
TEST(VectorOperatorsTests, VectorColumnIntMulInt){
    std::vector<std::vector<int>> tmp = {{1}, {2}, {3}, {4}},
            tmp_res = {{10}, {20}, {30}, {40}};

    Vector<int> vec = Vector<int>(tmp);
    int a = 10;
    Vector<int> res_vec = Vector<int>(tmp_res);

    ASSERT_TRUE(vec * a == res_vec);
}

TEST(VectorOperatorsTests, VectorColumnIntMulFloat){
    std::vector<std::vector<int>> tmp = {{1}, {2}, {3}, {4}},
            tmp_res = {{10}, {20}, {30}, {40}};

    Vector<int> vec = Vector<int>(tmp);
    float a = 10.2;
    Vector<int> res_vec = Vector<int>(tmp_res);

    ASSERT_TRUE(vec * a == res_vec);
}

TEST(VectorOperatorsTests, VectorColumnFloatMulInt){
    std::vector<std::vector<float>> tmp = {{1.0}, {2.0}, {3.0}, {4.0}},
            tmp_res = {{10.0}, {20.0}, {30.0}, {40.0}};

    Vector<float> vec = Vector<float>(tmp);
    int a = 10;
    Vector<float> res_vec = Vector<float>(tmp_res);

    ASSERT_TRUE(vec * a == res_vec);
}

TEST(VectorOperatorsTests, VectorColumnFloatMulFloat){
    std::vector<std::vector<float>> tmp = {{1.0}, {2.0}, {3.0}, {4.0}},
            tmp_res = {{10.2}, {20.4}, {30.6}, {40.8}};

    Vector<float> vec = Vector<float>(tmp);
    float a = 10.2;
    Vector<float> res_vec = Vector<float>(tmp_res);
    ASSERT_TRUE(res_vec.equalPrecision(vec * a));
}

TEST(VectorOperatorsTests, VectorRowIntMulInt){
    Vector<int> vec = Vector<int>({1, 2, 3, 4});
    int a = 10;
    Vector<int> res_vec = Vector<int>({10, 20, 30, 40});

    ASSERT_TRUE(vec * a == res_vec);
}

TEST(VectorOperatorsTests, VectorRowIntMulFloat){
    Vector<int> vec = Vector<int>({1, 2, 3, 4});
    float a = 10.2;
    Vector<int> res_vec = Vector<int>({10, 20, 30, 40});

    ASSERT_TRUE(vec * a == res_vec);
}

TEST(VectorOperatorsTests, VectorRowFloatMulInt){
    Vector<float> vec = Vector<float>({1.0, 2.0, 3.0, 4.0});
    int a = 10;
    Vector<float> res_vec = Vector<float>({10.0, 20.0, 30.0, 40.0});

    ASSERT_TRUE(vec * a == res_vec);
}

TEST(VectorOperatorsTests, VectorRowFloatMulFloat){
    Vector<float> vec = Vector<float>({1.0, 2.0, 3.0, 4.0});
    float a = 10.2;
    Vector<float> res_vec = Vector<float>({10.2, 20.4, 30.6, 40.8});
    ASSERT_TRUE(res_vec.equalPrecision(vec * a));
}
//  endregion

//  region scalar_product
TEST(VectorOperatorsTests, VectorColumnScProdRow){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}, {6}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7, 8});
    int res_sc = 90;

    ASSERT_EQ(vec % vec1, res_sc);
}

TEST(VectorOperatorsTests, VectorColumnScProdGrHeight){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}, {7}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7});

    ASSERT_THROW(vec % vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorColumnScProdLessHeight){
    std::vector<std::vector<int>> tmp = {{1}, {3}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7});

    ASSERT_THROW(vec % vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowScProdColumn){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2, 7}),
            vec1 = Vector<int>(tmp1);
    int res_sc = 42;

    ASSERT_EQ(vec % vec1, res_sc);
}

TEST(VectorOperatorsTests, VectorRowScProdColumnGrWidth){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2, 7, 8}),
            vec1 = Vector<int>(tmp1);

    ASSERT_THROW(vec % vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowScProdColumnLessWidth){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2}),
            vec1 = Vector<int>(tmp1);

    ASSERT_THROW(vec % vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowScProdRow){
    std::vector<std::vector<int>> tmp = {{2} , {6}, {3}},
            tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1);
    int res_sc = 35;

    ASSERT_EQ(vec % vec1, res_sc);
}

TEST(VectorOperatorsTests, VectorColumnScProdColumn){
    Vector<int> vec = Vector<int>({2 , 6, 3}),
            vec1 = Vector<int>({1, 3, 5});
    int res_sc = 35;
    ASSERT_EQ(vec % vec1, res_sc);
}
//  endregion

//  region vector_product
TEST(VectorOperatorsTests, VectorColumnVecProdRow){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}},
            tmp_res = {{11}, {-2}, {-1}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7});
    Vector<int> res_vec = Vector<int>(tmp_res);

    ASSERT_EQ(vec ^ vec1, res_vec);
}

TEST(VectorOperatorsTests, VectorColumnVecProdGrHeight){
    std::vector<std::vector<int>> tmp = {{1}, {3}, {5}, {7}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7});

    ASSERT_THROW(vec % vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorColumnVecProdLessHeight){
    std::vector<std::vector<int>> tmp = {{1}, {3}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({1, 2, 7});

    ASSERT_THROW(vec % vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowVecProdColumn){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}},
            tmp_res = {{-11}, {2}, {1}};
    Vector<int> vec = Vector<int>({1, 2, 7}),
            vec1 = Vector<int>(tmp1);

    Vector<int> res_vec = Vector<int>(tmp_res);

    ASSERT_EQ(vec ^ vec1, res_vec);
}

TEST(VectorOperatorsTests, VectorRowVecProdColumnGrWidth){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2, 7, 8}),
            vec1 = Vector<int>(tmp1);

    ASSERT_THROW(vec ^ vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowVecProdColumnLessWidth){
    std::vector<std::vector<int>> tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>({1, 2}),
            vec1 = Vector<int>(tmp1);

    ASSERT_THROW(vec ^ vec1, VectorSizeError);
}

TEST(VectorOperatorsTests, VectorRowVecProdRow){
    std::vector<std::vector<int>> tmp = {{2} , {6}, {3}},
            tmp_res = {{21}, {-7}, {0}},
            tmp1 = {{1}, {3}, {5}};
    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>(tmp1),
            vec_res = Vector<int>(tmp_res);

    ASSERT_EQ(vec ^ vec1, vec_res);
}

TEST(VectorOperatorsTests, VectorColumnVecProdColumn){
    std::vector<std::vector<int>> tmp_res = {{21}, {-7}, {0}};

    Vector<int> vec = Vector<int>({2 , 6, 3}),
            vec1 = Vector<int>({1, 3, 5}),
            res_vec = Vector<int>(tmp_res);

    ASSERT_EQ(vec ^ vec1, res_vec);
}
//  endregion
//  endregion

//  region div_by_scalar
TEST(VectorOperatorsTests, VectorColumnIntDivInt){
    std::vector<std::vector<int>> tmp = {{10}, {20}, {30}, {40}},
            tmp_res = {{1}, {2}, {3}, {4}};

    Vector<int> vec = Vector<int>(tmp);
    int a = 10;
    Vector<int> res_vec = Vector<int>(tmp_res);

    ASSERT_TRUE(vec / a == res_vec);
}

TEST(VectorOperatorsTests, VectorColumnIntDivFloat){
    std::vector<std::vector<int>> tmp = {{10}, {20}, {30}, {40}},
            tmp_res = {{1}, {2}, {3}, {4}};

    Vector<int> vec = Vector<int>(tmp);
    float a = 10.2;
    Vector<int> res_vec = Vector<int>(tmp_res);

    ASSERT_TRUE(vec / a == res_vec);
}

TEST(VectorOperatorsTests, VectorColumnFloatDivInt){
    std::vector<std::vector<float>> tmp = {{10.0}, {20.0}, {30.0}, {40.0}},
            tmp_res = {{1.0}, {2.0}, {3.0}, {4.0}};

    Vector<float> vec = Vector<float>(tmp);
    int a = 10;
    Vector<float> res_vec = Vector<float>(tmp_res);

    ASSERT_TRUE(vec / a == res_vec);
}

TEST(VectorOperatorsTests, VectorColumnFloatDivFloat){
    std::vector<std::vector<float>> tmp = {{10.2}, {20.4}, {30.6}, {40.8}},
            tmp_res = {{1.0}, {2.0}, {3.0}, {4.0}};

    Vector<float> vec = Vector<float>(tmp);
    float a = 10.2;
    Vector<float> res_vec = Vector<float>(tmp_res);
    ASSERT_TRUE(res_vec.equalPrecision(vec / a));
}

TEST(VectorOperatorsTests, VectorRowIntDivInt){
    Vector<int> vec = Vector<int>({10, 20, 30, 40});
    int a = 10;
    Vector<int> res_vec = Vector<int>({1, 2, 3, 4});

    ASSERT_EQ(vec / a, res_vec);
}

TEST(VectorOperatorsTests, VectorRowIntDivFloat){
    Vector<int> vec = Vector<int>({10, 20, 30, 40});
    float a = 10.2;
    Vector<int> res_vec = Vector<int>({1, 2, 3, 4});

    ASSERT_EQ(vec / a, res_vec);
}

TEST(VectorOperatorsTests, VectorRowFloatDivInt){
    Vector<float> vec = Vector<float>({10.0, 20.0, 30.0, 40.0});
    int a = 10;
    Vector<float> res_vec = Vector<float>({1.0, 2.0, 3.0, 4.0});

    ASSERT_TRUE(res_vec.equalPrecision(vec / a, 10e-5));
}

TEST(VectorOperatorsTests, VectorRowFloatDivFloat){
    Vector<float> vec = Vector<float>({10.2, 20.4, 30.6, 40.8});
    float a = 10.2;
    Vector<float> res_vec = Vector<float>({1.0, 2.0, 3.0, 4.0});
    ASSERT_TRUE(res_vec.equalPrecision(vec / a, 10e-5));
}
//  endregion

//  region get_by_index
TEST(VectorOperatorsTests, VectorIndex) {
    std::vector<std::vector<int>> tmp({{1},{2}, {3}, {4}});

    ASSERT_EQ(Vector<int>({1, 2, 3, 4})[3], 4);
    ASSERT_EQ(Vector<int>(tmp)[0], 1);
}

TEST(VectorOperatorsTests, VectorIndexOut) {
    std::vector<std::vector<int>> tmp({{1}, {2}, {3}, {4}});
    Vector<int> vec = Vector<int>({1, 2, 3, 4}),
                vec_col = Vector<int>(tmp);

    ASSERT_THROW(vec[4], MatrixIndexError);
    ASSERT_THROW(vec_col[5], MatrixIndexError);
}

TEST(VectorOperatorsTests, VectorIndexEq) {
    std::vector<std::vector<int>> tmp({{1},{2}, {3}, {4}}),
                                  tmp_res({{1}, {2}, {3}, {134}});

    Vector<int> vec_row({1, 2, 3, 4}), vec_col(tmp),
                vec_row_res({1, 2, 10, 4}), vec_col_res(tmp_res);
    vec_row[2] = 10;
    vec_col[3] = 134;

    ASSERT_EQ(vec_row, vec_row_res);
    ASSERT_EQ(vec_col, vec_col_res);
}
//  endregion
//  endregion

//  region methods
//  region transpose
TEST(VectorMethodsTests, VectorTransposed){
    std::vector<std::vector<int>> tmp = {{10}, {20}, {30}, {40}};

    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({10, 20, 30, 40});

    ASSERT_EQ(vec.transposed(), vec1);
    ASSERT_EQ(vec1.transposed(), vec);
}
TEST(VectorMethodsTests, VectorTranspose){
    std::vector<std::vector<int>> tmp = {{10}, {20}, {30}, {40}};

    Vector<int> vec = Vector<int>(tmp),
            vec1 = Vector<int>({10, 20, 30, 40}),
            vec_res = Vector<int>(vec);
    vec_res.transpose();
    ASSERT_EQ(vec_res, vec1);

    vec_res = Vector<int>(vec1);
    vec_res.transpose();
    ASSERT_EQ(vec_res, vec);
}
TEST(VectorMethodsTests, VectorTransposeOne){
    std::vector<std::vector<int>> tmp = {{2}};
    std::vector<int> tmp1 = {2};

    Vector<int> vec(tmp),
            vec1(tmp1),
            vec_res(vec);
    vec_res.transpose();
    ASSERT_EQ(vec1, vec_res);

    vec_res = vec1;
    vec_res.transpose();
    ASSERT_EQ(vec, vec_res);
}
//  endregion

//  region size
TEST(VectorMethodsTests, VectorColumnSize){
    std::vector<std::vector<int>> tmp = {{1}, {2}, {4}};
    Vector<int> vec = Vector<int>(tmp);

    ASSERT_EQ(vec.size(), 3);
}

TEST(VectorMethodsTests, VectorRowSize){
    Vector<int> vec = Vector<int>({1, 2, 4});

    ASSERT_EQ(vec.size(), 3);
}

TEST(VectorMethodsTests, VectorColumnEmptySize){
    Vector<int> vec = Vector<int>({});

    ASSERT_EQ(vec.size(), 0);
}

TEST(VectorMethodsTests, VectorRowEmptySize){
    std::vector<std::vector<int>> tmp;
    Vector<int> vec = Vector<int>(tmp);

    ASSERT_EQ(vec.size(), 0);
}
//  endregion

//  region length
TEST(VectorMethodsTests, VectorColumnLenght){
    std::vector<std::vector<int>> tmp = {{1}, {2}, {4}};
    Vector<int> vec = Vector<int>(tmp);

    EXPECT_NEAR(vec.length(), 4.5825756, 10e-5);
}

TEST(VectorMethodsTests, VectorRowLenght){
    Vector<int> vec = Vector<int>({1, 2, 4});

    EXPECT_NEAR(vec.length(), 4.5825756, 10e-5);
}

TEST(VectorMethodsTests, VectorEmptyLenght){
    std::vector<std::vector<int>> tmp = {};
    Vector<int> vec = Vector<int>(tmp);

    EXPECT_NEAR(vec.length(), 0, 10e-5);
}
//  endregion

//  region normalize
TEST(VectorMethodsTests, VectorColumnNormalize){
    std::vector<std::vector<int>> tmp = {{4}, {4}, {4}, {4}};
    std::vector<std::vector<float>> tmp_res = {{0.5}, {0.5}, {0.5}, {0.5}};
    Vector<int> vec = Vector<int>(tmp);
    Vector<float> vec_res = Vector<float>(tmp_res);
    Vector<long double> norm_vec = vec.normalize();
    ASSERT_TRUE(vec_res.equalPrecision(norm_vec, 10e-5));
}

TEST(VectorMethodsTests, VectorRowNormalize){
    Vector<int> vec = Vector<int>({2, 2, 2, 2});
    Vector<float> vec_res = Vector<float>({0.5, 0.5, 0.5, 0.5});

    ASSERT_TRUE(vec_res.equalPrecision(vec.normalize(), 10e-5));
}

TEST(VectorMethodsTests, VectorZeroNormalize){
    Vector<int> vec = Vector<int>({0, 0, 0});
    Vector<float> vec_res = Vector<float>({0, 0, 0});
    ASSERT_TRUE(vec_res.equalPrecision(vec.normalize(), 10e-5));
}

TEST(VectorMethodsTests, VectorEmptyNormalize){
    Vector<int> vec = Vector<int>({});
    Vector<float> vec_res = Vector<float>({});
    ASSERT_TRUE(vec_res.equalPrecision(vec.normalize(), 10e-5));
}
//  endregion
//  endregion


//  region BilinearForm
TEST(VectorFunctionTests, VectorBiForm){
    std::vector<std::vector<int>> tmp2 = {{10}, {20}, {30}};

    Vector<int> vec1 = Vector<int>({5, 15, 25}),
            vec2 = Vector<int>(tmp2);
    Matrix<int> mat = Matrix<int>(
            {
                    {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}
            });


    ASSERT_EQ(BilinearForm<int>(mat, vec1, vec2), 18000);
}

TEST(VectorFunctionTests, VectorBiFormFloat){
    std::vector<std::vector<long double>> tmp2 = {{10.5}, {20.5}, {30.2}};

    Vector<long double> vec1 = Vector<long double>({5.9, 15.2, 25.3}),
            vec2 = Vector<long double>(tmp2);
    Matrix<long double> mat = Matrix<long double>(
            {
                    {1.3, 2.5, 3.1},
                    {4.4, 5.3, 6.5},
                    {7.6, 8.5, 9.9}
            });


    ASSERT_NEAR(BilinearForm<long double>(mat, vec1, vec2), 20264.407, 10e-5);
}

TEST(VectorFunctionTests, VectorBiFormDiffSize){
    std::vector<std::vector<long double>> tmp2 = {{10.5}, {20.5}, {30.2}, {10.2}};

    Vector<long double> vec1 = Vector<long double>({5.9, 15.2, 25.3}),
            vec2 = Vector<long double>(tmp2);
    Matrix<long double> mat = Matrix<long double>(
            {
                    {1.3, 2.5, 3.1, 10},
                    {4.4, 5.3, 6.5, 32.3},
                    {7.6, 8.5, 9.9, 23.2}
            });

    ASSERT_THROW(BilinearForm<long double>(mat, vec1, vec2), MatrixSizeError);
}
//  endregion