#include "gtest/gtest.h"

#include "../../Engine/Engine.h"

using namespace Engine;

//  region constructs
TEST(EntityTests, EntityConstructs) {
    Entity defaultEntity,
           entity3d(LowLevel::CoordinateSystem<floatType>(
                   LowLevel::Point<floatType>(3, 0),
                   LowLevel::VectorSpace<floatType>({
                                    LowLevel::Vector<floatType>({1, 0, 0}),
                                    LowLevel::Vector<floatType>({0, 1, 0}),
                                    LowLevel::Vector<floatType>({0, 0, 1})}))),
           entityByEntity(defaultEntity);

    ASSERT_TRUE(defaultEntity.cs == entity3d.cs);
    ASSERT_FALSE(defaultEntity.identifier == entity3d.identifier);

    ASSERT_TRUE(entity3d.cs == entityByEntity.cs);
    ASSERT_FALSE(entity3d.identifier == entityByEntity.identifier);
}
//  endregion

//  region operators
//  region get_by_index
TEST(EntityTests, EntityOperatorIndex) {
    Entity defaultEntity;

    ASSERT_NO_THROW(defaultEntity.set_property("test_prop1", 10));
    ASSERT_NO_THROW(defaultEntity.set_property("test_prop2", (std::string)"str"));
    ASSERT_NO_THROW(defaultEntity.set_property("test_prop3", LowLevel::Point<int>({1, 1, 0})));

    ASSERT_EQ(std::any_cast<int>(defaultEntity["test_prop1"]), 10);
    ASSERT_EQ(std::any_cast<std::string>(defaultEntity["test_prop2"]), "str");
    ASSERT_EQ(std::any_cast<LowLevel::Point<int>>(defaultEntity["test_prop3"]),
              LowLevel::Point<int>({1, 1, 0}));

    ASSERT_NO_THROW(defaultEntity["test_prop1"] = 77.2f);
    ASSERT_EQ(std::any_cast<float>(defaultEntity["test_prop1"]), 77.2f);
}
//  endregion
//  endregion

//  region methods
TEST(EntityTests, EntityMethodProperty) {
    Entity defaultEntity;

    ASSERT_NO_THROW(defaultEntity.set_property("test_prop1", 10));
    ASSERT_NO_THROW(defaultEntity.set_property("test_prop2", (std::string)"str"));
    ASSERT_NO_THROW(defaultEntity.set_property("test_prop3", LowLevel::Point<int>({1, 1, 0})));

    ASSERT_EQ(std::any_cast<int>(defaultEntity.get_property("test_prop1")), 10);
    ASSERT_EQ(std::any_cast<std::string>(defaultEntity.get_property("test_prop2")), "str");
    ASSERT_EQ(std::any_cast<LowLevel::Point<int>>(defaultEntity.get_property("test_prop3")),
            LowLevel::Point<int>({1, 1, 0}));

    ASSERT_NO_THROW(defaultEntity.remove_property("test_prop1"));

    ASSERT_THROW(defaultEntity.get_property("test_prop1"), std::range_error);
    ASSERT_NO_THROW(defaultEntity.remove_property("test_prop1"));
}
//  endregion
