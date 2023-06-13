#include "gtest/gtest.h"

#include "../../LowLevel/LowLevel.h"

using namespace LowLevel;

TEST(CoordinateSystemConstructorsTests, CoordinateSystemConstructor) {

    std::vector<std::vector<int>> tmp1 = {{1}, {0}, {0}},
            tmp2 = {{0}, {1}, {0}},
            tmp3 = {{0}, {0}, {1}};

    Point<int> pt({1, 2, 3});
    VectorSpace<int> basis({Vector<int>(tmp1),
                                  Vector<int>(tmp2),
                                  Vector<int>(tmp3)});
    CoordinateSystem<int> cs(pt, basis);

    ASSERT_EQ(cs.initial_point, pt);
    ASSERT_EQ(cs.space, basis);
}

TEST(CoordinateSystemOperatorsTests, CoordinateSystemEqual) {

    std::vector<std::vector<int>> tmp1 = {{1}, {0}, {0}},
            tmp2 = {{0}, {1}, {0}},
            tmp3 = {{0}, {0}, {1}};

    Point<int> pt({1, 2, 3});
    VectorSpace<int> basis({Vector<int>(tmp1),
                            Vector<int>(tmp2),
                            Vector<int>(tmp3)}),
                     basis2({
                         Vector<int>({4, -2, 2}).transposed(),
                         Vector<int>({-3, 3, -4}).transposed(),
                         Vector<int>({2, -4, 3}).transposed()
                     });
    CoordinateSystem<int> cs(pt, basis);
    CoordinateSystem<int> cs2(pt, basis);
    CoordinateSystem<int> cs3(pt, basis2);

    ASSERT_TRUE(cs == cs2);
    ASSERT_FALSE(cs == cs3);
}