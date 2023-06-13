#include "gtest/gtest.h"

#include "../../Engine/Engine.h"

using namespace Engine;

TEST(GameObjectTests, GameObjectConstructors){
    ASSERT_NO_THROW(GameObject gameObj);
    ASSERT_NO_THROW(GameObject gameObj2(LowLevel::Point<floatType>({1,0,21}), LowLevel::Vector<floatType>({2,213,23})));
}

//  region methods
TEST(GameObjectTests, GameObjectMethodMove){
    GameObject gameObj;
    GameObject gameObj2(LowLevel::Point<floatType>({1,0,21}),
                        LowLevel::Vector<floatType>({2,213,23}));

    LowLevel::Vector<floatType> step({1, 0, -1});
    ASSERT_NO_THROW(gameObj.move(step));
    ASSERT_NO_THROW(gameObj2.move(step));

    ASSERT_EQ(std::any_cast<LowLevel::Point<floatType>>(gameObj.get_property("position")),
            LowLevel::Point<floatType>({1,0,-1}));
    ASSERT_EQ(std::any_cast<LowLevel::Point<floatType>>(gameObj2.get_property("position")),
            LowLevel::Point<floatType>({2,0, 20}));
}

TEST(GameObjectTests, GameObjectMethodRotate3D){
    set_precision(4);
    GameObject gameObj;
    GameObject gameObj2(LowLevel::Point<floatType>({1,0,21}),
                        LowLevel::Vector<floatType>({2,213,23}));
    ASSERT_NO_THROW(gameObj.rotate_3d(M_PI, M_PI/2, 3*M_PI));
    set_precision(10);
    ASSERT_NO_THROW(gameObj2.rotate_3d(-M_PI, 0, 3*M_PI));

    ASSERT_EQ(std::any_cast<LowLevel::Vector<floatType>>(gameObj.get_property("direction")),
              LowLevel::Vector<floatType>({-1, 1, 1}).transposed());
    ASSERT_EQ(std::any_cast<LowLevel::Vector<floatType>>(gameObj2.get_property("direction")),
            LowLevel::Vector<floatType>({-2, 213, -23}).transposed());
}

TEST(GameObjectTests, GameObjectMethodPlanarRotate){
    set_precision(4);
    GameObject gameObj;
    GameObject gameObj2(LowLevel::Point<floatType>({1,0,21}),
                        LowLevel::Vector<floatType>({2,213,23}));

    ASSERT_NO_THROW(gameObj.planar_rotate({0,1}, M_PI));
    ASSERT_NO_THROW(gameObj2.planar_rotate({0,2}, -M_PI));
    ASSERT_THROW(gameObj2.planar_rotate({0,3}, -M_PI), std::range_error);

    ASSERT_EQ(std::any_cast<LowLevel::Vector<floatType>>(gameObj.get_property("direction")),
              LowLevel::Vector<floatType>({-1, -1, 1}).transposed());

    ASSERT_EQ(std::any_cast<LowLevel::Vector<floatType>>(gameObj2.get_property("direction")),
              LowLevel::Vector<floatType>({-2, 213, -23}).transposed());
}

//  endregion
