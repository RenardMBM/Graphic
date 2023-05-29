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