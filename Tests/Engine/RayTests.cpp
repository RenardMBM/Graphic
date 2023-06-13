#include "gtest/gtest.h"

#include "../../Engine/Engine.h"

using namespace Engine;

//  region constructs
TEST(RayConstructorsTests, RayConstructors) {
    LowLevel::CoordinateSystem<floatType> cs;
    LowLevel::Point<floatType> pt;
    LowLevel::Vector<floatType> direction({1,1,1});

//    Ray ray(cs, pt, direction);
//    ASSERT_EQ(cs, ray.cs);
//    ASSERT_EQ(pt, ray.pt);
//    ASSERT_EQ(direction.transposed(), ray.direction);
}
//  endregion

//  region operators
//  region equal
TEST(RayOperatorsTests, RayOperatorsEqual) {
    LowLevel::CoordinateSystem<floatType> cs;
    LowLevel::Point<floatType> pt;
    LowLevel::Vector<floatType> direction({1,1,1}),
            direction1({1, 0, 1});

    Ray ray(cs, pt, direction);
    Ray ray1(cs, pt, direction);
    Ray ray2(cs, pt, direction.transposed());
    Ray ray3(cs, pt, direction1);
//
    ASSERT_TRUE(ray == ray1);
    ASSERT_TRUE(ray == ray2);
    ASSERT_FALSE(ray == ray3);
}
//  endregion

//  endregion

//  region methods
//  endregion

//  region static_methods
//  endregion