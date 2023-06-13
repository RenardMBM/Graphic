#include "gtest/gtest.h"

#include "../../Engine/Engine.h"

using namespace Engine;

TEST(EntityListTests, EntityListsAddAndGet){
    EntitiesList list;

    Entity entity1;
    Entity entity2;
    Entity entity3;

    ASSERT_NO_THROW(list.append(entity1));
    ASSERT_NO_THROW(list.append(entity2));
    ASSERT_NO_THROW(list.append(entity3));

    ASSERT_TRUE(list[entity1.identifier].identifier->get_value() == entity1.identifier->get_value());
    ASSERT_TRUE(list[entity2.identifier].identifier->get_value() == entity2.identifier->get_value());
    ASSERT_TRUE(list[entity3.identifier].identifier->get_value() == entity3.identifier->get_value());
}

TEST(EntityListTests, EntityListsExec){
    EntitiesList list;

    Entity entity1;
    Entity entity2;
    Entity entity3;

    ASSERT_NO_THROW(list.append(entity1));
    ASSERT_NO_THROW(list.append(entity2));
    ASSERT_NO_THROW(list.append(entity3));

    ASSERT_NO_THROW(list.exec([](Entity& entity) -> void{
        entity.set_property("prop_exec", (std::string)"exists");
    }));

    ASSERT_EQ(std::any_cast<std::string>(list[entity1.identifier].get_property("prop_exec")), "exists");
    ASSERT_EQ(std::any_cast<std::string>(list[entity2.identifier].get_property("prop_exec")), "exists");
    ASSERT_EQ(std::any_cast<std::string>(list[entity3.identifier].get_property("prop_exec")), "exists");
}

TEST(EntityListTests, EntityListsRemove){
    EntitiesList list;

    Entity entity1;
    Entity entity2;
    Entity entity3;

    ASSERT_NO_THROW(list.append(entity1));
    ASSERT_NO_THROW(list.append(entity2));
    ASSERT_NO_THROW(list.append(entity3));

    ASSERT_NO_THROW(list.remove(entity1.identifier));

    ASSERT_THROW(list[entity1.identifier], std::range_error);
    ASSERT_TRUE(list[entity2.identifier].identifier->get_value() == entity2.identifier->get_value());
    ASSERT_TRUE(list[entity3.identifier].identifier->get_value() == entity3.identifier->get_value());
}

TEST(EntityListTests, EntityListsSet){
    EntitiesList list;

    Entity entity1;
    Entity entity2;
    Entity entity3;

    ASSERT_NO_THROW(list.append(entity1));
    ASSERT_NO_THROW(list.append(entity2));
    ASSERT_NO_THROW(list.append(entity3));

    ASSERT_NO_THROW(list[entity1.identifier].set_property("new_prop", (std::string)"prop"));

    ASSERT_EQ(std::any_cast<std::string>(list[entity1.identifier].get_property("new_prop")), "prop");
}