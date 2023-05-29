#include "gtest/gtest.h"

#include "../../LowLevel/LowLevel.h"

using namespace LowLevel;

TEST(VectorSpaceOperatorTests, VectorSpaceEqual) {
    std::vector<std::vector<int>> tmp1 = {{1}, {0}, {0}},
        tmp2 = {{0}, {1}, {0}},
        tmp3 = {{0}, {0}, {1}},
        tmp4 = {{0}, {0}, {3}};
    VectorSpace<int> vs({Vector<int>(tmp1),
            Vector<int>(tmp2),
            Vector<int>(tmp3)});

    VectorSpace<int> vs_copy({Vector<int>(tmp1),
                         Vector<int>(tmp2),
                         Vector<int>(tmp3)});
    VectorSpace<int> vs_4({Vector<int>(tmp1),
                              Vector<int>(tmp2),
                              Vector<int>(tmp4)});
    ASSERT_EQ(vs, vs_copy);
    ASSERT_FALSE(vs == vs_4);
}

TEST(VectorSpaceMethodsTests, VectorSpaceScalarProduct) {
    std::vector<std::vector<int>> tmp1 = {{1}, {0}, {0}},
                                tmp2 = {{0}, {1}, {0}},
                                tmp3 = {{0}, {0}, {1}};

    VectorSpace<int> vs_standard({Vector<int>(tmp1),
                                        Vector<int>(tmp2),
                                        Vector<int>(tmp3)});
    Vector<int> vec = Vector<int>({1, 3, 5}),
            vec1 = Vector<int>({1, 2, 7});
    ASSERT_EQ(vs_standard.scalar_product(vec, vec1), vec % vec1);

    tmp1 = {{2}, {5}};
    tmp2 = {{4}, {-2}};
    VectorSpace<int> vs({Vector<int>(tmp1),
            Vector<int>(tmp2)});
    ASSERT_THROW(vs.scalar_product(vec, vec1), MatrixSizeError);


    vec = Vector<int>({1, 3});
    vec1 = Vector<int>({4, 2});

    ASSERT_EQ(vs.scalar_product(vec, vec1), 208);
}

TEST(VectorSpaceMethodsTests, VectorSpaceVectorProduct) {
    std::vector<std::vector<int>> tmp1 = {{1}, {0}, {0}},
            tmp2 = {{0}, {1}, {0}},
            tmp3 = {{0}, {0}, {1}};

    VectorSpace<int> vs_standard({Vector<int>(tmp1),
                                  Vector<int>(tmp2),
                                  Vector<int>(tmp3)});

    Vector<int> vec = Vector<int>({1, 3, 5}),
            vec1 = Vector<int>({1, 2, 7});
    ASSERT_EQ(vs_standard.vector_product(vec, vec1), vec ^ vec1);

    tmp1 = {{2}, {5}};
    tmp2 = {{4}, {-2}};
    VectorSpace<int> vs({Vector<int>(tmp1),
                         Vector<int>(tmp2)});
    vec = Vector<int>({1, 3});
    vec1 = Vector<int>({4, 2});

    ASSERT_THROW(vs.vector_product(vec, vec1), MatrixSizeError);
}

TEST(VectorSpaceMethodsTests, VectorSpaceAsVector) {
    std::vector<std::vector<int>> tmp1 = {{1}, {0}, {0}},
            tmp2 = {{0}, {1}, {0}},
            tmp3 = {{0}, {0}, {1}};

    VectorSpace<int> vs_standard({Vector<int>(tmp1),
                                  Vector<int>(tmp2),
                                  Vector<int>(tmp3)});

    std::vector<std::vector<int>> tmp_res = {{1}, {3}, {5}};
    ASSERT_EQ(vs_standard.as_vector(Point<int>({1, 3, 5})),
              Vector<int>(tmp_res));

    tmp1 = {{2}, {5}};
    tmp2 = {{4}, {-2}};
    VectorSpace<int> vs({Vector<int>(tmp1),
                         Vector<int>(tmp2)});

    tmp_res = {{14}, {-1}};
    ASSERT_EQ(vs.as_vector(Point<int>({1, 3})), Vector<int>(tmp_res));
}
