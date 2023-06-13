#include "gtest/gtest.h"

#include "../../Engine/Engine.h"

using namespace Engine;

TEST(GameTests, GameConstructors){
    ASSERT_NO_THROW(Game game);
    ASSERT_NO_THROW(Game game1((LowLevel::CoordinateSystem<floatType>()), (EntitiesList())));
}

TEST(GameTests, GameRunMethods){
    Game game;

    ASSERT_NO_THROW(game.run());
    ASSERT_NO_THROW(game.update());
    ASSERT_NO_THROW(game.exit());
}

TEST(GameTests, GameCreators){
    LowLevel::CoordinateSystem<Engine::floatType> cs;
    Game game(cs, EntitiesList());

    Entity e = game.get_entity_class();
    Ray r = game.get_ray_class(LowLevel::Point<floatType>({0,0,1}), LowLevel::Vector<floatType>({1,2,1}));
    ASSERT_EQ(e.cs, cs);
    ASSERT_EQ(r.cs, cs);
}